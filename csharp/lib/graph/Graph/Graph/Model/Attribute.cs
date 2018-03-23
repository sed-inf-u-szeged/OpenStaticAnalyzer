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

using System.Xml.Linq;
using Graph.Model.Sub;

namespace Graph.Model
{
	public abstract
	class Attribute<TValue>
	: IAttribute
	{
		public abstract
		AttributeType Type { get; }

		public
		string Name { get; private set; }

		/// <summary>
		/// Store some meta information about the attribute.
		/// </summary>
		public
		string Context { get; private set; }

		TValue value;

		object IAttribute.Value
		{
			get
			{
				return value;
			}
		}

		public
		TValue Value
		{
			get
			{
				return value;
			}
			private set
			{
				this.value = value;
			}
		}

		protected
		Attribute( string name, string context, TValue value )
		{
			Name = name;
			Context = context;
			Value = value;
		}

		public override
			string ToString( )
		{
			return string.Format( "{0} == {1} ({2})", Name, Value, Context );
		}

		public virtual
		XElement Dump( )
		{
			return new XElement(
				"attribute",
				new XAttribute( "type", Type.ToString( ) ),
				new XAttribute( "name", Name ),
				new XAttribute( "context", Context ),
				new XAttribute( "value", Value ) );
		}
	}
}