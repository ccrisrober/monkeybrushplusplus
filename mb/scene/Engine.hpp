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

#ifndef __MB_ENGINE__
#define __MB_ENGINE__

#include <mb/api.h>

#include <iostream>
#include <functional>
#include "../core/GLContext.hpp"
#include "../maths/Vect4.hpp"

namespace MB
{
	class Engine
	{
	public:
		MB_API
		Engine(GLContext* context, bool debugLayer = true);
		MB_API
		void run(std::function<void(float)> loop);
		MB_API
		void close();
		MB_API
        void setViewport(const Vect4& vp)
		{
			this->_context->state()->setViewport(vp);
		}
		MB_API
		GlobalState * state()
		{
			return this->_context->state();
		}
    private:
		double calcFPS(double theTimeInterval = 1.0f);
	protected:
        GLContext* _context;
        float deltaTime;
        float lastFrame;
		bool _debugLayer;

        double currentTime;
	};
}

#endif /* __MB_ENGINE__ */
