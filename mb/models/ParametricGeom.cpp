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

#include "ParametricGeom.hpp"
#include <vector>
#include "../maths/Vect3.hpp"
#include "../core/BufferAttribute.hpp"

namespace mb
{
	ParametricGeom::ParametricGeom(const std::function<mb::Vect3(float, float)>& func, 
		const unsigned int& slices, const unsigned int& stacks)
		: Drawable()
	{
		std::vector<float> normals;

		Vect3 evalVect3;
		float u, v;
		unsigned int i, j;

		unsigned int nv = (slices + 1) * (stacks + 1);

		BufferAttribute verts(std::vector<float>(3 * nv), 3);
		BufferAttribute norms(std::vector<float>(3 * nv, 0.0f), 3);
		BufferAttribute texCoords(std::vector<float>(2 * 3 * (slices * stacks) * 2), 2);
		std::vector<unsigned int> indices(3 * (slices * stacks) * 2);

		unsigned int count = slices + 1;

		unsigned int NVX = 0;
		unsigned int NTX = 0;

		for (i = 0; i <= stacks; ++i)
		{
			v = (float) i / stacks;
			for (j = 0; j <= slices; ++j)
			{
				u = (float) j / slices;
				evalVect3 = func(u, v);
				verts.setXYZ(NVX++, evalVect3.x(), evalVect3.y(), evalVect3.z());
			}
		}

		unsigned int pA, pB, pC, pD;
        // TODO: UVs error :(
		for (i = 0; i < stacks; ++i)
		{
			for (j = 0; j < slices; ++j)
			{
				pA = i * count + j;
				pB = i * count + j + 1;
				pC = (i + 1) * count + j + 1;
				pD = (i + 1) * count + j;

				indices.push_back(pA);
				indices.push_back(pB);
				indices.push_back(pC);
				texCoords.setXY(NTX++, j / slices, i / stacks);
				texCoords.setXY(NTX++, (j + 1) / slices, i / stacks);
				texCoords.setXY(NTX++, j / slices, (i + 1) / stacks);

				indices.push_back(pB);
				indices.push_back(pC);
				indices.push_back(pD);
				texCoords.setXY(NTX++, (j + 1) / slices, i / stacks);
				texCoords.setXY(NTX++, (j + 1) / slices, (i + 1) / stacks);
				texCoords.setXY(NTX++, j / slices, (i + 1) / stacks);
			}
		}

		/*for (i = 0; i < indices.size(); ++i) {
			norms.getXYZ
			const ia : MB.Vect3 = vertices[indices[i].x];
			const ib : MB.Vect3 = vertices[indices[i].y];
			const ic : MB.Vect3 = vertices[indices[i].z];

			const e1 : MB.Vect3 = MB.Vect3.sub(ia, ib);
			const e2 : MB.Vect3 = MB.Vect3.sub(ic, ib);
			const no : MB.Vect3 = MB.Vect3.cross(e1, e2);

			normals[indices[i].x] = normals[indices[i].x].add(no);
			normals[indices[i].y] = normals[indices[i].y].add(no);
			normals[indices[i].z] = normals[indices[i].z].add(no);
		}

		for (i = 0; i < normals.length; ++i) {
			normals[i] = normals[i].normalize();
		}

		let vertices2 : Array<number> = [];
		for (i = 0; i < vertices.length; ++i) {
			vertices2.push(vertices[i].x, vertices[i].y, vertices[i].z);
		}
		vertices = vertices2;
		let normals2 : Array<number> = [];
		for (i = 0; i < normals.length; ++i) {
			normals2.push(normals[i].x, normals[i].y, normals[i].z);
		}
		normals = normals2;
		let indices2 : Array<number> = [];
		for (i = 0; i < indices.length; ++i) {
			indices2.push(indices[i].x, indices[i].y, indices[i].z);
		}
		indices = indices2;
		let uvs2 : Array<number> = [];
		for (i = 0; i < uvs.length; ++i) {
			uvs2.push(uvs[i].x, uvs[i].y);
		}
		uvs = uvs2;*/
		_numVertices = verts.count();

		_vao = new VertexArray();
		_vao->bind();

		addBufferArray(0, verts.array(), 3, GL_STATIC_DRAW);
		addBufferArray(1, norms.array(), 3, GL_STATIC_DRAW);
		addBufferArray(2, texCoords.array(), 2, GL_STATIC_DRAW);

		std::vector<unsigned int> data = indices;
		unsigned int type = GL_STATIC_DRAW;

		VertexBuffer vbIndices(GL_ELEMENT_ARRAY_BUFFER);
		vbIndices.data(data, type);
		_indicesLen = data.size();
		this->_handle.push_back(vbIndices);

		_vao->unbind();
	}
}