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

using System.Linq;
using System.Xml.Linq;

namespace Graph.Model
{
	public
	class DirectedEdge
	: Edge
	{
		public
		DirectedEdge( string type, Node source, Node target )
		: base( type, source, target )
		{
			ForwardAttributes = new AttributeCollection( string.Empty,string.Empty );
			BackwardAttributes = new AttributeCollection( string.Empty,string.Empty );
		}

		public
		AttributeCollection ForwardAttributes { get; private set; }

		public
		AttributeCollection BackwardAttributes { get; private set; }

		public override
		string ToString( )
		{
			return string.Format(
				"{0} -->[{1};{2}]<-- {3} ({4})",
				Source,
				ForwardAttributes.Attributes.Count( ),
				BackwardAttributes.Attributes.Count( ),
				Target,
				Type );
		}

		public override
		XElement Dump( )
		{
			var _result = base.Dump( );
			_result.Add( new XAttribute( "direction", "bidirectional" ) );
			foreach ( var _attribute in ForwardAttributes.Attributes )
			{
				_result.Add( _attribute.Dump( ) );
			}
			var _backPair = new XElement( "edgePair" );
			foreach ( var _attribute in BackwardAttributes.Attributes )
			{
				_backPair.Add( _attribute.Dump( ) );
			}
			_result.Add( _backPair );
			return _result;
		}
	}
}