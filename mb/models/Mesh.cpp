/*
 * Copyright (c) 2016 maldicion069
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

#include "Mesh.hpp"

namespace mb
{
        Mesh::Mesh(const std::string& fileRoute)
    : Drawable()
    {
        mb::ObjParser obj;
        mb::Model model = obj.loadObj(fileRoute);

        BufferAttribute<float> verts(std::vector<float>(model.vertices.size()), 3);
        verts.array(model.vertices);
        BufferAttribute<float> norms(std::vector<float>(model.normals.size()), 3);
        norms.array(model.normals);
        BufferAttribute<float> texCoords(std::vector<float>(model.texCoords.size()), 2);
        texCoords.array(model.texCoords);

        _vao = new VertexArray();
        _vao->bind();

            addBufferArray(0, verts.array(), 3, GL_STATIC_DRAW);
            addBufferArray(1, norms.array(), 3, GL_STATIC_DRAW);
            addBufferArray(2, texCoords.array(), 2, GL_STATIC_DRAW);

            std::vector<unsigned int> data = model.indices;
            unsigned int type = GL_STATIC_DRAW;

            VertexBuffer vbIndices(GL_ELEMENT_ARRAY_BUFFER);
            vbIndices.data(data, type);
            _indicesLen = data.size();
            this->_handle.push_back(vbIndices);

        _vao->unbind();
    }
}
