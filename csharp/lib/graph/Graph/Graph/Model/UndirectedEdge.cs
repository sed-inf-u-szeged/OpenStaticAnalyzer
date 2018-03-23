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

using System.Linq;
using System.Xml.Linq;

namespace Graph.Model
{
	public
	class UndirectedEdge
	: Edge
	{
		public
		UndirectedEdge( string type, Node source, Node target )
		: base( type, source, target )
		{
			Attributes = new AttributeCollection( string.Empty, string.Empty );
		}

		public
		AttributeCollection Attributes { get; private set; }

		public override
		string ToString( )
		{
			return string.Format(
				"{0} --[{1}]--> {2} ({3})",
				Source,
				Attributes.Attributes.Count( ),
				Target,
				Type);
		}

		public override
		XElement Dump( )
		{
			var _result = base.Dump( );
			_result.Add( new XAttribute( "direction", "bidirectional" ) );
			foreach ( var _attribute in Attributes.Attributes )
			{
				_result.Add( _attribute.Dump( ) );
			}
			return _result;
		}
	}
}