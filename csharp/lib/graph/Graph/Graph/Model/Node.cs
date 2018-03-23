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
using System.Xml.Linq;
using Graph.Model.Sub;
using Graph.Model.Super;

namespace Graph.Model
{
	public
	class Node
	: AttributeCollection
	, IDumpable
	{
		internal
		DateTime TimeOfCreation { get; set; }

		List< Edge > edges = new List< Edge >( );

		public
		Node( string uniqueId, string type )
		: base( uniqueId, type ) {}

		internal
		DirectedEdge ConnectTo(Node target, string type)
		{
			DirectedEdge _edge = new DirectedEdge( type, this, target );
			edges.Add( _edge );
			target.edges.Add( _edge );
			return _edge;
		}

		internal
		UndirectedEdge Connect(Node other, string type)
		{
			UndirectedEdge _edge = new UndirectedEdge( type, this, other);
			edges.Add( _edge );
			other.edges.Add( _edge );
			return _edge;
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
		IEnumerable< Edge > OutEdges
		{
			get
			{
				return
					edges
						.OfType< DirectedEdge >( )
						.Where( _e => _e.Source == this )
						.Union<Edge>( edges.OfType< UndirectedEdge >( ) );
			}
		}

		public
		IEnumerable< Edge > InEdges
		{
			get
			{
				return
					edges
						.OfType< DirectedEdge >( )
						.Where( _e => _e.Target == this )
						.Union<Edge>( edges.OfType< UndirectedEdge >( ) );
			}
		}

		public
		XElement Dump( )
		{
			var _result = new XElement(
				"node",
				new XAttribute( "name", UniqueID ),
				new XAttribute( "type", Type ) );
			foreach ( var _attribute in Attributes )
			{
				_result.Add( _attribute.Dump( ) );
			}
			foreach ( var _edge in OutEdges )
			{
				_result.Add( _edge.Dump( ) );
			}
			return _result;
		}

		public override
		string ToString( )
		{
			if ( Attributes.Any( _a=>_a.Name=="Name" ) )
			{
				return string.Format( "{0} ({2}) of {1}", UniqueID, Type, Attributes.First( _a => _a.Name == "Name" ).Value );
			}
			else
			{
				return string.Format( "{0} of {1}", UniqueID, Type );
			}
		}
	}
}