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

#include "TransformFeedback.hpp"
#include "../Includes.hpp"

namespace mb
{
  TransformFeedback::TransformFeedback( void )
  {
    glCreateTransformFeedbacks(1, &_handler);
  }
  TransformFeedback::~TransformFeedback( void )
  {
    glDeleteTransformFeedbacks(1, &_handler);
  }
  void TransformFeedback::bind( void )
  {
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, _handler);
  }
  void TransformFeedback::unbind( void )
  {
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
  }
  void TransformFeedback::begin(unsigned int mode)
  {
    glBeginTransformFeedback(mode);
  }
  void TransformFeedback::beginPoints( void )
  {
    begin(GL_POINTS);
  }
  void TransformFeedback::beginLines( void )
  {
    begin(GL_LINES);
  }
  void TransformFeedback::beginTriangles( void )
  {
    begin(GL_TRIANGLES);
  }
  void TransformFeedback::end( void )
  {
    glEndTransformFeedback();
  }
  void TransformFeedback::pause( void )
  {
    glPauseTransformFeedback();
  }
  void TransformFeedback::resume( void )
  {
    glResumeTransformFeedback();
  }
  void TransformFeedback::varyings(const mb::Program* prog,
    const std::vector<const char*>& varyings, unsigned int bufferMode)
  {
    glTransformFeedbackVaryings(prog->program(),
      varyings.size(), &varyings[0], bufferMode);
  }
  std::vector<float> TransformFeedback::extractData(unsigned int numElems) const
  {
    std::vector<float> feedback(numElems);
    glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0,
      sizeof(feedback), &feedback[0]);
    return feedback;
  }
}
