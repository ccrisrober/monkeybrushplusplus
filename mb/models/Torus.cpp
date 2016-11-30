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

#include "Torus.hpp"

namespace mb
{
    Torus::Torus(float outerRadius, float innerRadius,
        unsigned int sides, unsigned int rings)
    : Drawable()
    {
        unsigned int faces = sides * rings;
        unsigned int nv  = sides * (rings + 1);   // One extra ring to duplicate first ring

		BufferAttribute verts(std::vector<float>(3 * nv), 3);
		BufferAttribute norms(std::vector<float>(3 * nv), 3);
		BufferAttribute texCoords(std::vector<float>(2 * nv), 2);

		std::vector<unsigned int> cells(6 * faces);

		// Generate the vertex data
        unsigned int NVIDX = 0;
        unsigned int NNIDX = 0;
        unsigned int NTIDX = 0;

        float ringFactor = Mathf::TWO_PI / rings;
        float sideFactor = Mathf::TWO_PI / sides;
        float norms_[3];
        for (unsigned int ring = 0; ring <= rings; ++ring)
        {
            float u = ring * ringFactor;
            float cu = std::cos(u);
            float su = std::sin(u);
            for (unsigned int side = 0; side < sides; ++side)
            {
                float v = side * sideFactor;
                float cv = std::cos(v);
                float sv = std::sin(v);
                float r = (outerRadius + innerRadius * cv);

				norms_[0] = cv * cu * r;
				norms_[1] = cv * su * r;
				norms_[2] = sv * r;
                // Normalize
                float len = std::sqrt(
					norms_[0] * norms_[0] +
					norms_[1] * norms_[1] +
					norms_[2] * norms_[2]);
				norms_[0] /= len;
				norms_[1] /= len;
				norms_[2] /= len;

                verts.setXYZ(NVIDX++, r * cu, r * su, innerRadius * sv);
                norms.setXYZ(NNIDX++, norms_[0], norms_[1], norms_[2]);
                texCoords.setXY(NTIDX++, u / Mathf::TWO_PI * 2.0, v / Mathf::TWO_PI * 2.0);
            }
        }

        unsigned int idx = 0;
        for (unsigned int ring = 0; ring < rings; ++ring)
        {
            unsigned int ringStart = ring * sides;
            unsigned int nextRingStart = (ring + 1) * sides;
            for (unsigned int side = 0; side < sides; ++side)
            {
                unsigned int nextSide = (side + 1) % sides;
                // The quad
                cells[idx] = (ringStart + side);
                cells[idx + 1] = (nextRingStart + side);
                cells[idx + 2] = (nextRingStart + nextSide);
                cells[idx + 3] = ringStart + side;
                cells[idx + 4] = nextRingStart + nextSide;
                cells[idx + 5] = (ringStart + nextSide);
                idx += 6;
            }
        }

		_numVertices = verts.count();

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
}
