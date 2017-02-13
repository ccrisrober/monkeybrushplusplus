/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus
 * <https://github.com/maldicion069/monkeybrushplusplus>
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

#ifndef __MB_OBJPARSER__
#define __MB_OBJPARSER__

#include <mb/api.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>

namespace mb
{
  struct Model
  {
    std::vector< float > vertices;
    std::vector< float > normals;
    std::vector< unsigned int > indices;
    std::vector< float > texCoords;
    std::vector< float > tangents;
    std::vector< float > bitangents;
  };
  class ObjParser
  {
  public:
    /**
     * ObjParser constructor
     */
    MB_API
    ObjParser( void );
    /**
     * Load new obj file
     * @param filename: Wavefront OBJ file route.
     * @param calculateTangAndBi: Calculate tangents and
     *   bitangents for object.
     * @return Model object with parsed values.
     */
    MB_API
    Model loadObj( const std::string& filename, bool calculateTangAndBi = false );
  protected:
    /*
      Load all file content
      @param std::string filename
      @return std::string
    */
    std::string loadFile( const std::string& filename );
    /*
      Split string by character separator
      @param string line
      @param char c
      @return std::vector<std::string>
    */
    std::vector< std::string > split( const std::string& s, char c );
    bool isNumeric( const std::string& input );
    bool isFloat( const std::string& myString );
    std::vector< float > splitLineToFloats( std::string& line );
    std::string trim( const std::string& str );
    std::vector< unsigned int > splitFace( std::string& line );
  };
}

#endif /* __MB_OBJPARSER__ */
