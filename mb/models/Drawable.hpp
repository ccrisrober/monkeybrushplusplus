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

#ifndef __MB_DRAWABLE__
#define __MB_DRAWABLE__

#include <mb/api.h>

#include "../Includes.hpp"
#include "../core/VertexArray.hpp"
#include "../core/VertexBuffer.hpp"

#include "../maths/Box3D.hpp"
#include "../maths/Sphere3D.hpp"

#include <algorithm>

namespace mb
{
    class Drawable
    {
    public:
    	MB_API
    	virtual ~Drawable() {}
        MB_API
        void render(unsigned int mode);
        MB_API
        unsigned int indicesLen() const;
		MB_API
		unsigned int verticesLen() const;

		virtual void configure() {};

		MB_API
		void computeBoundingSphere(const std::vector<float>& arr)
		{
			auto box = Box3D::createFromValues(arr);
			auto center = box.center();

			auto maxRadiusSquared = 0.0f;
			Vect3 v;
			// Trying to find a boundingSphere with a radius smaller that the boundingSphere of the box
			for (unsigned int i = 0, il = arr.size(); i < il; i+=3)
			{
				v.set(arr[i], arr[i + 1], arr[i + 2]);
				maxRadiusSquared = std::max(maxRadiusSquared, center.distanceToSquared(v));
			}

			boundingSphere = Sphere3D(center, maxRadiusSquared);
		}

		VertexArray* vertexArray() const
		{
			return _vao;
		}
		Sphere3D boundingSphere;
    protected:
        Drawable();
		unsigned int _numVertices;
		unsigned int _indicesLen;
		std::vector<VertexBuffer> _handle;
		VertexArray* _vao;
        void addBufferArray(unsigned int attribLocation, const std::vector<float>& data,
            unsigned int numElems, unsigned int type = GL_STATIC_DRAW);
    };
}

#endif /* __MB_DRAWABLE__ */
