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

#include "Query.hpp"

namespace mb
{
  Query::Query( void )
  {
    glCreateQueries(1, 1, &_handler);
  }
  Query::~Query( void )
  {
    glDeleteQueries(1, &_handler);
  }
  void Query::begin(unsigned int target)
  {
    glBeginQuery(target, _handler);
  }
  void Query::end(unsigned int target)
  {
    glEndQuery(target);
  }
  void Query::useAnySamples(const std::function<void()>& cb)
  {
    oneUse(GL_ANY_SAMPLES_PASSED, cb);
  }
  void Query::useAnySamplesConservative(const std::function<void()>& cb)
  {
    oneUse(GL_ANY_SAMPLES_PASSED_CONSERVATIVE, cb);
  }
  void Query::oneUse(unsigned int target, const std::function<void()>& cb)
  {
    begin(target);
    cb();
    end(target);
  }
  bool Query::isResultAvailable( void )
  {
    int value = 0;
    glGetQueryObjectiv(_handler, GL_QUERY_RESULT_AVAILABLE, &value);
    return value > 0;
  }
  unsigned int Query::getResult( void )
  {
    GLuint64 value = 0;
    glGetQueryObjectui64v(_handler, GL_QUERY_RESULT, &value);
    return value;
  }
}

