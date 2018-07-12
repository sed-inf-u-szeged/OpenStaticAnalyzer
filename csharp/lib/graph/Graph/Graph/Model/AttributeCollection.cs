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

namespace Graph.Model
{
	public
	class AttributeCollection
	: Typed
	{
		List< IAttribute > attributes = new List< IAttribute >( );

		public
		AttributeCollection( string uniqueId, string type )
		: base( uniqueId, type ) {}

		internal
		void AddAttributes(params IAttribute[] attribute)
		{
			attributes.AddRange( attribute );
		}

		public
		IEnumerable< IAttribute > Attributes
		{
			get
			{
				return attributes;
			}
		}

		public
		IAttribute this[ string name ]
		{
			get
			{
				return Attributes.First( _a => _a.Name == name );
			}
		}
	}
}