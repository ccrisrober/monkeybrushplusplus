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

#include "utils.hpp"
#include <algorithm>

namespace mb
{
	namespace utils
	{
		std::string generateUUID()
		{
			char GUID[40];
			int t = 0;
			std::string szTemp = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx";
			std::string szHex = "0123456789ABCDEF-";
			int nLen = szTemp.size();

			for (t = 0; t<nLen + 1; t++)
			{
				int r = rand() % 16;
				char c = ' ';

				switch (szTemp[t])
				{
  				case 'x': { c = szHex[r]; } break;
  				case 'y': { c = szHex[(r & 0x03) | 0x08]; } break;
  				case '-': { c = '-'; } break;
  				case '4': { c = '4'; } break;
				}

				GUID[t] = (t < nLen) ? c : 0x00;
			}

			return std::string(GUID);
		};
	}
}
