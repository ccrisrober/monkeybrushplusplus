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

#include "../Includes.hpp"
#include "../core/VertexArray.hpp"
#include "../core/VertexBuffer.hpp"

namespace MB
{
    class Drawable
    {
    public:
        Drawable(float /*side = 1.0f*/)
        {
            /*float side2 = side / 2.0f;
            // Vertices
            std::vector<float> vertices = {
                // Front
                -side2, -side2, side2,
                side2, -side2, side2,
                side2,  side2, side2,
                -side2,  side2, side2,
                // Right
                side2, -side2, side2,
                side2, -side2, -side2,
                side2,  side2, -side2,
                side2,  side2, side2,
                // Back
                -side2, -side2, -side2,
                -side2,  side2, -side2,
                side2,  side2, -side2,
                side2, -side2, -side2,
                // Left
                -side2, -side2, side2,
                -side2,  side2, side2,
                -side2,  side2, -side2,
                -side2, -side2, -side2,
                // Bottom
                -side2, -side2, side2,
                -side2, -side2, -side2,
                side2, -side2, -side2,
                side2, -side2, side2,
                // Top
                -side2,  side2, side2,
                side2,  side2, side2,
                side2,  side2, -side2,
                -side2,  side2, -side2
            };
            // Normals
            std::vector<float> normals = {
                // Front
                0.0, 0.0, 1.0,
                0.0, 0.0, 1.0,
                0.0, 0.0, 1.0,
                0.0, 0.0, 1.0,
                // Right
                1.0, 0.0, 0.0,
                1.0, 0.0, 0.0,
                1.0, 0.0, 0.0,
                1.0, 0.0, 0.0,
                // Back
                0.0, 0.0, -1.0,
                0.0, 0.0, -1.0,
                0.0, 0.0, -1.0,
                0.0, 0.0, -1.0,
                // Left
                -1.0, 0.0, 0.0,
                -1.0, 0.0, 0.0,
                -1.0, 0.0, 0.0,
                -1.0, 0.0, 0.0,
                // Bottom
                0.0, -1.0, 0.0,
                0.0, -1.0, 0.0,
                0.0, -1.0, 0.0,
                0.0, -1.0, 0.0,
                // Top
                0.0, 1.0, 0.0,
                0.0, 1.0, 0.0,
                0.0, 1.0, 0.0,
                0.0, 1.0, 0.0
            };
            // TexCoords
            std::vector<float> texCoords = {
                // Front
                0.0, 0.0,
                1.0, 0.0,
                1.0, 1.0,
                0.0, 1.0,
                // Right
                0.0, 0.0,
                1.0, 0.0,
                1.0, 1.0,
                0.0, 1.0,
                // Back
                0.0, 0.0,
                1.0, 0.0,
                1.0, 1.0,
                0.0, 1.0,
                // Left
                0.0, 0.0,
                1.0, 0.0,
                1.0, 1.0,
                0.0, 1.0,
                // Bottom
                0.0, 0.0,
                1.0, 0.0,
                1.0, 1.0,
                0.0, 1.0,
                // Top
                0.0, 0.0,
                1.0, 0.0,
                1.0, 1.0,
                0.0, 1.0
            };
            // TexCoords
            std::vector<unsigned int> indices = {
                0, 1, 2, 0, 2, 3,
                4, 5, 6, 4, 6, 7,
                8, 9, 10, 8, 10, 11,
                12, 13, 14, 12, 14, 15,
                16, 17, 18, 16, 18, 19,
                20, 21, 22, 20, 22, 23
            };
            _handle.resize(4);
            addElementArray(indices);

            addBufferArray(0, vertices, 3);
            addBufferArray(1, normals, 3);
            addBufferArray(2, texCoords, 2);

            _vao->unbind();*/

            /*GLfloat vertices[] = {
                0.5f,  0.5f, 0.0f,  // Top Right
                0.5f, -0.5f, 0.0f,  // Bottom Right
                -0.5f, -0.5f, 0.0f,  // Bottom Left
                -0.5f,  0.5f, 0.0f   // Top Left
            };
            GLuint indices[] = {  // Note that we start from 0!
                0, 1, 3,  // First Triangle
                1, 2, 3   // Second Triangle
            };
            GLuint VBO, EBO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindVertexArray(0);*/

            std::vector<float> cubeVertexPos = {
                //Cara z = 1
                0.0f,	0.0f,	1.0f, //0
                1.0f,	0.0f,	1.0f, //1
                0.0f,	1.0f,	1.0f, //2
                1.0f,	1.0f,	1.0f, //3

                //Cara z = 0
                0.0f,	0.0f,	0.0f, //4
                1.0f,	0.0f,	0.0f, //5
                0.0f,	1.0f,	0.0f, //6
                1.0f,	1.0f,	0.0f, //7

                //Cara x = 1
                1.0f,	0.0f,	0.0f, //8
                1.0f,	0.0f,	1.0f, //9
                1.0f,	1.0f,	0.0f, //10
                1.0f,	1.0f,	1.0f, //11

                //Cara x = 0
                0.0f,	0.0f,	0.0f, //12
                0.0f,	0.0f,	1.0f, //13
                0.0f,	1.0f,	0.0f, //14
                0.0f,	1.0f,	1.0f, //15

                //Cara y = 1
                0.0f,	1.0f,	0.0f, //16
                0.0f,	1.0f,	1.0f, //17
                1.0f,	1.0f,	0.0f, //18
                1.0f,	1.0f,	1.0f, //19

                //Cara y = 0
                0.0f,	0.0f,	0.0f, //20
                0.0f,	0.0f,	1.0f, //21
                1.0f,	0.0f,	0.0f, //22
                1.0f,	0.0f,	1.0f  //23
            };
            std::vector<float> cubeVertexNormal = {
                //Cara z = 1
                0.0f,	0.0f,	 1.0f,
                0.0f,	0.0f,	 1.0f,
                0.0f,	0.0f,	 1.0f,
                0.0f,	0.0f,	 1.0f,

                //Cara z = 0
                0.0f,	0.0f,	-1.0f,
                0.0f,	0.0f,	-1.0f,
                0.0f,	0.0f,	-1.0f,
                0.0f,	0.0f,	-1.0f,

                //Cara x = 1
                1.0f,	0.0f,	 0.0f,
                1.0f,	0.0f,	 0.0f,
                1.0f,	0.0f,	 0.0f,
                1.0f,	0.0f,	 0.0f,

                //Cara x = 0
                -1.0f,	0.0f,	 0.0f,
                -1.0f,	0.0f,	 0.0f,
                -1.0f,	0.0f,	 0.0f,
                -1.0f,	0.0f,	 0.0f,

                //Cara y = 1
                0.0f,	1.0f,	0.0f,
                0.0f,	1.0f,	0.0f,
                0.0f,	1.0f,	0.0f,
                0.0f,	1.0f,	0.0f,

                //Cara y = 0
                0.0f,	-1.0f,	0.0f,
                0.0f,	-1.0f,	0.0f,
                0.0f,	-1.0f,	0.0f,
                0.0f,	-1.0f,	0.0f
            };
            std::vector<unsigned int> cubeTriangleIndex = {
                //Cara z = 1
                0,1,2,			1,3,2,
                //Cara z = -1
                4,6,5,			5,6,7,
                //Cara x = 1
                8,10,9,			9,10,11,
                //Cara x = -1
                12,13,14,		13,15,14,
                //Cara y = 1
                16,17,18,		17,19,18,
                //Cara y = -1
                20,22,21,		21,22,23,
            };

            _vao = new VertexArray();
            vbo = new VertexBuffer(GL_ARRAY_BUFFER);
            vboN = new VertexBuffer(GL_ARRAY_BUFFER);
            // Not neccesary vbo->bind();
            vbo->data(cubeVertexPos, GL_STATIC_DRAW);
            vboN->data(cubeVertexNormal, GL_STATIC_DRAW);

            _vao->bind();
            // Position attribute
            vbo->vertexAttribPointer(0, 3, GL_FLOAT, false);
            vboN->vertexAttribPointer(1, 3, GL_FLOAT, false);


            VertexBuffer vb2(GL_ELEMENT_ARRAY_BUFFER);
            vb2.data(cubeTriangleIndex, GL_STATIC_DRAW);

            _vao->unbind();
        }
        VertexBuffer *vbo, *vboN;
        void render()
        {
            this->_vao->bind();
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            this->_vao->unbind();
        }
    protected:
        void addBufferArray(unsigned int attribLocation, const std::vector<float>& data,
            unsigned int numElems, unsigned int type = GL_STATIC_DRAW)
        {
            VertexBuffer vb(GL_ARRAY_BUFFER);
            vb.data(data, type);
            vb.vertexAttribPointer(attribLocation, numElems, GL_FLOAT, false);
            this->_handle.push_back(vb);
        }
        void addElementArray(const std::vector<unsigned int>& data,
            unsigned int type = GL_STATIC_DRAW)
        {
            _indicesLen = data.size();
            VertexBuffer vb(GL_ELEMENT_ARRAY_BUFFER);
            vb.data(data, type);
            this->_handle.push_back(vb);
        }
        unsigned int _indicesLen;
        std::vector<VertexBuffer> _handle;
        VertexArray* _vao;
    };
}

#endif /* __MB_DRAWABLE__ */
