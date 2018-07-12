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
using System.Xml.Linq;
using Graph.Model.Sub;
using Graph.Model.Super;

namespace Graph.Model
{
	public abstract
	class Edge
	: Typed
	, IDumpable
	{
		public
		Edge( string type, Node source, Node target )
		: base( string.Empty, type )
		{
			Source = source;
			Target = target;
		}

		public override
		string UniqueID
		{
			get
			{
				throw new NotSupportedException( );
			}
		}

		public
		Node Source { get; private set; }

		public
		Node Target { get; private set; }

		public virtual
		XElement Dump( )
		{
			return new XElement(
				"edge",
				new XAttribute( "type", Type ),
				new XAttribute( "to", Target.UniqueID ) );
		}
	}
}