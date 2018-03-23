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
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Threading;
using System.Xml.Linq;
using Graph.Model;
using Graph.Model.Sub;
using Graph.Model.Super;
using NUnit.Framework;
using System.Linq;

namespace Graph.Control.Loading
{
	public
	class Loader
	{
		Dictionary< uint, string > texts = new Dictionary< uint, string >( );

		public
		GeneralGraph Load(FileInfo input)
		{
			return Load( input.OpenRead( ), input.FullName );
		}

		public
		GeneralGraph Load(Stream input, string name)
		{
			GeneralGraph _graph = new GeneralGraph( name );
			using ( BinaryReader _input = new BinaryReader( input ) )
			{
				checkMagicNumber( _input );
				skipBuckets( _input );
				readTexts( _input );
				readMetaData( _input, _graph );
				readNodes( _input, _graph );
			}
			return _graph;
		}

		void readNodes( BinaryReader input, GeneralGraph graph )
		{
			uint _uid;
			uint _typeOfNode;
			do
			{
				_uid = input.ReadUInt32( );
				_typeOfNode = input.ReadUInt32( );
				if ( _uid == 0 &&
				     _typeOfNode == 0 )
				{
					break;
				}

				Node _source = getOrCreateNode( graph, _uid );
				var _attributesOfNode = readAttributes( input );
				_source.AddAttributes( _attributesOfNode.ToArray( ) );
				_source.Type = texts[ _typeOfNode ];
				_source.TimeOfCreation = DateTime.Now;

				readEdges( input, graph, _source );

				graph.Add( _source );
			} while ( _uid != 0 &&
			          _typeOfNode != 0 );
		}

		void readEdges( BinaryReader _input, GeneralGraph _graph, Node _source )
		{
			uint _typeKey;
			uint _directionOfEdge;
			uint _targetKey;
			do
			{
				_typeKey = _input.ReadUInt32( );
				_directionOfEdge = _input.ReadUInt32( );
				_targetKey = _input.ReadUInt32( );
				if ( _typeKey == 0 && _directionOfEdge == 0 &&
				     _targetKey == 0 )
				{
					break;
				}
				string _typeOfEdge = texts[ _typeKey ];
				bool _pairNeeded = _input.ReadBoolean( );
				var _attributesOfEdge = readAttributes( _input );
				Node _target = getOrCreateNode( _graph, _targetKey );

				switch ( _directionOfEdge )
				{
					case 0:
						var _undirectedEdge = _graph.Connect( _source, _typeOfEdge, _target );
						_undirectedEdge.Attributes.AddAttributes( _attributesOfEdge.ToArray( ) );
						break;
					case 1:
						var _directedEdge = _graph.ConnectDirected( _source, _typeOfEdge, _target );
						_directedEdge.ForwardAttributes.AddAttributes( _attributesOfEdge.ToArray( ) );
						if ( _pairNeeded )
						{
							var _attributesOfReverseEdge = readAttributes( _input );
							_directedEdge.BackwardAttributes.AddAttributes( _attributesOfReverseEdge.ToArray( ) );
						}
						break;
					default:
						throw new NotSupportedException( "unknown edge direction" );
				}
			} while ( _typeKey != 0 && _directionOfEdge != 0 &&
			          _targetKey != 0 );
		}

		Node getOrCreateNode( GeneralGraph graph, uint uid )
		{
			Node _node;
			var _id = texts[ uid ];
			var _nodeCandidates = graph.Nodes.Where( _n => _n.UniqueID == _id );
			var _candidates = _nodeCandidates as Node[ ] ?? _nodeCandidates.ToArray( );
			if ( _candidates.Any( ) )
			{
				_node = _candidates.First( );
			}
			else
			{
				_node = new Node( _id, string.Empty );
			}
			return _node;
		}

		List< IAttribute > readAttributes( BinaryReader input )
		{
			uint _numberOfAttributes = input.ReadUInt32( );
			List< IAttribute > _attributes = new List< IAttribute >( );
			for ( int _i = 0; _i < _numberOfAttributes; _i++ )
			{
				uint _typeKey = input.ReadUInt32( );
				uint _nameKey = input.ReadUInt32( );
				uint _contextKey = input.ReadUInt32( );
				string _name;
				_name = texts[ _nameKey ];
				var _context = texts[ _contextKey ];
				switch ( _typeKey )
				{
					case 0: //int
						int _intValue = input.ReadInt32( );
						_attributes.Add( new IntAttribute( _name, _context, _intValue ) );
						break;
					case 1: //float
						float _floatValue = input.ReadSingle( );
						_attributes.Add( new FloatAttribute( _name, _context, _floatValue ) );
						break;
					case 2: //string
						uint _stringValue = input.ReadUInt32( );
						_attributes.Add( new StringAttribute( _name, _context, texts[ _stringValue ] ) );
						break;
					case 3: //composite
						List< IAttribute > _innerAttributes = readAttributes( input );
						_attributes.Add( new CompositeAttribute( _name, _context, _innerAttributes ) );
						break;
					default:
						throw new NotSupportedException( "unknown attribute type" );
				}
			}
			return _attributes;
		}

		void readMetaData( BinaryReader _input, GeneralGraph _graph )
		{
			uint _numberOfHeaders = _input.ReadUInt32( );
			for ( int _i = 0; _i < _numberOfHeaders; _i++ )
			{
				uint _key = _input.ReadUInt32( );
				uint _value = _input.ReadUInt32( );
				_graph.AddMetaData( texts[ _key ], texts[ _value ] );
			}
		}

		void readTexts( BinaryReader _input )
		{
			uint _key;
			do
			{
				_key = _input.ReadUInt32( );
				if (_key == 0) break;
				uint _length = _input.ReadUInt32( );
				string _text = Encoding.UTF8.GetString( _input.ReadBytes( ( int )_length ) );
				texts[ _key ] = _text;
			} while ( _key != 0 );
			texts[ 0 ] = string.Empty;
			//texts = texts.OrderBy( _e => _e.Key ).ToDictionary( _e => _e.Key, _e => _e.Value );
		}

		void skipBuckets( BinaryReader _input )
		{
			uint _numberOfBucket = _input.ReadUInt32( );
			_input.ReadBytes( ( int )( 2 * _numberOfBucket ) );
		}

		void checkMagicNumber( BinaryReader _input )
		{
			string _magicNumber = Encoding.UTF8.GetString( _input.ReadBytes( 6 ) );
			if ( _magicNumber != "STRTBL" )
			{
				throw new FormatException( "Bad magic number." );
			}
		}

		[ TestFixture ]
		public static
		class Test
		{
			[Conditional("TEST")]
			[ Test ]
			public static
			void TestLoader( )
			{
				Loader _loader = new Loader( );
				DirectoryInfo _samples = new DirectoryInfo( "samples" );
				if(_samples.Exists)
				{
					foreach ( var _file in _samples.GetFiles( "*.graph" ) )
					{
						GeneralGraph _graph = _loader.Load( _file );
						_graph.DumpToFile( );
						Process.Start(
							new ProcessStartInfo( @"native-dumper\GraphDump.exe", "-xml "+_file.FullName ) );
					}
				}
			}
		}
	}
}