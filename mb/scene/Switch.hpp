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

#ifndef __MB_SWITCH__
#define __MB_SWITCH__

#include <mb/api.h>

#include "Group.hpp"

namespace mb
{
	class Switch: public Group
	{
	public:
        MB_API
        Switch( const std::string& name, const std::string& tag = "Untagged" );
		MB_API
		virtual ~Switch( void );
		MB_API
		NodePtr getCurrentNode( void );
		MB_API
        int getCurrentNodeIndex( void ) const;
		MB_API
        void setCurrentNodeIndex( int index );
		MB_API
        void selectNextNode( void );
		MB_API
        void selectPrevNode( void );
    private:
        int _currentIdx = 0;
	};
}

#endif /* __MB_SWITCH__ */
