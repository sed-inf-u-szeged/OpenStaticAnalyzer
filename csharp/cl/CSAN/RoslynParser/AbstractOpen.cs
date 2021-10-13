using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Loader;
using SysIO = System.IO;
using System.Threading.Tasks;
using Columbus.CSAN.Exceptions;
using Microsoft.CodeAnalysis.MSBuild;
using Microsoft.Build.Locator;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.Emit;

namespace Columbus.CSAN.RoslynParser
{
    abstract class AbstractOpen : IDisposable
    {
        private readonly string filePath;
        protected readonly MSBuildWorkspace msbuildWorkspace;
        protected readonly EventHandler<WorkspaceDiagnosticEventArgs> workspaceFailedHandler = (sender, args) => throw new MsBuildException(args.Diagnostic.Message);

        public string CssiExtension { get; protected set; }

        public Solution Solution { get; protected set; }

        public List<Project> TopologicallySortedProjectDependencies { get; protected set; } = new List<Project>();

        protected string Path
        {
            get
            {
                var fullPath = SysIO.Path.GetFullPath(filePath);
                return String.IsNullOrWhiteSpace(fullPath) ? String.Empty : fullPath;
            }
        }

        protected AbstractOpen(string path, string configuration, string platform)
        {
            if (String.IsNullOrEmpty(path))
                throw new ArgumentNullException(nameof(path));

            filePath = path;

            RegisterVisualStudioInstance();

            msbuildWorkspace = MSBuildWorkspace.Create(new Dictionary<string, string>
            {
                { "CheckForSystemRuntimeDependency", "true" },
                //{ "DesignTimeBuild",                 "false" },
                //{ "BuildingInsideVisualStudio",      "true" },
                { "Configuration",                   configuration },
                { "Platform",                        platform }
            });
            msbuildWorkspace.SkipUnrecognizedProjects = true;
            msbuildWorkspace.LoadMetadataForReferencedProjects = true;
            msbuildWorkspace.WorkspaceFailed += workspaceFailedHandler;
        }

        private static void RegisterVisualStudioInstance()
        {
            var instances = MSBuildLocator.QueryVisualStudioInstances().ToList();
            WriteMsg.WriteLine("Found VisualStudio and MSBuild instances:", WriteMsg.MsgLevel.DDebug);
            instances.ForEach(i => WriteMsg.WriteLine($"    {i.Name} {i.Version} {i.VisualStudioRootPath} {i.MSBuildPath}", WriteMsg.MsgLevel.DDebug));

            VisualStudioInstance registered = null;

            foreach (var instance in instances)
            {
                try
                {
                    MSBuildLocator.RegisterInstance(instance);
                    WriteMsg.WriteLine("Registered VisualStudio and MSBuild instance:", WriteMsg.MsgLevel.DDebug);
                    WriteMsg.WriteLine($"{instance.Name} {instance.Version} {instance.VisualStudioRootPath} {instance.MSBuildPath}", WriteMsg.MsgLevel.DDebug);
                    registered = instance;
                    break;
                }
                catch (ArgumentException e)
                {
                    WriteMsg.WriteLine($"Failed to register VS instance: {instance.Name} {instance.Version} {instance.VisualStudioRootPath} {instance.MSBuildPath}", WriteMsg.MsgLevel.DDebug);
                    WriteMsg.WriteLine(e.Message, WriteMsg.MsgLevel.DDebug);
                    WriteMsg.WriteLine(e.StackTrace, WriteMsg.MsgLevel.DDDebug);
                }
            }

            if (registered == null)
                throw new MsBuildException($"Could not locate MsBuild. Make sure that you have installed the appropriate tools listed in the User's Guide.");

            // Workaround for NuGet binaries on Core.
            // https://github.com/microsoft/MSBuildLocator/issues/86#issuecomment-640275377
            AssemblyLoadContext.Default.Resolving += (assemblyLoadContext, assemblyName) =>
            {
                var path = SysIO.Path.Combine(registered.MSBuildPath, assemblyName.Name + ".dll");
                return SysIO.File.Exists(path) ? assemblyLoadContext.LoadFromAssemblyPath(path) : null;
            };
        }

