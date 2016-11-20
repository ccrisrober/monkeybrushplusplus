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

#ifndef __MB__DISC__
#define __MB__DISC__

#include "Drawable.hpp"
#include "../core/BufferAttribute.hpp"

namespace MB
{
    class Disc: public Drawable
    {
    public:
		Disc(float radius, unsigned int divisions, unsigned int stacks = 1,
			float innerRadius = 0.0f, float stackInc = 0.0f)
			: Drawable()
        {
			if (divisions < 3)
			{
				throw("divisions must be 3 or greater");
			}

			unsigned int nv = (1 + stacks) * (1 + divisions);

			BufferAttribute verts(std::vector<float>(3 * nv), 3);
			BufferAttribute norms(std::vector<float>(3 * nv), 3);
			BufferAttribute texCoords(std::vector<float>(2 * nv), 2);
			std::vector<unsigned int> cells(3 * stacks * divisions * 2);

			unsigned int idx = 0;
			auto radiusSpan = radius - innerRadius;
			unsigned int pointsPerStack = divisions + 1;

			unsigned int NVIDX = 0;
			unsigned int NNIDX = 0;
			unsigned int NTIDX = 0;
			unsigned int ii = 0;

			for (unsigned int stack = 0; stack <= stacks; ++stack)
			{
				auto stackRadius = innerRadius + radiusSpan * std::pow(stack / stacks, stackInc);

				for (unsigned int i = 0; i <= divisions; ++i)
				{
					auto theta = 2.0f * Mathf::PI * i / divisions;

					verts.setXYZ(NVIDX++, stackRadius * std::cos(theta), 0.0f, stackRadius * std::sin(theta));
					norms.setXYZ(NNIDX++, 0.0f, 1.0f, 0.0f);
					texCoords.setXY(NTIDX++, 1.0f - (i / divisions), stack / stacks);

					if (stack > 0 && i != divisions)
					{
						unsigned int a = idx + (i + 1);
						unsigned int b = idx + i;
						unsigned int c = idx + i - pointsPerStack;
						unsigned int d = idx + (i + 1) - pointsPerStack;

						// Create two triangles (quad)
						cells[ii++] = a;
						cells[ii++] = b;
						cells[ii++] = c;

						cells[ii++] = a;
						cells[ii++] = c;
						cells[ii++] = d;
					}
				}

				idx += divisions + 1;
			}


			_vao = new VertexArray();
			_vao->bind();

			addBufferArray(0, verts.array(), 3, GL_STATIC_DRAW);
			addBufferArray(1, norms.array(), 3, GL_STATIC_DRAW);
			addBufferArray(2, texCoords.array(), 2, GL_STATIC_DRAW);

			std::vector<unsigned int> data = cells;
			unsigned int type = GL_STATIC_DRAW;

			VertexBuffer vbIndices(GL_ELEMENT_ARRAY_BUFFER);
			vbIndices.data(data, type);
			_indicesLen = data.size();
			this->_handle.push_back(vbIndices);

			_vao->unbind();
        }
    };
}

#endif /* __MB__DISC__ */
