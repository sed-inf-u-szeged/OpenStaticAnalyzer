using System.Collections.Generic;
using Columbus.CSAN.Commons;
using Columbus.CSAN.Contexts;
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
    internal class LOC
    {
        private readonly SolutionContext solutionContext;
        private readonly TLOC tloc;

        public LOC(SolutionContext solutionContext)
        {
            this.solutionContext = solutionContext;
            tloc = new TLOC(solutionContext);
        }

        public void SetLOC( Scope limScope )
        {
            var intervals = new List< Interval >( );
            var loc = (long)tloc.Calculate(limScope, ref intervals);
            if ( loc == 0 ) return;
            unchecked
            {
                limScope.TLOC = ( uint ) loc;
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
                    SetLOC(method);
                    var methodLOC = method.LOC;
                    var temp = new List< Interval >( );
                    var methodTLOC = ( uint ) tloc.Calculate( method, ref temp );

                    loc -= ( methodTLOC - methodLOC );
                }
                else if ( Lim.Asg.Common.getIsScope( member ) && LessOrEqualsThan( limScope, member as Scope ) &&
                          limScope.Id != solutionContext.LimFactory.Root )
                {
                    var visitedBorders = new Dictionary< uint, HashSet< uint > >( );
                    var memberScope = member as Scope;
                    var memberIntervals = new List< Interval >( );
                    var memberTLOC = tloc.Calculate( memberScope, ref memberIntervals );

                    loc -= (long)memberTLOC;

                    foreach ( var interval in memberIntervals )
                    {
                        if ( BorderCounts( limScope, interval.Key, interval.From, ref visitedBorders ) ) loc++;
                        if ( BorderCounts( limScope, interval.Key, interval.To, ref visitedBorders ) ) loc++;
                    }
                }
                memberIt = memberIt.getNext( );
            }

            if ( loc < 0 )
            {
                //Console.WriteLine("Debug: would have been negative, set to 0");
                loc = 0;
            }

            limScope.LOC = ( uint ) loc;
        }

        private bool BorderCounts( Scope limScope, uint key, uint line,
            ref Dictionary< uint, HashSet< uint > > visited )
        {
            if ( !visited.ContainsKey( key ) )
                visited.Add( key, new HashSet< uint >( ) );

            // if already checked this border
            var mapped = visited[ key ];
            if ( mapped.Contains( line ) ) return false;
            visited[ key ].Add( line );

            // if the parent also has something in this line
            if ( solutionContext.LLOCMap.ContainsKey( limScope.Id ) &&
                 solutionContext.LLOCMap[ limScope.Id ].ContainsKey( key ) )
            {
                mapped = solutionContext.LLOCMap[ limScope.Id ][ key ];
                if ( mapped.Contains( line ) ) return true;
            }

            return false;
        }

        private static bool LessOrEqualsThan( Scope lhs, Scope rhs )
        {
            if ( Lim.Asg.Common.getIsMethod( lhs ) ) return true;
            if ( Lim.Asg.Common.getIsClass( lhs ) ) return !Lim.Asg.Common.getIsMethod( rhs );
            if ( Lim.Asg.Common.getIsPackage( lhs ) ) return Lim.Asg.Common.getIsPackage( rhs );
            return false;
        }

        public void AddLocToComponent( uint NodeId, uint Key, ulong lastLineNumber )
        {
            tloc.InsertComponentTLOCMap( NodeId, Key, lastLineNumber );
            var itBegin = solutionContext.ReverseEdges.constIteratorBegin( NodeId,
                Types.EdgeKind.edkComponent_Contains );
            while ( itBegin.getValue( ) != null )
            {
                AddLocToComponent( itBegin.getValue( ).Id, Key, lastLineNumber );
                itBegin = itBegin.getNext( );
            }
        }
    }
}
