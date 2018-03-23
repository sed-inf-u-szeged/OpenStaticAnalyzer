/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
 *
 *  Licensed under Version 1.2 of the EUPL (the "Licence");
 *
 *  You may not use this work except in compliance with the Licence.
 *
 *  You may obtain a copy of the Licence in the LICENSE file or at:
 *
 *  https://joinup.ec.europa.eu/software/page/eupl
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the Licence is distributed on an "AS IS" basis,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the Licence for the specific language governing permissions and
 *  limitations under the Licence.
 */

using System.Collections.Generic;
using System.Threading.Tasks;

using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Base;
using Columbus.Lim.Asg.Nodes.Logical;

using Columbus.CSAN.Utils;
using Columbus.CSAN.Utils.Info;

using Microsoft.CodeAnalysis;

namespace Columbus.CSAN.Commons
{
    /// <summary>
    /// Singleton main class to hold "global" variables through the analysis.
    /// Some of these get updated, e.g. per file, or project.
    /// </summary>
    class MainDeclaration
    {
        private static MainDeclaration instance;

        public SemanticModel Model { get; set; }

        public static MainDeclaration Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new MainDeclaration();
                }

                return instance;
            }
        }

        private MainDeclaration()
        {
            LimFactory = new Factory(new StrTable());
            ClassStack = new Stack<ClassInfo>();
            MethodStack = new Stack<MethodInfo>();
            NamespaceStack = new Stack<uint>();
            LocalMap = new SymbolMap<uint>();
            FileMap = new Dictionary<uint, uint>();
            TypeMap = new SymbolMap<Columbus.Lim.Asg.Nodes.Type.Type>();
            CgiMap = new Dictionary<string, ClassGenericInstance>();
            UsesStack = new Stack<HashSet<uint>>();
            MgiMap = new Dictionary<string, MethodGenericInstance>();
            LLOCMap = new LLOCMapType();
            ComponentTLOCMap = new Dictionary<uint, Dictionary<uint, ulong>>();
            LimOrigin = new LimOrigin();
            MainWatch = new Stopwatch();
            RoslynWatch = new Stopwatch();
            CSSIWatch = new Stopwatch();
            LIMWatch = new Stopwatch();
            Statistics = new Statistic[1];
            Statistics[0] = new Statistic();
            OverrideRelations = new OverrideRelations(LimFactory);
            FxCopTasks = new LinkedList<Task>();
        }
        /// <summary>
        /// Stopwatch for roughly measuring time being spent in Roslyn's code. Started before every
        /// major roslyn method call, eg. getting semantic models, and stopped right after the call returned.
        /// </summary>
        public Stopwatch RoslynWatch { get; private set; }

        /// <summary>
        /// Stopwatch for measuring C# language asg building time. CrossEdges are not included however.
        /// </summary>
        public Stopwatch CSSIWatch { get; private set; }

        /// <summary>
        /// Stopwatch for measuring LIM asg building time. C# asg's crossedges are also included, because those
        /// are not taking much time, and are filled from LIM visitors.
        /// </summary>
        public Stopwatch LIMWatch { get; private set; }

        /// <summary>
        /// Main stopwatch. Started at the very beginning of Main() and runs during the whole analysis.
        /// </summary>
        public Stopwatch MainWatch { get; private set; }

        public Statistic[] Statistics { get; private set; }

        /// <summary>
        /// The currently analysed file is filtered out by softfilter.
        /// </summary>
        public bool CurrentFileIsSoftFiltered { get; set; }

        public Filter HardFilter { get; set; }

        public Filter SoftFilter { get; set; }

        public OverrideRelations OverrideRelations { get; set; }

        public ReverseEdges RevEdges { get; set; }

        public Dictionary<uint, Dictionary<uint, ulong>> ComponentTLOCMap { get; private set; }

        public LLOCMapType LLOCMap { get; private set; }

        public Factory LimFactory { get; private set; }

        public LimOrigin LimOrigin { get; private set; }

        public Component Component  { get; set; }

        public Stack<uint> NamespaceStack { get; private set; }

        public Stack<ClassInfo> ClassStack { get; private set; }

        public Stack<MethodInfo> MethodStack { get; private set; }

        public Solution Solution { get; set; }

        /// <summary>
        /// ISymbol to Lim map
        /// </summary>
        /// <returns></returns>
        public SymbolMap<uint> LocalMap { get; private set; }

        public Package Root { get; set; }

        public Dictionary<uint, uint> FileMap { get; private set; }

        public SymbolMap<Lim.Asg.Nodes.Type.Type> TypeMap { get; private set; }

        public Dictionary<string, ClassGenericInstance> CgiMap { get; private set; }

        public Dictionary<string, MethodGenericInstance> MgiMap { get; private set; }

        public Stack<HashSet<uint>> UsesStack { get; private set; }

        public string CSSIExtension { get; set; }

        public bool DumpLimml = false;

        public bool DumpCsharpml = false;

        /// <summary>
        /// Holds the changepathfrom argument converted to regex with this method:
        /// '^' + argums["changepathfrom"].Replace("\\", "\\\\")
        /// </summary>
        public string ChangePathFrom = string.Empty;
        public string ChangePathTo = string.Empty;

        /// <summary>
        /// The task of the background Project Building. Null if building is disabled.
        /// </summary>
        public Task BuildTask { get; set; }

        public ICollection<Task> FxCopTasks { get; private set; }
    }
}