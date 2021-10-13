using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using Columbus.CSAN.Utils;
using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Logical;
using Microsoft.CodeAnalysis;
using Type = Columbus.Lim.Asg.Nodes.Type.Type;

namespace Columbus.CSAN.Contexts
{
    class SolutionContext : AbstractContext
    {
        public Solution Solution { get; }
        public Factory LimFactory { get; }
        public ReverseEdges ReverseEdges { get; }
        public OverrideRelations OverrideRelations { get; }
        public LimOrigin LimOrigin { get; }

        public Filter HardFilter { get; }
        public Filter SoftFilter { get; }

        // TODO some of these are only accessed from SymbolConverter, moving them there would be great, but that would require
        // Symbol converter to be here instead, but it needs FileContexts at the moment
        public Dictionary<string, ClassGenericInstance> CgiMap { get; }
        public Dictionary<string, MethodGenericInstance> MgiMap { get; }
        /// <summary>
        /// Main map containing every Lim node build for the Roslyn symbols
        /// </summary>
        public SymbolMap<uint> MainMap { get; }
        public Dictionary<uint, uint> FileMap { get; }
        public SymbolMap<Type> TypeMap { get; }
        public Dictionary<uint, Dictionary<uint, ulong>> ComponentTLOCMap { get; }
        public LLOCMapType LLOCMap { get; }

        public WatchBag WatchBag { get; }

        private readonly Regex changePathFrom;
        private readonly string changePathTo;

        public SolutionContext(Solution solution, OptionBag optionBag, WatchBag watchBag)
        {
            Solution = solution;
            LimFactory = new Factory(new StrTable()) {Language = Types.LanguageKind.lnkCsharp};
            ReverseEdges = LimFactory.GetReverseEdges();
            OverrideRelations = new OverrideRelations(LimFactory);
            LimOrigin = new LimOrigin();

            HardFilter = new Filter(optionBag.ExternalHardFilter);
            SoftFilter = new Filter(optionBag.ExternalSoftFilter);

            CgiMap = new Dictionary<string, ClassGenericInstance>();
            MgiMap = new Dictionary<string, MethodGenericInstance>();
            MainMap = new SymbolMap<uint>();
            FileMap = new Dictionary<uint, uint>();
            TypeMap = new SymbolMap<Type>();
            ComponentTLOCMap = new Dictionary<uint, Dictionary<uint, ulong>>();
            LLOCMap = new LLOCMapType();

            WatchBag = watchBag;

            var cpf = optionBag.ChangePathFrom;
            if (!string.IsNullOrEmpty(cpf))
            {
                changePathFrom = new Regex(
                    "^" + (cpf.Last() == Path.DirectorySeparatorChar ? cpf : cpf + Path.DirectorySeparatorChar)
                    .Replace(Path.DirectorySeparatorChar.ToString(), "\\" + Path.DirectorySeparatorChar),
                    RegexOptions.IgnoreCase);
                changePathTo = optionBag.ChangePathTo;
            }
        }

        /// <summary>
        /// Processes ChangePathFrom and to arguments on the given path
        /// </summary>
        /// <param name="path"></param>
        /// <returns></returns>
        public string ProcessPath(string path)
        {
            return string.IsNullOrEmpty(path) || changePathFrom == null
                ? path
                : changePathFrom.Replace(path, changePathTo);
        }
    }
}
