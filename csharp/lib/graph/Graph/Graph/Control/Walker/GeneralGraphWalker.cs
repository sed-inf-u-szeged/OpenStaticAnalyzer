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

using System;
using System.Collections.Generic;
using System.Linq;
using AKindnessCommons.EventRelated;
using Graph.Control.ErrorHandling;
using Graph.Model;
using Graph.Model.Super;

namespace Graph.Control.Walker
{
	public
	class GeneralGraphWalker
	{
		GeneralGraph graph;

		Dictionary< Node, int > touchCounters = new Dictionary< Node, int >( );

		public
		GeneralGraphWalker( GeneralGraph graph )
		{
			this.graph = graph;
		}

		public
		event EventHandler< EventArgs< Node >> ShowUp;

		public
		event EventHandler< EventArgs<  Node > > PassOff;

		public
		event EventHandler< EventArgs< Node > > Visiting;

		public
		int GetTouchCountOf(Node node)
		{
			if(touchCounters.ContainsKey( node ))
			{
				return touchCounters[ node ];
			}
			else
			{
				return 0;
			}
		}

		Node touch(Node node)
		{
			if ( !touchCounters.ContainsKey( node ) )
			{
				touchCounters[ node ] = 0;
			}
			touchCounters[ node ]++;
			return node;
		}

		public
		void Visit(Action<List<Node>,Node > incrementor, Func<Node,bool> nodeSelector, Func<Edge,bool> edgeSelector )
		{
			List< Node > _entitiesToVisit = new List< Node >( graph.Roots(nodeSelector, edgeSelector) );
			while ( _entitiesToVisit.Any( ) )
			{
				Node _current = _entitiesToVisit.First( );
				_entitiesToVisit.Remove( _current );
				if(nodeSelector(_current))
				{
					if ( GetTouchCountOf( _current ) == 0 )
					{
						ShowUp.Raise( this, new EventArgs< Node >( _current ) );
					}
					if ( GetTouchCountOf(_current) == 1 )
					{
						PassOff.Raise( this, new EventArgs< Node >( _current ) );
					}
					if ( GetTouchCountOf(_current) == 0 )
					{
						incrementor( _entitiesToVisit, _current );
					}
					Visiting.Raise( this, new EventArgs< Node >( _current ) );
				}
			}
		}

		public
		void DepthFirstVisit(Func<Edge,bool> edgeSelector, Func< Node, bool > nodeSelector )
		{
			if ( graph.IsForest(edgeSelector) )
			{
				Visit(
					( _entitiesToVisit, _current ) =>
					{
						touch( _current );
						var _nodesOnfilteredEdges = _current.OutEdges.Where( edgeSelector ).Select(
							_e =>
							{
								if ( _e.Source.UniqueID != _current.UniqueID )
								{
									return _e.Source;
								}
								else if ( _e.Target.UniqueID != _current.UniqueID )
								{
									return _e.Target;
								}
								else
								{
									throw new InvalidGraphException( "Edge attached to vertex which is niether its source nor its target." );
								}
							} );
						//simulate the behavior of stack push operation (in a batch)
						_entitiesToVisit.InsertRange( 0, _nodesOnfilteredEdges.Where( nodeSelector ).Union( new[ ] { _current } ) );
					},
					nodeSelector, edgeSelector );
			}
		}

		public
		void BreadthFirstVisit(Func<Edge,bool> edgeSelector, Func< Node, bool > cut )
		{
			throw new NotImplementedException( );
			if ( graph.IsForest(edgeSelector) )
			{
				Visit(
					( _entitiesToVisit, _current ) =>
					//TODO: integrate edgeSelector into this query
					_entitiesToVisit.AddRange(
						touch( _current ).OutEdges.Select(
							_edge => graph.Nodes.First(
								_node => ReferenceEquals( _node, _edge.Target ) ) ).Concat( new[ ] { _current } ) ),
					cut, edgeSelector );
			}
		}
	}
}