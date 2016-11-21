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

#ifndef __MB_CAPSULE__
#define __MB_CAPSULE__

#include <mb/api.h>

#include <functional>
#include "Drawable.hpp"
#include "../maths/Mathf.hpp"
#include "../core/BufferAttribute.hpp"

namespace MB
{
    class Capsule: public Drawable
    {
    public:
		MB_API
        Capsule(float radius = 0.5f, float height = 1.0f,
            unsigned int subHeight = 12, unsigned int numSegm = 12)
        : Drawable()
        {
			unsigned int ringsBody = subHeight + 1;
			unsigned int ringsTotal = subHeight + ringsBody;

			float bodyIncr = 1.0f / (ringsBody - 1);
			float ringIncr = 1.0f / (subHeight - 1);
			float nv = ((std::round(subHeight / 2) * numSegm) +
				(ringsBody * numSegm) + std::round(subHeight / 2) * numSegm);

			BufferAttribute verts(std::vector<float>(3 * nv), 3);
			BufferAttribute norms(std::vector<float>(3 * nv), 3);
			BufferAttribute texCoords(std::vector<float>(2 * nv), 2);

			std::vector<unsigned int> cells((ringsTotal - 1) * (numSegm - 1) * 2 * 3);

			unsigned int NVIDX = 0;
			unsigned int NNIDX = 0;
			unsigned int NTIDX = 0;
		
			std::function<void(unsigned int, float, float, float)> calcNewRing([&](unsigned int segments, float r_, float y, float dy)
			{
				float segIncr = 1.0f / (segments - 1);

				for (unsigned int s = 0; s < segments; ++s)
				{
					float val = (Mathf::PI * 2.0f) * s * segIncr;
					float x = std::cos(val) * r_;
					float z = std::sin(val) * r_;

					verts.setXYZ(NVIDX++,
						radius * x,
						radius * y + height * dy,
						radius * z
					);

					norms.setXYZ(NNIDX++,
						x,
						y,
						z
					);

					texCoords.setXY(NTIDX++,
						1.0 - (s * segIncr),
						0.5 - ((radius * y + height * dy) / (2.0 * radius + height))
					);
				}
			});

			unsigned int r;
			for (r = 0; r < subHeight / 2; ++r)
			{
				calcNewRing(numSegm, std::sin(Mathf::PI * r * ringIncr),
					std::sin(Mathf::PI * (r * ringIncr - 0.5f)), -0.5f);
			}

			for (r = 0; r < ringsBody; ++r)
			{
				calcNewRing(numSegm, 1.0f, 0.0f, r * bodyIncr - 0.5f);
			}

			for (r = subHeight / 2; r < subHeight; ++r)
			{
				calcNewRing(numSegm, std::sin(Mathf::PI * r * ringIncr),
					std::sin(Mathf::PI * (r * ringIncr - 0.5f)), +0.5f);
			}

			unsigned int idx = 0;
			for (r = 0; r < ringsTotal - 1; ++r)
			{
				for (unsigned int s = 0; s < numSegm - 1; ++s)
				{
					cells[idx++] = r * numSegm + (s + 1);
					cells[idx++] = r * numSegm + (s + 0);
					cells[idx++] = (r + 1) * numSegm + (s + 1);
					cells[idx++] = (r + 1) * numSegm + (s + 0);
					cells[idx++] = (r + 1) * numSegm + (s + 1);
					cells[idx++] = r * numSegm + s;
				}
			};

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

#endif /* __MB_CAPSULE__ */
