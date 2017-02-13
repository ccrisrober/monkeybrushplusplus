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

#ifndef __MB_GLOBAL_STATE__
#define __MB_GLOBAL_STATE__

#include "../core/Color4.hpp"
#include "../maths/Vect4.hpp"

#include "../Includes.hpp"

namespace mb
{
  class CullingState
  {
  public:
    void setStatus(const bool enabled);
    void setFlipSided(unsigned int flipSide);
  protected:
    unsigned int _currentFrontFace;
    bool _cullingEnabled = false;
    unsigned int _cullingFaceMode;
  };
  class DepthState
  {
  public:
    void setFunc(unsigned int depthFunc);
    void setStatus(const bool enabled);
    void setMask(const bool mask);
    void setClear(float depth);
    void clearBuffer();
    void depthRange(float znear = 0.0f, float zfar = 1.0f);
  protected:
    bool _depthEnabled = false;
  };
  class ColorState
  {
  public:
    void setMask(float r, float g, float b, float a);
    void setMask(const Color4& bgColor);
    void setClear(float r, float g, float b, float a);
    void setClear(const Color4& bgColor);
    void clearBuffer();
  };
  class ScissorsState
  {
  public:
    void setStatus(const bool enabled);
    void setRectangle(float x, float y, float w, float h);
  };
  class StencilState
  {
  public:
    void setStatus(const bool enabled);
    void setMaskValue(unsigned int mask);
    void setFunc(unsigned int compFun, unsigned int ref, unsigned int mask);
    void setOp(unsigned int fail, unsigned int zfail, unsigned int zpass);
    void setClear(int s);
  };
  class BlendingState
  {
  public:
    void setStatus(const bool enabled);
    void setEquation(unsigned int mode);
    void setEquationSeparate(unsigned int modeRGB, unsigned int modeAlpha);
    void setColor(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f);
  };
  class GlobalState
  {
  public:
    GlobalState();
    void setViewport(const Vect4& vp);
    float getLineWidth() const;
    void setLineWidth(float width);
    unsigned int getPolygonMode() const;
    void setPolygonMode(unsigned int mode);

    DepthState depth;
    CullingState culling;
    ColorState color;
    StencilState stencil;
    BlendingState blending;

  protected:
    unsigned int _polygonMode = -1;
    float _lineWidth = 1.0f;
  };
}

#endif /* __MB_GLOBAL_STATE__ */
