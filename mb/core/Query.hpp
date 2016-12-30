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

#ifndef __MB_QUERY__
#define __MB_QUERY__

#include "../Includes.hpp"
#include <functional>

namespace mb
{
	class Query
	{
	public:
    MB_API
    Query( void );
    MB_API
    virtual ~Query( void );
    MB_API
    void begin(unsigned int target);
    MB_API
    void end(unsigned int target);
    MB_API
    void useAnySamples(const std::function<void()>& cb);
    MB_API
    void useAnySamplesConservative(const std::function<void()>& cb);
    MB_API
    void oneUse(unsigned int target, const std::function<void()>& cb);
    MB_API
    bool isResultAvailable( void );
    MB_API
    unsigned int getResult( void );
    protected:
      unsigned int _handler;
	};
}

#endif /* __MB_QUERY__ */
