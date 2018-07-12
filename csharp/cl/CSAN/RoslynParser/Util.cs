/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2018 Department of Software Engineering - University of Szeged
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

using Microsoft.CodeAnalysis;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Columbus.CSAN.RoslynParser
{
    static class Util
    {
        public static IEnumerable<MetadataReference> GetGlobalReferences()
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
                typeof(System.CodeDom.Compiler.CodeCompiler).Assembly,              //System.CodeDom.Compiler
            };

            var refs = from a in assemblies
                       select MetadataReference.CreateFromFile(a.Location);
            var returnList = refs.ToList();

            //The location of the .NET assemblies
            var assemblyPath = Path.GetDirectoryName(typeof(object).Assembly.Location);

            /* 
                * Adding some necessary .NET assemblies
                * These assemblies couldn't be loaded correctly via the same construction as above,
                * in specific the System.Runtime.
                */
            returnList.Add(MetadataReference.CreateFromFile(Path.Combine(assemblyPath, "mscorlib.dll")));
            returnList.Add(MetadataReference.CreateFromFile(Path.Combine(assemblyPath, "System.dll")));
            returnList.Add(MetadataReference.CreateFromFile(Path.Combine(assemblyPath, "System.Core.dll")));
            returnList.Add(MetadataReference.CreateFromFile(Path.Combine(assemblyPath, "System.Runtime.dll")));

            return returnList;
        }

    }
}
