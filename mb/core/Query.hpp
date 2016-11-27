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

#ifndef __MB_QUERY__
#define __MB_QUERY__

#include "../Includes.hpp"
#include <functional>

namespace mb
{
	class Query
	{
	public:
        Query()
        {
            glCreateQueries(1, 1, &_handler);
        }
        virtual ~Query()
        {
            glDeleteQueries(1, &_handler);
        }
        void begin(unsigned int target)
        {
            glBeginQuery(target, _handler);
        }
        void end(unsigned int target)
        {
            glEndQuery(target);
        }
        void useAnySamples(const std::function<void()>& cb)
        {
            oneUse(GL_ANY_SAMPLES_PASSED, cb);
        }
        void useAnySamplesConservative(const std::function<void()>& cb)
        {
            oneUse(GL_ANY_SAMPLES_PASSED_CONSERVATIVE, cb);
        }
        void oneUse(unsigned int target, const std::function<void()>& cb)
        {
            begin(target);
            cb();
            end(target);
        }
        // TODO: Need to be a boolean
        unsigned int isResultAvailable()
        {
            unsigned int value = 0;
            //glGetQueryObject(_handler, GL_QUERY_RESULT_AVAILABLE, value);
            return value;
        }
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
