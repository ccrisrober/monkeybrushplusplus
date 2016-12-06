#ifndef _IDRAW_
#define _IDRAW_

#include <mb/api.h>

#include "../core/BufferAttribute.hpp"
#include "../core/VertexArray.hpp"
#include "../core/VertexBuffer.hpp"
#include "../core/Color3.hpp"

namespace mb
{
	class IDraw
	{
	public:
		MB_API
		virtual void render() = 0;
		MB_API
		unsigned int indicesLen() { return 0; }
		MB_API
		unsigned int verticesLen() { return 0; }
	};
	class InstancedIndexedDrawrable : public IDraw
	{
	public:
		MB_API
			InstancedIndexedDrawrable() : IDraw()
		{
			float side2 = 1.0f / 2.0f;
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
			std::vector<unsigned int> indices = {
				0, 1, 2, 0, 2, 3,
				4, 5, 6, 4, 6, 7,
				8, 9, 10, 8, 10, 11,
				12, 13, 14, 12, 14, 15,
				16, 17, 18, 16, 18, 19,
				20, 21, 22, 20, 22, 23
			};

			_vao.bind();

			addBufferArray(0, vertices, 3, GL_STATIC_DRAW);

			std::vector<float> offset;
			std::vector<float> color;
			const int max = 5;
			srand(time(nullptr));
			for (int i = -max; i < max; ++i)
			{
				for (int j = -max; j < max; ++j)
				{
					for (int k = -max; k < max; ++k)
					{
						offset.push_back(i * 2.5f);
						offset.push_back(j * 2.5f);
						offset.push_back(k * 2.5f);

						Color3 color_;
						switch (std::rand() % 8)
						{
						case 0:
							color_ = Color3::Pink;
							break;
						case 1:
							color_ = Color3::Red;
							break;
						case 2:
							color_ = Color3::Green;
							break;
						case 4:
							color_ = Color3::White;
							break;
						case 5:
							color_ = Color3::Yellow;
							break;
						case 6:
							color_ = Color3::Blue;
							break;
						case 7:
							color_ = Color3::Brown;
							break;
						}
						color.push_back(color_.r());
						color.push_back(color_.g());
						color.push_back(color_.b());
					}
				}
			}

			numInstances = offset.size() / 3;

			VertexBuffer vb(GL_ARRAY_BUFFER);
			vb.data(offset, GL_DYNAMIC_DRAW);
			vb.attribDivisor(1, 3, 1);

			VertexBuffer vb2(GL_ARRAY_BUFFER);
			vb2.data(color, GL_DYNAMIC_DRAW);
			vb2.attribDivisor(2, 3, 1);

			//addElementArray(data, type);

			VertexBuffer vbIndices(GL_ELEMENT_ARRAY_BUFFER);
			vbIndices.data(indices, GL_STATIC_DRAW);
			_indicesLen = indices.size();
			this->_handles.push_back(vbIndices);

			_vao.unbind();
		}
		MB_API
			virtual void render() override
		{
			_vao.bind();
			glDrawElementsInstanced(GL_TRIANGLES, _indicesLen, GL_UNSIGNED_INT, 0, numInstances);
			_vao.unbind();
		}
	protected:
		unsigned int numInstances;
		void addBufferArray(unsigned int attribLocation, const std::vector<float>& data,
			unsigned int numElems, unsigned int type)
		{
			VertexBuffer vb(GL_ARRAY_BUFFER);
			vb.data(data, type);
			vb.vertexAttribPointer(attribLocation, numElems, GL_FLOAT, false);
			_handles.push_back(vb);
		}

