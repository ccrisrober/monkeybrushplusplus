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

#include "Plane.hpp"

namespace mb
{
    Plane::Plane(const float& xsize, const float& zsize, const float& xdivs, const float& zdivs,
		const float& smax, const float& tmax)
		: Drawable()
	{
		std::vector<float> verts(3 * (xdivs + 1) * (zdivs + 1));
		std::vector<float> norms(3 * (xdivs + 1) * (zdivs + 1));
		std::vector<float> tex(2 * (xdivs + 1) * (zdivs + 1));
		std::vector<unsigned int> el(6 * xdivs * zdivs);

		float x2 = xsize / 2.0f;
		float z2 = zsize / 2.0f;

		float iFactor = zsize / zdivs;
		float jFactor = xsize / xdivs;
		float texi = smax / zdivs;
		float texj = tmax / xdivs;
		float x, z;
		unsigned int vidx = 0, tidx = 0;
		for (unsigned int i = 0; i <= zdivs; ++i)
		{
			z = iFactor * i - z2;
			for (unsigned int j = 0; j <= xdivs; ++j)
			{
				x = jFactor * j - x2;
				verts[vidx] = x;
				verts[vidx + 1] = 0.0f;
				verts[vidx + 2] = z;
				norms[vidx] = 0.0;
				norms[vidx + 1] = 1.0f;
				norms[vidx + 2] = 0.0f;
				vidx += 3;
				tex[tidx] = j * texi;
				tex[tidx + 1] = i * texj;
				tidx += 2;
			}
		}

		unsigned int rowStart, nextRowStart;
		unsigned int idx = 0;
		for (unsigned int i = 0; i < zdivs; ++i)
		{
			rowStart = i * (xdivs + 1);
			nextRowStart = (i + 1) * (xdivs + 1);
			for (unsigned int j = 0; j < xdivs; ++j)
			{
				el[idx] = rowStart + j;
				el[idx + 1] = nextRowStart + j;
				el[idx + 2] = nextRowStart + j + 1;
				el[idx + 3] = rowStart + j;
				el[idx + 4] = nextRowStart + j + 1;
				el[idx + 5] = rowStart + j + 1;
				idx += 6;
			}
		}

		_numVertices = verts.size() / 3;

		_vao = new mb::VertexArray();
		_vao->bind();

		addBufferArray(0, verts, 3, GL_STATIC_DRAW);
		addBufferArray(1, norms, 3, GL_STATIC_DRAW);
		addBufferArray(2, tex, 2, GL_STATIC_DRAW);

		std::vector<unsigned int> data = el;
		unsigned int type = GL_STATIC_DRAW;

		mb::VertexBuffer vbIndices(GL_ELEMENT_ARRAY_BUFFER);
		vbIndices.data(data, type);
		_indicesLen = data.size();
		this->_handle.push_back(vbIndices);

		_vao->unbind();
	}
}
