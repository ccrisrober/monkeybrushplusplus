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

#ifndef __MB_CUSTOM_PING_PONG__
#define __MB_CUSTOM_PING_PONG__

#include <mb/api.h>

#include <functional>

namespace mb
{
  template <class T>
  class CustomPingPong
  {
  public:
    CustomPingPong( const T & elem1, const T & elem2 );
    void swap( void );
    void swap( std::function<void()> cb );
    T first( void ) const;
    T last( void ) const;
  protected:
    T _elem1;
    T _elem2;
  };
}

#include "CustomPingPong.inl"

#endif /* __MB_CUSTOM_PING_PONG__ */