		std::vector<VertexBuffer> _handles;
		VertexArray _vao;
		unsigned int _indicesLen;
	};
	class IndexedDrawable: public IDraw
	{
	public:
		MB_API
		IndexedDrawable(): IDraw()
		{
			float side2 = 1.0f / 2.0f;
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
	        std::vector<unsigned int> indices = {
	            0, 1, 2, 0, 2, 3,
	            4, 5, 6, 4, 6, 7,
	            8, 9, 10, 8, 10, 11,
	            12, 13, 14, 12, 14, 15,
	            16, 17, 18, 16, 18, 19,
	            20, 21, 22, 20, 22, 23
	        };

			_vao.bind();

			addBufferArray(0, vertices, 3, GL_STATIC_DRAW);
			//addElementArray(data, type);

			VertexBuffer vbIndices(GL_ELEMENT_ARRAY_BUFFER);
			vbIndices.data(indices, GL_STATIC_DRAW);
			_indicesLen = indices.size();
			this->_handles.push_back(vbIndices);

        	_vao.unbind();
		}
		MB_API
		virtual void render() override
		{
			_vao.bind();
	        glDrawElements(GL_TRIANGLES, _indicesLen, GL_UNSIGNED_INT, 0);
	        _vao.unbind();
		}
	protected:
	    void addBufferArray(unsigned int attribLocation, const std::vector<float>& data,
	        unsigned int numElems, unsigned int type)
	    {
	        VertexBuffer vb(GL_ARRAY_BUFFER);
			vb.data(data, type);
			vb.vertexAttribPointer(attribLocation, numElems, GL_FLOAT, false);
	        _handles.push_back(vb);
	    }

		std::vector<VertexBuffer> _handles;
		VertexArray _vao;
		unsigned int _indicesLen;
	};
	class ArraysDrawable: public IDraw
	{
	public:
		MB_API
		ArraysDrawable(): IDraw()
		{
			float g_vertex_buffer_data[] = {
				-1.0f,-1.0f,-1.0f,
				-1.0f,-1.0f, 1.0f,
				-1.0f, 1.0f, 1.0f,
				1.0f, 1.0f,-1.0f,
				-1.0f,-1.0f,-1.0f,
				-1.0f, 1.0f,-1.0f,
				1.0f,-1.0f, 1.0f,
				-1.0f,-1.0f,-1.0f,
				1.0f,-1.0f,-1.0f,
				1.0f, 1.0f,-1.0f,
				1.0f,-1.0f,-1.0f,
				-1.0f,-1.0f,-1.0f,
				-1.0f,-1.0f,-1.0f,
				-1.0f, 1.0f, 1.0f,
				-1.0f, 1.0f,-1.0f,
				1.0f,-1.0f, 1.0f,
				-1.0f,-1.0f, 1.0f,
				-1.0f,-1.0f,-1.0f,
				-1.0f, 1.0f, 1.0f,
				-1.0f,-1.0f, 1.0f,
				1.0f,-1.0f, 1.0f,
				1.0f, 1.0f, 1.0f,
				1.0f,-1.0f,-1.0f,
				1.0f, 1.0f,-1.0f,
				1.0f,-1.0f,-1.0f,
				1.0f, 1.0f, 1.0f,
				1.0f,-1.0f, 1.0f,
				1.0f, 1.0f, 1.0f,
				1.0f, 1.0f,-1.0f,
				-1.0f, 1.0f,-1.0f,
				1.0f, 1.0f, 1.0f,
				-1.0f, 1.0f,-1.0f,
				-1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f,
				-1.0f, 1.0f, 1.0f,
				1.0f,-1.0f, 1.0f
			};
			glGenBuffers(1, &vertexbuffer);
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
		}
		unsigned int vertexbuffer;
		virtual void render() override
		{
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(
				0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);
			glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles
		}
	protected:
		// std::vector<BufferAttribute> _buffers;
		std::vector<VertexBuffer> _handles;
		void addBufferArray(unsigned int attribLocation, const std::vector<float>& data,
	        unsigned int numElems, unsigned int type)
	    {
	        VertexBuffer vb(GL_ARRAY_BUFFER);
			vb.data(data, type);
			vb.vertexAttribPointer(attribLocation, numElems, GL_FLOAT, false);
	        _handles.push_back(vb);
	    }
	};
}

#endif _IDRAW_