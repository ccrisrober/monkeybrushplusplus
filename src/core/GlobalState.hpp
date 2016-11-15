/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal
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

namespace MB {
    class CullingState {

    };
    class DepthState {

    };
    class ColorState {
        public:

        void setClear(float r, float g, float b, float a)
        {
            this->setClear(Color4(r, g, b, a));
        }
        void setClear(const Color4& bgColor)
        {
            glClearColor(bgColor.r(), bgColor.g(), bgColor.b(), bgColor.a());
        }
    };
    class ScissorsState {

    };
    class StencilState {

    };
    class BlendingState {

    };
	class GlobalState {
    public:
        GlobalState()
        {
            this->color.setClear(0.0f, 0.0f, 0.0f, 1.0f);
            this->depth.setClear(1.0f);
            this->stencil.setClear(0.0f);

            this->depth.setStatus(true);
            //this->depth.setFunc(MB.ctes.ComparisonFunc.LessEqual);

            this->culling.setFlipSided(MB.ctes.FaceDir.InvClockwise);
            //this->culling.setMode(MB.ctes.FaceSide.Back);
            this->culling.setStatus(true);

            //this.blending.set(MB.ctes.BlendingMode2.Normal);
        }

        DepthState depth;
        CullingState culling;
        ColorState color;
        StencilState stencil;
        BlendingState blending;
	};
}

#endif /* __MB_GLOBAL_STATE__ */
