/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus <https://github.com/maldicion069/monkeybrushplusplus>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "ObjParser.hpp"
#include <math.h>

namespace MB
{
	ObjParser::ObjParser( void )
	{
	}

	std::string ObjParser::loadFile( std::string& filename )
	{
		std::ifstream file( filename.c_str( ) );
		std::stringstream buffer;

		buffer << file.rdbuf( );
		std::string str = buffer.str( );
		return str;
	}

	std::vector< std::string > ObjParser::split( const std::string& s, char c )
	{
		std::vector< std::string > v;
		std::string::size_type i = 0;
		std::string::size_type j = s.find( c );

		while ( j != std::string::npos )
		{
			v.push_back( s.substr( i, j - i ) );
			i = ++j;
			j = s.find( c, j );

			if ( j == std::string::npos )
				v.push_back( s.substr( i, s.length( ) ) );
		}
		return v;
	}

	bool ObjParser::isNumeric( const std::string& input )
	{
		return std::all_of( input.begin( ), input.end( ), ::isdigit );
	}

	bool ObjParser::isFloat( const std::string& myString )
	{
		std::istringstream iss( myString );
		float f;
		iss >> std::noskipws >> f;
		return iss.eof( ) && !iss.fail( );
	}

	std::vector< float > ObjParser::splitLineToFloats( std::string& line )
	{
		std::vector< float > values;
		std::vector< std::string > split_ = split( line, ' ' );
		for ( const auto& str : split_ )
		{
			if ( isFloat( str ) )
			{
				values.push_back( std::stod( str ) );
			}
		}
		return values;
	}

	std::string ObjParser::trim( const std::string& str )
	{
		size_t first = str.find_first_not_of( ' ' );
		size_t last = str.find_last_not_of( ' ' );
		return str.substr( first, ( last - first + 1 ) );
	}

	std::vector< int > ObjParser::splitFace( std::string& line )
	{
		std::vector< int > values;
		std::vector< std::string > _splitFace = split( line, '/' );

		for ( std::string& face : _splitFace )
		{
			if ( isNumeric( face ) )
				values.push_back( std::stoi( face ) );
		}
		return values;
	}

