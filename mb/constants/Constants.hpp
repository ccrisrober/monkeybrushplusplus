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

#ifndef __MB_CONSTANTS__
#define __MB_CONSTANTS__

#include "../Includes.hpp"

namespace MB
{
	namespace ctes
	{
        enum class ClearBuffer
		{
            DepthBuffer   = GL_DEPTH_BUFFER_BIT,
            StencilBuffer = GL_STENCIL_BUFFER_BIT,
            ColorBuffer   = GL_COLOR_BUFFER_BIT
		};

		enum class RenderMode
		{
			Points = GL_POINTS,
			Lines = GL_LINES,
			LineLoop = GL_LINE_LOOP,
			LineStrip = GL_LINE_STRIP,
			Triangles = GL_TRIANGLES,
			TriangleStrip = GL_TRIANGLE_STRIP,
			TriangleFan = GL_TRIANGLE_FAN
		};

		enum class BlendingMode
		{
			Zero = GL_ZERO,
			One = GL_ONE,
			SrcColor = GL_SRC_COLOR
		};

		enum class BlendingEq
		{
			Add = GL_ADD,
			Substract = GL_SUBTRACT,
			RevSubstract = GL_FUNC_REVERSE_SUBTRACT,
			Min = GL_MIN,
			Max = GL_MAX
		};

		enum class BufferType
		{
			Array = GL_ARRAY_BUFFER,
			ElementArray = GL_ELEMENT_ARRAY_BUFFER,
			TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
			Uniform = GL_UNIFORM_BUFFER,
			PixelPack = GL_PIXEL_PACK_BUFFER,
			PixelUnpack = GL_PIXEL_UNPACK_BUFFER,
			CopyRead = GL_COPY_READ_BUFFER,
			CopyWrite = GL_COPY_WRITE_BUFFER
		};

		enum class FaceSide
		{
			Front = GL_FRONT,
			Back = GL_BACK,
			FrontAndBack = GL_FRONT_AND_BACK
		};



		enum class FaceDir
		{
			Clockwise = GL_CW,
			InvClockwise = GL_CCW
		};









		enum class TFMode
		{
			Interleaved = GL_INTERLEAVED_ATTRIBS,
			Separate = GL_SEPARATE_ATTRIBS
        };
		enum class TFPrimitive
		{
			Points = GL_POINTS,
			Lines = GL_LINES,
			Triangles = GL_TRIANGLES
		};
		enum class TFTarget
		{
			TransformFeedback = GL_TRANSFORM_FEEDBACK
		};


        enum class MouseButton
		{
			Left = 0,
			Middle = 1,
			Right = 2
        };
	}
}

#endif /* __MB_CONSTANTS__ */