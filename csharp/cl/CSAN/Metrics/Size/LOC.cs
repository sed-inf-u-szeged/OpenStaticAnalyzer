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

using System.Collections.Generic;
using System.Runtime.CompilerServices;
using Columbus.CSAN.Commons;
using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Logical;

namespace Columbus.CSAN.Metrics.Size
{
    /// <summary>
    ///     Method:
    ///     number of code lines of the method, including empty and comment lines; however, its anonymous and local classes are
    ///     not included.
    ///     Class:
    ///     number of code lines of the class, including empty and comment lines, as well as its local methods; however, its
    ///     nested, anonymous, and local classes are not included.
    ///     Package:
    ///     number of code lines of the package, including empty and comment lines; however, its subpackages are not included.
    /// </summary>
    internal static class LOC
    {
        public static void SetLOC( this Scope limScope )
        {
            var intervals = new List< Interval >( );
            var m_LOC = ( long ) TLOC.Calculate( limScope, ref intervals );
            if ( m_LOC == 0 ) return;
            unchecked
            {
                limScope.TLOC = ( uint ) m_LOC;
            }

            var memberIt = limScope.HasMemberListIteratorBegin;
            while ( memberIt.getValue( ) != null )
            {
                var member = memberIt.getValue( );
                // the contents of a method count while its inner member's contents do not
                // so we calculate the difference between the method's LOC and TLOC first
                // and subtract only that from the enclosing scope's LOC.
                if ( Lim.Asg.Common.getIsMethod( member ) && !Lim.Asg.Common.getIsMethod( limScope ) )
                {
                    var method = member as Method;
                    method.SetLOC( );
                    var methodLOC = method.LOC;
                    var temp = new List< Interval >( );
                    var methodTLOC = ( uint ) TLOC.Calculate( method, ref temp );

                    m_LOC -= ( methodTLOC - methodLOC );
                }
                else if ( Lim.Asg.Common.getIsScope( member ) && limScope.LessOrEqualsThan( member as Scope ) &&
                          limScope.Id != MainDeclaration.Instance.LimFactory.Root )
                {
                    var visitedBorders = new Dictionary< uint, HashSet< uint > >( );
                    var memberScope = member as Scope;
                    var memberIntervals = new List< Interval >( );
                    var memberTLOC = TLOC.Calculate( memberScope, ref memberIntervals );

                    m_LOC -= (long)memberTLOC;

                    foreach ( var interval in memberIntervals )
                    {
                        if ( BorderCounts( limScope, interval.Key, interval.From, ref visitedBorders ) ) m_LOC++;
                        if ( BorderCounts( limScope, interval.Key, interval.To, ref visitedBorders ) ) m_LOC++;
                    }
                }
                memberIt = memberIt.getNext( );
            }

            if ( m_LOC < 0 )
            {
                //Console.WriteLine("Debug: would have been negative, set to 0");
                m_LOC = 0;
            }

            limScope.LOC = ( uint ) m_LOC;
        }

        private static bool BorderCounts( Scope limScope, uint key, uint line,
            ref Dictionary< uint, HashSet< uint > > visited )
        {
            if ( !visited.ContainsKey( key ) )
                visited.Add( key, new HashSet< uint >( ) );

            // if already checked this border
            var mapped = visited[ key ];
            if ( mapped.Contains( line ) ) return false;
            visited[ key ].Add( line );

            // if the parent also has something in this line
            if ( MainDeclaration.Instance.LLOCMap.ContainsKey( limScope.Id ) &&
                 MainDeclaration.Instance.LLOCMap[ limScope.Id ].ContainsKey( key ) )
            {
                mapped = MainDeclaration.Instance.LLOCMap[ limScope.Id ][ key ];
                if ( mapped.Contains( line ) ) return true;
            }

            return false;
        }

        private static bool LessOrEqualsThan( this Scope lhs, Scope rhs )
        {
            if ( Lim.Asg.Common.getIsMethod( lhs ) ) return true;
            if ( Lim.Asg.Common.getIsClass( lhs ) ) return !Lim.Asg.Common.getIsMethod( rhs );
            if ( Lim.Asg.Common.getIsPackage( lhs ) ) return Lim.Asg.Common.getIsPackage( rhs );
            return false;
        }

        public static void AddLocToComponent( uint NodeId, uint Key, ulong lastLineNumber )
        {
            TLOC.InsertComponentTLOCMap( NodeId, Key, lastLineNumber );
            var itBegin = MainDeclaration.Instance.RevEdges.constIteratorBegin( NodeId,
                Types.EdgeKind.edkComponent_Contains );
            while ( itBegin.getValue( ) != null )
            {
                AddLocToComponent( itBegin.getValue( ).Id, Key, lastLineNumber );
                itBegin = itBegin.getNext( );
            }
        }
    }
}