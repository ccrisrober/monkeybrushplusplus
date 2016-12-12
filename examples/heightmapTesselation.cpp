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

#include <iostream>
#include <mb/mb.h>
#include <assetsFiles.h>

mb::Engine* engine;
mb::Scene* scene;

void renderFunc(float dt);

class ChangeTessLevelComponent : public mb::Component
{
public:
	ChangeTessLevelComponent(const float& tessLevel)
		: mb::Component()
		, _tessLevel(tessLevel)
	{
	}
	virtual void update(const float) override
	{
		if (mb::Input::isKeyPressed(mb::Keyboard::Key::Plus))
		{
			_tessLevel += 0.1f;
			getNode()->getMesh()->getMaterial()->uniform("tess_level")
				->value(_tessLevel);
		}
		else if (mb::Input::isKeyPressed(mb::Keyboard::Key::Minus))
		{
			_tessLevel -= 0.1f;
			getNode()->getMesh()->getMaterial()->uniform("tess_level")
				->value(_tessLevel);
		}
	}
protected:
	float _tessLevel;
};

int main(void)
{
	mb::GLContext context(4, 4, 1024, 768, "Heightmap tesselation");

	auto engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine, 
		new mb::SimpleCamera(mb::Vect3(0.2f, 0.18f, 8.44f)));

	mb::Drawable* model = new mb::Plane(26.0f, 20.0f, 50, 50);

	std::vector<std::pair<mb::ShaderType, const char*> > shaders = {
		{
			mb::VertexShader,
			R"(#version 440
			layout(location = 0) in vec3 position;
			layout(location = 2) in vec2 uv;
			out vec2 outUV;
			void main() {
				gl_Position = vec4(position, 1.0f);
				outUV = uv;
			})"
		},{
			mb::TesselationControlShader,
			R"(#version 440
			layout (vertices = 3) out;
			uniform float tess_level;
			#define ID gl_InvocationID
			in vec2 outUV[];
			out vec2 uv[];
			void main(void) {
			    if (ID == 0) {
			        gl_TessLevelInner[0] = tess_level;
			        gl_TessLevelOuter[0] = tess_level;
			        gl_TessLevelOuter[1] = tess_level;
			        gl_TessLevelOuter[2] = tess_level;
			    }
			    gl_out[ID].gl_Position = gl_in[ID].gl_Position;
			uv[ID] = outUV[ID];
			})"
		},{
			mb::TesselationEvaluationShader,
			R"(#version 440
			layout (triangles) in;
			uniform mat4 projection;
			uniform mat4 view;
			uniform mat4 model;
			uniform float amount;
			in vec2 uv[];
			out vec2 outUV;
			uniform sampler2D texHeightmap;
			void main(void) {

			    vec4 pos = (gl_TessCoord.x * gl_in[0].gl_Position) +
			                  (gl_TessCoord.y * gl_in[1].gl_Position) +
			                  (gl_TessCoord.z * gl_in[2].gl_Position);
			    outUV = (gl_TessCoord.x * uv[0]) +
			                  (gl_TessCoord.y * uv[1]) +
			                  (gl_TessCoord.z * uv[2]);

				const vec2 size = vec2(0.25, 0.0);
				const ivec3 off = ivec3(-1, 0, 1);
				vec4 wave = texture(texHeightmap, outUV);
				float s11 = wave.x;
				float s01 = textureOffset(texHeightmap, outUV, off.xy).x;
				float s21 = textureOffset(texHeightmap, outUV, off.zy).x;
				float s10 = textureOffset(texHeightmap, outUV, off.yx).x;
				float s12 = textureOffset(texHeightmap, outUV, off.yz).x;
				vec3 va = normalize(vec3(size.xy, s21 - s01));
				vec3 vb = normalize(vec3(size.yx, s12 - s10));
				vec4 bump = vec4(cross(va, vb), s11);
				pos.y += amount * bump.w;

				gl_Position = projection * view * model * pos;
			})"
		},{
			mb::FragmentShader,
			R"(#version 440
			out vec4 fragColor;
			uniform vec3 color;
			uniform sampler2D texDiffuse;
			in vec2 outUV;
			void main() {
				fragColor = vec4(outUV, 0.0, 1.0);
				fragColor = texture(texDiffuse, outUV);
			})"
		}
	};

	float tess_level = 2.0f;

	mb::TexOptions opts;
	opts.minFilter = mb::ctes::TextureFilter::Nearest;
	opts.magFilter = mb::ctes::TextureFilter::Nearest;
	opts.wrapS = mb::ctes::WrapMode::Clamp2Edge;
	opts.wrapT = mb::ctes::WrapMode::Clamp2Edge;
	mb::Texture* tex = new mb::Texture2D(opts,
		MB_TEXTURE_ASSETS + std::string("/Srtm_ramp2.world.21600x10800.jpg"));

	mb::Texture* tex2 = new mb::Texture2D(opts,
		MB_TEXTURE_ASSETS + std::string("/3_no_ice_clouds_8k.jpg"));

	std::vector<std::pair<const char*, mb::Uniform*> > uniforms = {
		std::make_pair("projection", new mb::Uniform(mb::Matrix4)),
		std::make_pair("view", new mb::Uniform(mb::Matrix4)),
		std::make_pair("model", new mb::Uniform(mb::Matrix4)),
		std::make_pair("color", new mb::Uniform(mb::Vector3, mb::Vect3(mb::Color3::Pink))),
		std::make_pair("tess_level", new mb::Uniform(mb::Float, tess_level)),
		std::make_pair("amount", new mb::Uniform(mb::Float, 1.05f)),
		std::make_pair("texHeightmap", new mb::Uniform(mb::TextureSampler, tex)),
		std::make_pair("texDiffuse", new mb::Uniform(mb::TextureSampler, tex2)),
	};

	mb::ShaderMaterial material("triangleTesselation", shaders, uniforms);
	material.Cull = false;
	material.PolygonMode = GL_LINE;

	auto mbModel = new mb::Node(std::string("model"));
	mbModel->addComponent(new mb::MeshRendererTesselation(model, &material));
	mbModel->addComponent(new ChangeTessLevelComponent(tess_level));

	scene->root()->addChild(mbModel);

	engine->run(renderFunc);

	delete(scene);
	delete(engine);

	return 0;
}

void renderFunc(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->render(dt);
}
