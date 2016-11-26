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

#ifndef __MB__LAYER__
#define __MB__LAYER__

#include <mb/api.h>

#include <array>

namespace MB
{
	class Layer
	{
	public:
		MB_API
		Layer();
		MB_API
		void set(const int& channel);
		MB_API
		void enable(const int& channel);
		MB_API
		void toggle(const int& channel);
		MB_API
		void disable(const int& channel);
		MB_API
		bool check(const Layer& layer2) const;
		MB_API
		bool check(const int& channel) const;
	protected:
		int _mask;
	};

	class LayerLookup
	{
	public:
		MB_API
		static std::string name(const int& channel);
		MB_API
		static void name(const std::string name, const int& index);
	protected:
		static std::array<std::string, 32> _names;
		static bool _initialized;

		static void initialize();
	};
}

#endif /* __MB__LAYER__ */
