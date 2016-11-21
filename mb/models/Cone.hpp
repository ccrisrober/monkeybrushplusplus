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

#ifndef __MB__CONE__
#define __MB__CONE__

#include <mb/api.h>

#include <functional>
#include "Drawable.hpp"
#include "../maths/Mathf.hpp"
#include "../core/BufferAttribute.hpp"

namespace MB
{
    class Cone: public Drawable
    {
    public:
		MB_API
        Cone(float bottomRadius, float topRadius,
			float height, unsigned int radialSubDiv = 3, int heightSubDiv = 1,
			bool createTopBase = true, bool createBottomBase = true)
        : Drawable()
        {
			if (radialSubDiv < 3) {
				throw ("radialSubDiv must be 3 or greater");
			}

			if (heightSubDiv < 1) {
				throw ("heightSubDiv must be 1 or greater");
			}
            unsigned int extra = (createTopBase ? 2 : 0) + (createBottomBase ? 2 : 0);

			unsigned int nv = (radialSubDiv + 1) * (heightSubDiv + 1 + extra);

			BufferAttribute verts(std::vector<float>(3 * nv), 3);
			BufferAttribute norms(std::vector<float>(3 * nv), 3);
			BufferAttribute texCoords(std::vector<float>(2 * nv), 2);

			std::vector<unsigned int> cells(3 * radialSubDiv * (heightSubDiv + extra) * 2);

			unsigned int vertsAroundEdge = radialSubDiv + 1;

			// Slant: Distance from the top of a Cone, down the side to a point on the edge of the base.
			float slantH = std::atan2(bottomRadius - topRadius, height);
			float cSlantH = std::cos(slantH);
			float sSlantH = std::sin(slantH);

			int start = createTopBase ? -2 : 0;
			int end = heightSubDiv + (createBottomBase ? 2 : 0);

			unsigned int NVIDX = 0;
			unsigned int NNIDX = 0;
			unsigned int NTIDX = 0;
			for (int yy = start; yy <= end; ++yy)
			{
				float v = yy / heightSubDiv;
				float y = height * v;
				float ringRadius;
				if (yy < 0)
				{
					y = 0;
					v = 1;
					ringRadius = bottomRadius;
				}
				else if (yy > heightSubDiv)
				{
					y = height;
					v = 1;
					ringRadius = topRadius;
				}
				else
				{
					ringRadius = bottomRadius +
						(topRadius - bottomRadius) * (yy / heightSubDiv);
				}
				if (yy == -2 || yy == heightSubDiv + 2)
				{
					ringRadius = 0;
					v = 0;
				}
				y -= height / 2;

				for (unsigned int ii = 0; ii < vertsAroundEdge; ++ii)
				{
					float sin = std::sin(ii * Mathf::PI * 2 / radialSubDiv);
					float cos = std::cos(ii * Mathf::PI * 2 / radialSubDiv);

					verts.setXYZ(NVIDX++, sin * ringRadius, y, cos * ringRadius);
					norms.setXYZ(NNIDX++,
						(yy < 0 || yy > heightSubDiv) ? 0 : (sin * cSlantH),
						(yy < 0) ? -1 : (yy > heightSubDiv ? 1 : sSlantH),
						(yy < 0 || yy > heightSubDiv) ? 0 : (cos * cSlantH));
					texCoords.setXY(NTIDX++, (ii / radialSubDiv), 1.0 - v);
				}
			}

			// Generate the element list
			unsigned int idx = 0;
			for (unsigned int yy = 0; yy < heightSubDiv + extra; ++yy)
			{
				for (unsigned int ii = 0; ii < radialSubDiv; ++ii)
				{
					cells[idx++] = vertsAroundEdge * (yy + 0) + 0 + ii;
					cells[idx++] = vertsAroundEdge * (yy + 0) + 1 + ii;
					cells[idx++] = vertsAroundEdge * (yy + 1) + 1 + ii;

					cells[idx++] = vertsAroundEdge * (yy + 0) + 0 + ii;
					cells[idx++] = vertsAroundEdge * (yy + 1) + 1 + ii;
					cells[idx++] = vertsAroundEdge * (yy + 1) + 0 + ii;
				}
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

#endif /* __MB__CONE__ */
