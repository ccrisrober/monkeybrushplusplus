/*
 * Copyright (c) 2017 maldicion069
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

#include "Switch.hpp"

namespace mb
{
    Switch::Switch( const std::string& name, const std::string& tag )
	: Group(name, tag) {}
	Switch::~Switch( void ) {}
	NodePtr Switch::getCurrentNode( void ) { return getChild( _currentIdx ); }
    int Switch::getCurrentNodeIndex( void ) const { return _currentIdx; }
    void Switch::setCurrentNodeIndex( int index ) { _currentIdx = index; }
    void Switch::selectNextNode( void )
    {
    	if ( !hasNodes( ) )
    	{
    		return;
    	}
    	auto nodeCount = getNumChildren( );
    	_currentIdx = ( _currentIdx + 1 ) % nodeCount;
    }
    void Switch::selectPrevNode( void )
    {
    	if ( !hasNodes( ) )
    	{
    		return;
    	}
    	auto nodeCount = getNumChildren( );
		_currentIdx = ( _currentIdx + nodeCount - 1 ) % nodeCount;
    }
}
