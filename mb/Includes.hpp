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

#ifndef __MB_INCLUDES__
#define __MB_INCLUDES__

#include <iostream>
#include "core/Log.hpp"

#ifndef SKIP_GLEW_INCLUDE
	#include <GL/glew.h>
#endif

#define SKIP_GLEW_INCLUDE 1

#ifdef Darwin
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#include <GLFW/glfw3.h>

#include <memory>

#include "others/Exception.hpp"

#endif /* __MB_INCLUDES__ */
