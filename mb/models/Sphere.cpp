/*
 * Copyright (c) 2017 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus
 * <https://github.com/maldicion069/monkeybrushplusplus>
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

#include "Sphere.hpp"
#include "../maths/Mathf.hpp"
#include "../core/BufferAttribute.hpp"

namespace mb
{
	Sphere::Sphere(const float& radius,
		const unsigned int& widthSubDiv,
		const unsigned int& heightSubDiv)
	{
		unsigned int faces = (1 + heightSubDiv) * (1 + widthSubDiv);
		unsigned int nv = 3 * heightSubDiv * widthSubDiv * 2;

		BufferAttribute<float> verts(std::vector<float>(3 * nv), 3);
		BufferAttribute<float> norms(std::vector<float>(3 * nv), 3);
		BufferAttribute<float> texCoords(std::vector<float>(2 * nv), 2);
		std::vector<unsigned int> indices;
		indices.reserve(nv);

		// Generate the vertex data
		unsigned int NVIDX = 0;
		unsigned int NNIDX = 0;
		unsigned int NTIDX = 0;
		unsigned int IDX = 0;

		std::vector< std::vector< unsigned int > > grid;

		float u, v;

		mb::Vect3 vertex;

		for( unsigned int i = 0; i <= heightSubDiv; ++i )
		{
			std::vector< unsigned int> idxs;
			v = (float)i/(float)heightSubDiv;
			for( unsigned int j = 0; j <= widthSubDiv; ++j )
			{
				u = (float)j/(float)widthSubDiv;

				vertex.x(-radius * cos(u * Mathf::TWO_PI) * sin(v * Mathf::TWO_PI));
				vertex.y(radius * cos(v * Mathf::TWO_PI));
				vertex.z(radius * sin(u * Mathf::TWO_PI) * sin(v * Mathf::TWO_PI));

				verts.setXYZ(NVIDX++,
					vertex.x(),
					vertex.y(),
					vertex.z()
				);

				vertex.normalize();

				norms.setXYZ(NNIDX++,
					vertex.x(),
					vertex.y(),
					vertex.z()
				);
				texCoords.setXY(NTIDX++, u, 1.0f - v);

				idxs.push_back( IDX++ );
			}
			grid.push_back( idxs );
		}

		for (unsigned int i = 0; i < heightSubDiv; ++i)
		{
			for (unsigned int j = 0; j < widthSubDiv; ++j)
			{
				unsigned int a = grid[i][j + 1];
				unsigned int b = grid[i][j];
				unsigned int c = grid[i + 1][j];
				unsigned int d = grid[i + 1][j + 1];

				indices.push_back(a);
				indices.push_back(b);
				indices.push_back(d);

				indices.push_back(b);
				indices.push_back(c);
				indices.push_back(d);
			}
		}

		_numVertices = verts.count();

		_vao = new VertexArray();
		_vao->bind();
    VertexBuffer vbIndices(GL_ELEMENT_ARRAY_BUFFER);
    vbIndices.data(indices, GL_STATIC_DRAW);
    _indicesLen = indices.size();

		addBufferArray(0, verts.array(), 3, GL_STATIC_DRAW);
		addBufferArray(1, norms.array(), 3, GL_STATIC_DRAW);
		addBufferArray(2, texCoords.array(), 2, GL_STATIC_DRAW);

		this->_handle.push_back(vbIndices);

		_vao->unbind();
	}
}
