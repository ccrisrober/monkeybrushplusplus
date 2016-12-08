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
    Query()
    {
      glCreateQueries(1, 1, &_handler);
    }
    MB_API
    virtual ~Query()
    {
      glDeleteQueries(1, &_handler);
    }
    MB_API
    void begin(unsigned int target)
    {
      glBeginQuery(target, _handler);
    }
    MB_API
    void end(unsigned int target)
    {
      glEndQuery(target);
    }
    MB_API
    void useAnySamples(const std::function<void()>& cb)
    {
      oneUse(GL_ANY_SAMPLES_PASSED, cb);
    }
    MB_API
    void useAnySamplesConservative(const std::function<void()>& cb)
    {
      oneUse(GL_ANY_SAMPLES_PASSED_CONSERVATIVE, cb);
    }
    MB_API
    void oneUse(unsigned int target, const std::function<void()>& cb)
    {
      begin(target);
      cb();
      end(target);
    }
    // TODO: Need to be a boolean
    MB_API
    unsigned int isResultAvailable()
    {
      unsigned int value = 0;
      //glGetQueryObject(_handler, GL_QUERY_RESULT_AVAILABLE, value);
      return value;
    }
    MB_API
    unsigned int getResult()
    {
      unsigned int value = 0;
      //glGetQueryObject(_handler, GL_QUERY_RESULT, value);
      return value;
    }
    protected:
      unsigned int _handler;
	};
}

#endif /* __MB_QUERY__ */
