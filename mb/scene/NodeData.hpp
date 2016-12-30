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

#ifndef __MB_NODEDATA__
#define __MB_NODEDATA__

#include <mb/api.h>

#include <unordered_map>

#include "Node.hpp"
#include "../utils/any.hpp"

namespace mb
{
	class NodeData: public Node
	{
	public:
		MB_API
		NodeData( const std::string& name, const std::string& tag = "Untagged" );
		MB_API
		void insertData( const std::string& name, const mb::any& data );
    MB_API
		mb::any getData( const std::string& name );
    MB_API
		bool removeData( const std::string& name );
	protected:
		std::unordered_map<std::string, mb::any> _userData;
	};
}

#endif /* __MB_NODEDATA__ */
