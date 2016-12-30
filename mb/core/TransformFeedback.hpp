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

#ifndef __MB__TRANSFORM_FEEDBACK__
#define __MB__TRANSFORM_FEEDBACK__

#include <mb/api.h>
#include "Program.hpp"
#include <vector>

namespace mb
{
  class TransformFeedback
  {
  public:
    MB_API
    TransformFeedback( void );
    MB_API
    virtual ~TransformFeedback( void );
    /**
    * Bind this TransformFeedback object to current GL state.
    */
    MB_API
    void bind( void );
    /**
    * Unbind this TransformFeedback object to current GL state.
    */
    MB_API
    void unbind( void );
    /**
    * Init TransformFeedback operation using given mode.
    * @param {MB.ctes.TFPrimitive} mode TransformFeedback mode.
    */
    MB_API
    void begin(unsigned int mode);
    /**
    * Init TransformFeedback operation using point mode.
    */
    MB_API
    void beginPoints( void );
    /**
    * Init TransformFeedback operation using line mode.
    */
    MB_API
    void beginLines( void );
    /**
    * Init TransformFeedback operation using triangle mode.
    */
    MB_API
    void beginTriangles( void );
    /**
    * Finish TransformFeedback operation.
    */
    MB_API
    void end( void );
    /**
    * Pause TransformFeedback operation.
    */
    MB_API
    void pause( void );
    /**
    * Resume TransformFeedback operation.
    */
    MB_API
    void resume( void );
    MB_API
    static void varyings(const mb::Program* prog,
      const std::vector<const char*>& varyings, unsigned int bufferMode);
    MB_API
    std::vector<float> extractData(unsigned int numElems) const;
  protected:
    unsigned int _handler;
  };
}

#endif /* __MB__TRANSFORM_FEEDBACK__ */
