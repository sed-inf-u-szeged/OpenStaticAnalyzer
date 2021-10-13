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

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Xml.Linq;
using AKindnessCommons.EventRelated;
using Graph.Model.Sub;
using Graph.Model.Super;

namespace Graph.Model
{
	public
	class GeneralGraph
	: IDumpable
	{
		public
		string Name { get; private set; }

		Dictionary<string,string> metaData=new Dictionary< string, string >();

		internal
		void AddMetaData(string key, string value)
		{
			metaData[ key ] = value;
		}

		List< Node > nodes = new List< Node >( );

		internal
		void Add(Node node)
		{
			ensureContainment( node );
		}

		List< Edge > edges = new List< Edge >( );

		public
		GeneralGraph( string name )
		{
			Name = name;
		}

		public
		IEnumerable< Node > Nodes
		{
			get
			{
				return nodes;
			}
		}

		public
		IEnumerable< Edge > Edges
		{
			get
			{
				return edges;
			}
		}

		public
		Node this[ string index ]
		{
			get
			{
				return nodes.First( _n => _n.UniqueID == index );
			}
		}

		internal
		DirectedEdge ConnectDirected(Node source, string type, Node target)
		{
			ensureContainment( source );
			ensureContainment( target );
			DirectedEdge _edge = source.ConnectTo( target, type );
			if(!edges.Contains( _edge ))
			{
				edges.Add( _edge );
			}
			return _edge;
		}

		internal
		UndirectedEdge Connect(Node aNode, string type, Node bNode)
		{
			ensureContainment( aNode );
			ensureContainment( bNode );
			UndirectedEdge _edge = aNode.Connect( bNode, type );
			if(!edges.Contains( _edge ))
			{
				edges.Add( _edge );
			}
			return _edge;
		}

		void ensureContainment( Node node )
		{
			var _candidates = nodes.Where( _n => _n.UniqueID == node.UniqueID );
			if ( !_candidates.Any( ) )
			{
				nodes.Add( node );
			}
		}

		public override
		string ToString( )
		{
			return string.Format( "N:{0} E:{1}", nodes.Count( ), edges.Count( ) );
		}

		public
		XElement Dump( )
		{
			var _result = new XElement( "graph" );
			var _header = new XElement( "header" );
			foreach ( var _metaData in metaData )
			{
				_header.Add(
					new XElement( "info", new XAttribute( "name", _metaData.Key ), new XAttribute( "value", _metaData.Value ) ) );
			}
			_result.Add( _header );
			var _data = new XElement( "data" );
			foreach ( var _node in Nodes.OrderByDescending( _n=>_n.TimeOfCreation ) )
			{
				_data.Add( _node.Dump( ) );
			}
			_result.Add( _data );
			return _result;
		}

		public
		void DumpToFile()
		{
			var _dumpDoc = new XDocument( new XDeclaration( "1.0", "utf-8", "yes" ), Dump( ) );
			_dumpDoc.Save(
				string.Format( "{0}.ggdump.xml", Name ) );
		}

		public
		IEnumerable< Node > Roots( Func< Node, bool > nodeSelector, Func< Edge, bool > edgeSelector )
		{
			return nodes.Where( nodeSelector ).Where( _node => !_node.InEdges.Where( edgeSelector ).Any( ) );
		}

		public
		bool IsSingleRooted(Func< Node, bool > nodeSelector, Func<Edge,bool> edgeSelector)
		{
			return Roots( nodeSelector, edgeSelector ).Count( ) == 1;
		}

		public
		bool IsForest(Func<Edge,bool> edgeSelector)
		{
			var _nonTreeNodes = nodes.Where( _e => _e.InEdges.Where( edgeSelector ).Count( ) > 1 );
			return !_nonTreeNodes.Any( );
		}
	}
}