        /// <summary>
        /// Factory method to create the appropriate instance for the path given (.cs/.csproj/.xproj/.sln)
        /// </summary>
        /// <param name="path">Path of the source, project or solution file</param>
        /// <param name="configuration"></param>
        /// <param name="platform"></param>
        public static AbstractOpen CreateInstance(string path, string configuration, string platform)
        {
            string ext = SysIO.Path.GetExtension(path);
            switch (ext)
            {
                case ".sln":
                    return new SolutionOpen(path, configuration, platform);
                case ".csproj":
                case ".xproj":
                    return new ProjectOpen(path, configuration, platform);
                case ".cs":
                    return new FileOpen(path, configuration, platform);
                default:
                    throw new ArgumentException("Invalid file type: " + ext); // TODO more user friendly handling for this
            }
        }

        protected async Task<EmitResult> EmitProject(Project project)
        {
            if (String.IsNullOrWhiteSpace(project.OutputFilePath))
                throw new ColumbusException(nameof(EmitProject), $"Output path for poject ${project} is empty!");

            var compilation = await project.GetCompilationAsync();

            string directory = SysIO.Path.GetDirectoryName(project.OutputFilePath);
            string pdbPath = SysIO.Path.Combine(directory, SysIO.Path.GetFileNameWithoutExtension(project.OutputFilePath) + ".pdb");

            if (!SysIO.Directory.Exists(directory))
                SysIO.Directory.CreateDirectory(directory);

            using (var fileStream = SysIO.File.Create(project.OutputFilePath))
            using (var pdbStream = SysIO.File.Create(pdbPath))
                return compilation.Emit(fileStream, pdbStream);
        }

        public abstract Task<bool> BuildSoulution();

        public abstract void Parse();

        #region IDisposable Support
        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
                msbuildWorkspace?.Dispose();
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }
        #endregion

        protected static IEnumerable<MetadataReference> GetGlobalReferences()
        {
            var assemblies = new[] 
            {
                /*Making sure all MEF assemblies are loaded*/
                typeof(System.Composition.Convention.AttributedModelProvider).Assembly, //System.Composition.AttributeModel
                typeof(System.Composition.Convention.ConventionBuilder).Assembly,   //System.Composition.Convention
                typeof(System.Composition.Hosting.CompositionHost).Assembly,        //System.Composition.Hosting
                typeof(System.Composition.CompositionContext).Assembly,             //System.Composition.Runtime
                typeof(System.Composition.CompositionContextExtensions).Assembly,   //System.Composition.TypedParts

                /*Used for the GeneratedCode attribute*/
                //typeof(System.CodeDom.Compiler.CodeCompiler).Assembly,              //System.CodeDom.Compiler

                typeof(ValueTask<object>).Assembly,                                 //corlib or System.Threading.Tasks.Extensions
                typeof(System.Linq.Enumerable).Assembly,                            //corlib or System.Linq
            };

            var returnSet = (from a in assemblies
                select MetadataReference.CreateFromFile(a.Location)).ToHashSet();

            //The location of the .NET assemblies
            var coreLibLocation = typeof(object).Assembly.Location;
            var assemblyPath = SysIO.Path.GetDirectoryName(coreLibLocation);

            /*
             * Adding some necessary .NET assemblies
             * These assemblies couldn't be loaded correctly via the same construction as above,
             * in specific the System.Runtime.
             */
            returnSet.Add(MetadataReference.CreateFromFile(coreLibLocation));
            returnSet.Add(MetadataReference.CreateFromFile(SysIO.Path.Combine(assemblyPath, "System.dll")));
            returnSet.Add(MetadataReference.CreateFromFile(SysIO.Path.Combine(assemblyPath, "System.Console.dll")));
            returnSet.Add(MetadataReference.CreateFromFile(SysIO.Path.Combine(assemblyPath, "System.Core.dll")));
            returnSet.Add(MetadataReference.CreateFromFile(SysIO.Path.Combine(assemblyPath, "System.Runtime.dll")));

            returnSet.Add(MetadataReference.CreateFromFile(typeof(ValueTask<object>).Assembly.Location));

            return returnSet;
        }
    }
}
