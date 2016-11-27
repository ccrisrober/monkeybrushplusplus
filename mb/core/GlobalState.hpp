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
		void setStatus(const bool enabled)
		{
			if (_cullingEnabled == enabled)
				return;
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
		void setFlipSided(unsigned int flipSide)
		{
			glFrontFace(flipSide);
		}
	protected:
		unsigned int _currentFrontFace;
		bool _cullingEnabled = false;
		unsigned int _cullingFaceMode;
    };
    class DepthState
    {
	public:
		void setFunc(unsigned int depthFunc)
		{
			glDepthFunc(depthFunc);
		}
		void setStatus(const bool enabled)
		{
			if (_depthEnabled == enabled)
				return;
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
		void setMask(const bool mask)
		{
			glDepthMask(mask);
		}
		void setClear(float depth)
		{
			glClearDepth(depth);
		}
		void clearBuffer()
		{
			glClear(GL_DEPTH_BUFFER_BIT);
		}
		void depthRange(float znear = 0.0f, float zfar = 1.0f)
		{
			glDepthRange(znear, zfar);
		}
	protected:
		bool _depthEnabled = false;
    };
    class ColorState
    {
	public:
		void setMask(float r, float g, float b, float a)
		{
			this->setMask(Color4(r, g, b, a));
		}
		void setMask(const Color4& bgColor)
		{
			glColorMask(bgColor.r(), bgColor.g(), bgColor.b(), bgColor.a());
		}
        void setClear(float r, float g, float b, float a)
        {
            this->setClear(Color4(r, g, b, a));
        }
        void setClear(const Color4& bgColor)
        {
            glClearColor(bgColor.r(), bgColor.g(), bgColor.b(), bgColor.a());
        }
		void clearBuffer()
		{
			glClear(GL_COLOR_BUFFER_BIT);
		}
    };
    class ScissorsState
    {
	public:
		void setStatus(const bool enabled)
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
		void setRectangle(float x, float y, float w, float h)
		{
			glScissor(x, y, w, h);
		}
    };
    class StencilState
    {
	public:
		void setStatus(const bool enabled)
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
		void setMaskValue(unsigned int mask)
		{
			glStencilMask(mask);
		}
		void setFunc(unsigned int compFun, unsigned int ref, unsigned int mask)
		{
			glStencilFunc(compFun, ref, mask);
		}
		void setOp(unsigned int fail, unsigned int zfail, unsigned int zpass)
		{
			glStencilOp(fail, zfail, zpass);
		}
		void setClear(int s)
		{
			glClearStencil(s);
		}
    };
    class BlendingState
    {
	public:
		void setStatus(const bool enabled)
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
		void setEquation(unsigned int mode)
		{
			glBlendEquation(mode);
		}
		void setEquationSeparate(unsigned int modeRGB, unsigned int modeAlpha)
		{
			glBlendEquationSeparate(modeRGB, modeAlpha);
		}
		void setColor(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f)
		{
			glBlendColor(r, g, b, a);
		}
    };
	class GlobalState
    {
    public:
        GlobalState()
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

		void setViewport(const Vect4& vp)
		{
			glViewport(vp.x(), vp.y(), vp.z(), vp.w());
		}
		float getLineWidth() const
		{
			return this->_lineWidth;
		}
		void setLineWidth(float width)
		{
			if (width == _lineWidth)
				return;
			glLineWidth(width);
			_lineWidth = width;
		}
		unsigned int getPolygonMode() const
		{
			return this->_polygonMode;
		}
		void setPolygonMode(unsigned int mode)
		{
			if (mode == _polygonMode)
				return;
			glPolygonMode(GL_FRONT_AND_BACK, mode);
			_polygonMode = mode;
		}

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
