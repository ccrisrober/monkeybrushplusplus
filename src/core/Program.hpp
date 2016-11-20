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

#ifndef __MB_PROGRAM__
#define __MB_PROGRAM__

#include <map>
#include <map>
#include <string>
#include <vector>
#include <functional>
#include <regex>

#define MB_GEOMETRY_SHADERS
#define MB_TESSELATION_SHADERS
#define MB_COMPUTE_SHADERS
#define MB_SUBPROGRAMS
#define MB_OCC_QUERY

namespace MB
{
	class Program
	{
	public:
		std::string _processImports(const std::string& src)
		{
			std::string ret = "TODO";
			/*if (std::regex_search(src, sm, regex))
			{

			}
			bool match = std::regex_match(src, regex);*/
			/*
			let match = regex.exec(src);
			let ret = src.slice(0);
			while (match != null) {
				let includeFile = match[1];
				if (MB.ResourceShader.exist(includeFile)) {
					let content = MB.ResourceShader.get(includeFile);
					if (match[4]) {
						let splits = match[5].split(",");
						let sp;
						for (let idx = 0, size = splits.length; idx < size; ++idx) {
							sp = splits[idx].split("=");
							content = content.replace(new RegExp(sp[0], "g"), sp[1]);
						}
					}
					if (match[2]) {
						let idxStr = match[3];
						if (idxStr.indexOf("..") != = -1) {
							let idxSplits = idxStr.split("..");
							let min = parseInt(idxSplits[0]);
							let max = parseInt(idxSplits[1]);
							let srcContent = content.slice(0);
							content = "";
							if (isNaN(max)) {
								max = min;
							}
							for (let i = min; i <= max; i++) {
								content += srcContent.replace(/ \{N\} / g, i + "") + "\n";
							}
						}
						else {
							content = content.replace(/ \{N\} / g, idxStr);
						}
					}
					ret = ret.replace(match[0], this._processImports(content));
				}
				else {
					// ...
					ret = ret.replace(match[0], "FAIL");
				}
				match = regex.exec(src);
			}
			*/
			return ret;
		}



		void autocatching(bool attributes = true, bool uniforms = true);