	Model ObjParser::loadObj( std::string& filename, bool calculateTangAndBi )
	{
		Model m;
		m.vertices.clear( );
		m.normals.clear( );
		m.texCoords.clear( );
		m.indices.clear( );

		std::vector< float > verts, normals, textures;
		std::map< std::string, int > idxCache;
		int idx = 0;

		std::vector< std::string > lines = split( loadFile( filename ), '\n' );
		for ( auto line : lines )
		{
			auto elems = split( line, ' ' );
			if ( elems.empty( ) ) continue;
			elems.erase( elems.begin( ) );

			std::string type = trim( line.substr( 0, 2 ) );
			if ( type == "v" )
			{
				auto values = splitLineToFloats( line );
				verts.push_back( values[ 0 ] );
				verts.push_back( values[ 1 ] );
				verts.push_back( values[ 2 ] );
			}
			else if ( type == "vn" )
			{
				auto values = splitLineToFloats( line );
				normals.push_back( values[ 0 ] );
				normals.push_back( values[ 1 ] );
				normals.push_back( values[ 2 ] );
			}
			else if ( type == "vt" )
			{
				auto values = splitLineToFloats( line );
				textures.push_back( values[ 0 ] );
				textures.push_back( values[ 1 ] );
			}
			else if ( type == "f" )
			{
				bool quad = false;
				for ( size_t j = 0, size = elems.size( ); j < size; ++j )
				{
					if ( j == 3 && !quad )
					{
						j = 2;
						quad = true;
					}
					if ( idxCache.find( elems[ j ] ) != idxCache.end( ) )
					{
						m.indices.push_back( idxCache[ elems[ j ] ] );
					}
					else
					{
						std::vector< int > vertex = splitFace( elems[ j ] );
						auto v = ( vertex[0] - 1 ) * 3;
						m.vertices.push_back( verts[ v ] );
						m.vertices.push_back( verts[ v + 1 ] );
						m.vertices.push_back( verts[ v + 2 ] );
						if (!textures.empty())
						{
							auto tc = ( vertex[ 1 ] - 1) * 2;
							m.texCoords.push_back( textures[ tc ] );
							m.texCoords.push_back( textures[ tc + 1 ] );
						}
						auto n = ( vertex[ 2 ] - 1 ) * 3;
						m.normals.push_back( normals[ n ] );
						m.normals.push_back( normals[ n + 1] );
						m.normals.push_back( normals[ n + 2] );
						idxCache[ elems[ j ] ] = idx;
						m.indices.push_back( idx );
						++idx;
					}
					if ( j == 3 && quad )
					{
						m.indices.push_back( idxCache[ elems[ 0 ] ] );
					}
				}
			}
		}

		if ( calculateTangAndBi )
		{
			std::vector<std::vector<float>> tangents(m.vertices.size( ) / 3);
			std::vector<std::vector<float>> bitangents(m.vertices.size( ) / 3);

			for (size_t j = 0; j < tangents.size( ); ++j)
			{
				tangents[j] = std::vector<float>(3, 0.0);
				bitangents[j] = std::vector<float>(3, 0.0);
			}

			// Calculate tangents
			for (size_t i = 0; i < m.indices.size( ); i+=3)
			{
				int index = m.indices[i];

				std::vector<float> v0;
				v0.push_back(m.vertices[index*3]);
				v0.push_back(m.vertices[index*3+1]);
				v0.push_back(m.vertices[index*3+2]);
				std::vector<float> uv0;
				uv0.push_back(m.texCoords[index*3]);
				uv0.push_back(m.texCoords[index*3+1]);

				index = m.indices[i+1];

				std::vector<float> v1;
				v1.push_back(m.vertices[index*3]);
				v1.push_back(m.vertices[index*3+1]);
				v1.push_back(m.vertices[index*3+2]);
				std::vector<float> uv1;
				uv1.push_back(m.texCoords[index*3]);
				uv1.push_back(m.texCoords[index*3+1]);

				index = m.indices[i+2];

				std::vector<float> v2;
				v2.push_back(m.vertices[index*3]);
				v2.push_back(m.vertices[index*3+1]);
				v2.push_back(m.vertices[index*3+2]);
				std::vector<float> uv2;
				uv2.push_back(m.texCoords[index*3]);
				uv2.push_back(m.texCoords[index*3+1]);

				std::vector<float> deltaPos1(3);
				std::vector<float> deltaPos2(3);
				for (auto j = 0; j < 3; ++j)
				{
					deltaPos1[j] = v1[j] - v0[j];
					deltaPos2[j] = v2[j] - v0[j];
				}

				std::vector<float> deltaUV1(2);
				std::vector<float> deltaUV2(2);
				for (auto j = 0; j < 2; ++j)
				{
					deltaUV1[j] = uv1[j] - uv0[j];
					deltaUV2[j] = uv2[j] - uv0[j];
				}

				float f = 0.0;
				float aux = ((deltaUV1[0] * deltaUV2[1]) - (deltaUV1[1] * deltaUV2[0]));
				if (aux != 0) f = 1.0 / aux;

				std::vector<float> tangent(3);
				tangent[0] = f * (deltaUV2[1] * deltaPos1[0] - deltaUV1[1] * deltaPos2[0]);
				tangent[1] = f * (deltaUV2[1] * deltaPos1[1] - deltaUV1[1] * deltaPos2[1]);
				tangent[2] = f * (deltaUV2[1] * deltaPos1[2] - deltaUV1[1] * deltaPos2[2]);

				float normalize = sqrt((tangent[0] * tangent[0]) +
						(tangent[1] * tangent[1]) + (tangent[2] * tangent[2]));

				if (normalize != 0)
				{
					for (auto j = 0; j < 3; ++j)
					{
						tangent[j] /= normalize;
					}
				}

				std::vector<float> bitangent(3);
				bitangent[0] = f * (-deltaUV2[0] * deltaPos1[0] + deltaUV1[0] * deltaPos2[0]);
				bitangent[1] = f * (-deltaUV2[0] * deltaPos1[1] + deltaUV1[0] * deltaPos2[1]);
				bitangent[2] = f * (-deltaUV2[0] * deltaPos1[2] + deltaUV1[0] * deltaPos2[2]);

				normalize = sqrt((bitangent[0] * bitangent[0]) +
						(bitangent[1] * bitangent[1]) + (bitangent[2] * bitangent[2]));

				if (normalize != 0)
					{
					for (auto j = 0; j < 3; ++j)
					{
						bitangent[j] /= normalize;
					}
				}

				// Average the value of the vector outs
				for (auto v = 0; v < 3; ++v)
				{
					int addTo = m.indices[i+v];
					for (auto j = 0; j < 3; ++j)
					{
						tangents[addTo][j] += tangent[j];
						bitangents[addTo][j] += bitangent[j];
					}
				}
			}

			for (size_t j = 0; j < tangents.size( ); ++j)
			{
				for (auto k = 0; k < 3; ++k)
				{
					m.tangents.push_back(tangents[j][k]);
					m.bitangents.push_back(bitangents[j][k]);
				}
			}

			tangents.clear( );
			bitangents.clear( );
		}
		
		return m;
	}
};