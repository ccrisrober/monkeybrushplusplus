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

#include "GlobalState.hpp"

namespace mb
{
  void CullingState::setStatus(const bool enabled)
  {
    if (_cullingEnabled == enabled)
    {
      return;
    }
    if (enabled)
    {
      glEnable(GL_CULL_FACE);
    }
    else
    {
      glDisable(GL_CULL_FACE);
    }
    _cullingEnabled = enabled;
  }
  void CullingState::setFlipSided(unsigned int flipSide)
  {
    glFrontFace(flipSide);
  }

  void DepthState::setFunc(unsigned int depthFunc)
  {
    glDepthFunc(depthFunc);
  }
  void DepthState::setStatus(const bool enabled)
  {
    if (_depthEnabled == enabled)
    {
      return;
    }
    if (enabled)
    {
      glEnable(GL_DEPTH_TEST);
    }
    else
    {
      glDisable(GL_DEPTH_TEST);
    }
    _depthEnabled = enabled;
  }
  void DepthState::setMask(const bool mask)
  {
    glDepthMask(mask);
  }
  void DepthState::setClear(float depth)
  {
    glClearDepth(depth);
  }
  void DepthState::clearBuffer()
  {
    glClear(GL_DEPTH_BUFFER_BIT);
  }
  void DepthState::depthRange(float znear, float zfar)
  {
    glDepthRange(znear, zfar);
  }

  void ColorState::setMask(float r, float g, float b, float a)
  {
    this->setMask(Color4(r, g, b, a));
  }
  void ColorState::setMask(const Color4& bgColor)
  {
    glColorMask(bgColor.r(), bgColor.g(), bgColor.b(), bgColor.a());
  }
  void ColorState::setClear(float r, float g, float b, float a)
  {
    this->setClear(Color4(r, g, b, a));
  }
  void ColorState::setClear(const Color4& bgColor)
  {
    glClearColor(bgColor.r(), bgColor.g(), bgColor.b(), bgColor.a());
  }
  void ColorState::clearBuffer()
  {
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void ScissorsState::setStatus(const bool enabled)
  {
    if (enabled)
    {
      glEnable(GL_SCISSOR_TEST);
    }
    else
    {
      glDisable(GL_SCISSOR_TEST);
    }
  }
  void ScissorsState::setRectangle(float x, float y, float w, float h)
  {
    glScissor(x, y, w, h);
  }

  void StencilState::setStatus(const bool enabled)
  {
    if (enabled)
    {
      glEnable(GL_STENCIL_TEST);
    }
    else
    {
      glDisable(GL_STENCIL_TEST);
    }
  }
  void StencilState::setMaskValue(unsigned int mask)
  {
    glStencilMask(mask);
  }
  void StencilState::setFunc(unsigned int compFun, unsigned int ref, unsigned int mask)
  {
    glStencilFunc(compFun, ref, mask);
  }
  void StencilState::setOp(unsigned int fail, unsigned int zfail, unsigned int zpass)
  {
    glStencilOp(fail, zfail, zpass);
  }
  void StencilState::setClear(int s)
  {
    glClearStencil(s);
  }

  void BlendingState::setStatus(const bool enabled)
  {
    if (enabled)
    {
      glEnable(GL_BLEND);
    }
    else
    {
      glDisable(GL_BLEND);
    }
  }
  void BlendingState::setEquation(unsigned int mode)
  {
    glBlendEquation(mode);
  }
  void BlendingState::setEquationSeparate(unsigned int modeRGB, unsigned int modeAlpha)
  {
    glBlendEquationSeparate(modeRGB, modeAlpha);
  }
  void BlendingState::setColor(float r, float g, float b, float a)
  {
    glBlendColor(r, g, b, a);
  }

  GlobalState::GlobalState()
  {
    this->color.setClear(0.0f, 0.0f, 0.0f, 1.0f);
    this->depth.setClear(1.0f);
    this->stencil.setClear(0.0f);

    this->depth.setStatus(true);
    this->depth.setFunc(GL_LEQUAL);

    this->culling.setFlipSided(GL_CCW);
    //this->culling.setMode(MB.ctes.FaceSide.Back);
    this->culling.setStatus(true);

    //this.blending.set(MB.ctes.BlendingMode2.Normal);
  }
  void GlobalState::setViewport(const Vect4& vp)
  {
    glViewport(vp.x(), vp.y(), vp.z(), vp.w());
  }
  float GlobalState::getLineWidth() const
  {
    return this->_lineWidth;
  }
  void GlobalState::setLineWidth(float width)
  {
    if (width == _lineWidth)
      return;
    glLineWidth(width);
    _lineWidth = width;
  }
  unsigned int GlobalState::getPolygonMode() const
  {
    return this->_polygonMode;
  }
  void GlobalState::setPolygonMode(unsigned int mode)
  {
    if (mode == _polygonMode)
      return;
    glPolygonMode(GL_FRONT_AND_BACK, mode);
    _polygonMode = mode;
  }
}
