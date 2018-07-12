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
using System.Linq;
using System.Xml.Linq;
using Graph.Model.Sub;

namespace Graph.Model
{
	public
	class CompositeAttribute
	: Attribute<IEnumerable< IAttribute > >
	{
		public
		CompositeAttribute( string name, string context, IEnumerable<IAttribute> value )
		: base( name, context, value ) {}

		public override
		AttributeType Type
		{
			get
			{
				return AttributeType.Composite;
			}
		}

		public
		IAttribute this[ string name ]
		{
			get
			{
				return Value.First( _a => _a.Name == name );
			}
		}

		public override
		XElement Dump( )
		{
			var _result = new XElement(
				"attribute",
				new XAttribute( "type", Type.ToString( ) ),
				new XAttribute( "name", Name ),
				new XAttribute( "context", Context ) );
			foreach ( var _attribute in Value )
			{
				_result.Add( _attribute.Dump( ) );
			}
			return _result;
		}
	}
}