		Program(void);
		~Program(void);
		/**
		* Method to load and add a vertex and fragment shaders from file
		* @param source: Vertex shader file source
		* @param source: Fragment shader source
		* @return Shader loaded
		*/
		bool load(const std::string& vsFile, const std::string& fsFile);
		/**
		* Method to load and add a vertex shader from file
		* @param source: Shader file source
		* @return Shader loaded
		*/
		bool loadVertexShader(const std::string& file);
		/**
		* Method to load and add a fragment shader from file
		* @param source: Shader file source
		* @return Shader loaded
		*/
		bool loadFragmentShader(const std::string& file);
#ifdef MB_GEOMETRY_SHADERS
		/**
		* Method to load and add a geometry shader from file
		* @param source: Shader file source
		* @return Shader loaded
		*/
		bool loadGeometryShader(const std::string& file);
#endif
#ifdef MB_TESSELATION_SHADERS
		/**
		* Method to load and add a tesselation evaluation shader from file
		* @param source: Shader file source
		* @return Shader loaded
		*/
		bool loadTesselationEvaluationShader(const std::string& file);
		/**
		* Method to load and add a tesselation control shader from file
		* @param source: Shader file source
		* @return Shader loaded
		*/
		bool loadTesselationControlShader(const std::string& file);
#endif
#ifdef MB_COMPUTE_SHADERS
		/**
		* Method to load and add a computer shader from file
		* @param source: Shader file source
		* @return Shader loaded
		*/
		bool loadComputeShader(const std::string& file);
#endif
		/**
		* Method to load and add a vertex and fragment shaders from text
		* @param source: Vertex shader source
		* @param source: Fragment shader source
		* @return Shader loaded
		*/
		bool loadFromText(const std::string& vsSource, const std::string& fsSource);
		/**
		* Method to load and add a vertex shader from text
		* @param source: Shader source
		* @return Shader loaded
		*/
		bool loadVertexShaderFromText(const std::string& source);
		/**
		* Method to load and add a fragment shader from text
		* @param source: Shader source
		* @return Shader loaded
		*/
		bool loadFragmentShaderFromText(const std::string& source);
#ifdef MB_GEOMETRY_SHADERS
		/**
		* Method to load and add a geometry shader from text
		* @param source: Shader source
		* @return Shader loaded
		*/
		bool loadGeometryShaderFromText(const std::string& source);
#endif
#ifdef MB_TESSELATION_SHADERS
		/**
		* Method to load and add a tesselation evaluation shader from text
		* @param source: Shader source
		* @return Shader loaded
		*/
		bool loadTesselationEvaluationShaderFromText(const std::string& source);
		/**
		* Method to load and add a tesselation control shader from text
		* @param source: Shader source
		* @return Shader loaded
		*/
		bool loadTesselationControlShaderFromText(const std::string& source);
#endif
#ifdef MB_COMPUTE_SHADERS
		/**
		* Method to load and add a computer shader from text
		* @param source: Shader source
		* @return Shader loaded
		*/
		bool loadComputeShaderFromText(const std::string& source);
#endif
		/**
		* Method to compile a program
		* @return If program compile and link OK
		*/
		bool compileAndLink(void);
		/**
		* Method to get Program id
		* @return program identifier.
		*/
		unsigned int program(void) const;
		/**
		* Method to enable a program
		*/
		void use(void);
		/**
		* Method to disable a program (not necessary)
		*/
		void unuse(void);
		/**
		* Method to catching an attribute value of a vertex shader
		* @param attr: Attribute name
		*/
		void addAttribute(const std::string& attr);
		/**
		* Method to catching an array of attribute values of a vertex shader
		* @param attrs: Attribute vector names
		*/
		void addAttributes(const std::vector<char*> attrs);
		/**
		* Method to bind a specific index to a attribute value
		* @param attr: Attribute name
		* @param index: Attribute index
		*/
		void bindAttribute(const std::string& attr, unsigned int index);
		/**
		* Method to catching an uniform value.
		* @param uniform: Uniform name
		*/
		void addUniform(const std::string& uniform);
		/**
		* Method to catching an array of uniform values.
		* @param uniforms: Uniform vector names
		*/
		void addUniforms(const std::vector<char*> uniforms);
		/**
		* Method to bind a specific index to a uniform value
		* @param uniform: Uniform name
		* @param index: Uniform index
		*/
		void bindUniform(const std::string& uniform, unsigned int index);
		/**
		* Method to catching an uniform buffer object
		* @param _ubo: Uniform Buffer Object name
		*/
		void addUbo(const std::string& _ubo);
#ifdef MB_SUBPROGRAMS
		/**
		* Method to cathing a subprogram in a specific kind of shader
		* @param name: Subprogram name
		* @param shaderType: OpenGL Shader type
		*/
		void addSubroutine(const std::string& name, int shaderType);
#endif
		/**
		* Method to get a attribute index in cache
		* @param _attr: Attribute name
		* @return Attribute index
		*/
		unsigned int attribute(const std::string& _attr);
		/**
		* Method to get a uniform index in cache
		* @param _unif: Uniform name
		* @return Uniform index
		*/
		unsigned int uniform(const std::string& _unif);
		/**
		* Method to get a Uniform Buffer Object index in cache
		* @param _ubo: Uniform Buffer Object name
		* @return Uniform Buffer Object index
		*/
		unsigned int ubo(const std::string& _ubo);
		/**
		* Method to get a subprogram index of a specific kind of shader
		*    in cache
		* @param name: Subprogram name
		* @param shaderType: OpenGL Shader type
		* @return Subprogram index
		*/
		unsigned int subprogram(const std::string& name, int shaderType);
		/**
		* Method to get a attribute index in cache
		* @param _attr: Attribute name
		* @return Attribute index
		*/
		unsigned int operator( )(const std::string& _attr);
		/**
		* Method to get a uniform index in cache
		* @param _unif: Uniform name
		* @return Uniform index
		*/
		unsigned int operator[](const std::string& _unif);
		/**
		* Method to send a boolean
		* @param uniform: Uniform name
		* @param val: Boolean data
		*/
		void sendUniformb(const std::string& uniform, bool val);
		/**
		* Method to send an integer
		* @param uniform: Uniform name
		* @param v: Int data
		*/
		void sendUniformi(const std::string& uniform, int val);
		/**
		* Method to send an unsigned integer
		* @param uniform: Uniform name
		* @param val: Unsigned integer data
		*/
		void sendUniformu(const std::string& uniform, unsigned int val);
		/**
		* Method to send a float
		* @param uniform: Uniform name
		* @param val: Float data
		*/
		void sendUniformf(const std::string& uniform, float val);
		/**
		* Method to send a vec3 with separated data
		* @param uniform: Uniform name
		* @param x: First element
		* @param y: Second element
		* @param z: Third element
		*/
		void sendUniform(const std::string& uniform, float x, float y, float z);
		/**
		* Method to send a vec2
		* @param uniform: Uniform name
		* @param data: Data
		*/
		void sendUniform2v(const std::string& uniform, const std::vector< float > & data);
		/**
		* Method to send a vec2
		* @param uniform: Uniform name
		* @param data: Data
		*/
		void sendUniform2v(const std::string& uniform, const float* data);
		/**
		* Method to send a vec3
		* @param uniform: Uniform name
		* @param data: Data
		*/
		void sendUniform3v(const std::string& uniform, const std::vector< float > & data);
		/**
		* Method to send a vec3
		* @param uniform: Uniform name
		* @param data: Data
		*/
		void sendUniform3v(const std::string& uniform, const float* data);
		/**
		* Method to send a vec4
		* @param uniform: Uniform name
		* @param data: Data
		*/
		void sendUniform4v(const std::string& uniform, const std::vector< float > & data);
		/**
		* Method to send a vec4
		* @param uniform: Uniform name
		* @param data: Data
		*/
		void sendUniform4v(const std::string& uniform, const float* data);
		/**
		* Method to send a mat3
		* @param uniform: Uniform name
		* @param data: Data
		*/
		void sendUniform3m(const std::string& uniform, const std::vector< float > & data);
		/**
		* Method to send a mat3
		* @param uniform: Uniform name
		* @param data: Data
		*/
		void sendUniform3m(const std::string& uniform, const float* data);
		/**
		* Method to send a mat4
		* @param uniform: Uniform name
		* @param data: Data
		* @param inverse: Specifies whether to transpose
		*    the matrix as the values are loaded into the uniform variable
		*/
		void sendUniform4m(const std::string& uniform, 
			const std::vector< float > & m, bool inverse = false);
		/**
		* Method to send a mat4
		* @param uniform: Uniform name
		* @param data: Data
		* @param inverse: Specifies whether to transpose
		*    the matrix as the values are loaded into the uniform variable
		*/
		void sendUniform4m(const std::string& uniform, 
			const float* m, bool inverse = false);

#ifdef MB_SUBPROGRAMS
		/**
		* Method to active a subprogram in a specific shader
		* @param name: Subprogram name
		* @param shaderType: OpenGL Shader type
		*/
		void activeSubprogram(const std::string& name, int shaderType);
#endif

#ifdef MB_OCC_QUERY
		/**
		* Method to check if object is visible in frustrum
		* @return object is visible
		*/
		bool occlusionQuery(std::function<void()> renderFunc);
#endif

#ifdef MB_COMPUTE_SHADERS
		/**
		* Method to launch one or more compute work groups.
		* @param numGroupX: The number of work groups to be launched
		*                   in the X dimension.
		* @param numGroupY: The number of work groups to be launched
		*                   in the Y dimension.
		* @param numGroupZ: The number of work groups to be launched
		*                   in the Z dimension.
		*/
		void launchComputeWork(unsigned int numGroupX, unsigned int numGroupY,
			unsigned int numGroupZ);
#endif
#ifdef MB_TESSELATION_SHADERS
		/**
		* Method to get patch vertices.
		* @return Num of patches
		*/
		unsigned int getPatchVertices(void);
		/**
		* Method to get inner tesselation level.
		* @return Inner level
		*/
		float getInnerLevel(void);
		/**
		* Method to get outer tesselation level.
		* @return Outer level
		*/
		float getOuterLevel(void);
		/**
		* Method to set patch vertices.
		* @param numPatches: Num of patches
		*/
		void setPatchVertices(unsigned int numPatches);
		/**
		* Method to set inner tesselation level.
		* @param level: Inner level
		*/
		void setInnerLevel(float level);
		/**
		* Method to set outer tesselation level.
		* @param level: Outer level
		*/
		void setOuterLevel(float level);
#endif
#ifdef MB_GEOMETRY_SHADERS
		/**
		* Method to get max output vertices.
		* @return int: Máx. num of vertices
		*/
		int getGeometryMaxOutput(void);
		/**
		* Method to get max input geometry type.
		* @return int: Input geometry type
		*/
		int getGeometryInputType(void);
		/**
		* Method to get output geometry type.
		* @return int: Output geometry type
		*/
		int getGeometryOutputType(void);
		/**
		* Method to set max output vertices.
		* @param maxValue: Max. num of vertices
		*/
		void setGeometryMaxOutput(unsigned int maxValue);
		/**
		* Method to set input geometry type.
		* @param inputValue: Input geometry type
		*/
		void setGeometryInputType(unsigned int inputValue);
		/**
		* Method to set output geometry type.
		* @param outputType: Output geometry type
		*/
		void setGeometryOutputType(unsigned int outputType);
#endif
		/**
		* Method to create program and attach all shaders
		*/
		void create(void);
		/**
		* Method to link program and check status
		*/
		bool link(void);
	protected:
		void _destroy();
		bool _load(const std::string& file, int type);
		bool _loadFromText(const std::string& source, int type);

		unsigned int _program;
		std::map<std::string, unsigned int> _attrsList;
		std::map<std::string, unsigned int> _uniformList;
		std::map<std::string, unsigned int> _uboList;

#ifdef MB_SUBPROGRAMS
		typedef struct SubProgram
		{
			const char* name;
			unsigned int index;
			SubProgram(const char* n, unsigned int i)
			{
				this->name = n;
				this->index = i;
			}
		} SubProgram;
		std::multimap<int, SubProgram> _subprograms;
#endif
		std::vector<unsigned int> _shaders;

#ifdef MB_OCC_QUERY
		unsigned int _occQuery;
#endif
	};
}

#endif /* __MB_PROGRAM__ */