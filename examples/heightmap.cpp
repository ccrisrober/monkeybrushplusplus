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

#include <iostream>
#include <mb/mb.h>
#include <assetsFiles.h>

mb::Scene* scene;

class HeightMapController : public mb::Component
{
public:
  HeightMapController(const float& amount)
    : mb::Component()
    , _amount(amount) {}
  virtual void update(const float) override
  {
    if (mb::Input::isKeyPressed(mb::Keyboard::Key::Plus))
    {
      _amount -= 0.1f;
      getNode()->getMesh()->getMaterial()->uniform("amount")->value(_amount);
    }
    if (mb::Input::isKeyPressed(mb::Keyboard::Key::Minus))
    {
      _amount += 0.1f;
      getNode()->getMesh()->getMaterial()->uniform("amount")->value(_amount);
    }
  }
protected:
  float _amount;
};

class HeightmapMaterial : public mb::Material
{
public:
	HeightmapMaterial(const float& amount = 5.0f)
		: mb::Material()
	{
		_uniforms["projection"] = new mb::Uniform(mb::Matrix4);
		_uniforms["view"] = new mb::Uniform(mb::Matrix4);
		_uniforms["model"] = new mb::Uniform(mb::Matrix4);
		_uniforms["amount"] = new mb::Uniform(mb::Float, amount);
		_uniforms["tex"] = new mb::Uniform(mb::TextureSampler, nullptr);
		
		const char* vsShader = "#version 330\n"
			"layout(location = 0) in vec3 position;\n"
			"layout(location = 1) in vec3 normal;\n"
			"layout(location = 2) in vec2 uv;\n"
			""
			"out vec2 outUV; \n"
			""
			"uniform mat4 projection; \n"
			"uniform mat4 view; \n"
			"uniform mat4 model; \n"
			"uniform float amount; \n"
			"uniform sampler2D tex; \n"
			"void main() {\n"
			"	mat3 normalMatrix = mat3(inverse(transpose(model))); \n"
			"	vec3 pos = position; \n"
			"	outUV = uv; \n"
			"	const vec2 size = vec2(0.5, 0.0); \n"
			"	const ivec3 off = ivec3(-1, 0, 1); \n"
			"	vec4 wave = texture(tex, outUV); \n"
			"	float s11 = wave.x; \n"
			"	float s01 = textureOffset(tex, outUV, off.xy).x; \n"
			"	float s21 = textureOffset(tex, outUV, off.zy).x; \n"
			"	float s10 = textureOffset(tex, outUV, off.yx).x; \n"
			"	float s12 = textureOffset(tex, outUV, off.yz).x; \n"
			"	vec3 va = normalize(vec3(size.xy, s21 - s01)); \n"
			"	vec3 vb = normalize(vec3(size.yx, s12 - s10)); \n"
			"	vec4 bump = vec4(cross(va, vb), s11); \n"
			"	pos.y += amount * bump.w; \n"
			"	vec4 pp = model * vec4(pos, 1.0); \n"
			"	pp = view * pp; \n"
			"	gl_Position = projection * pp; \n"
			"}\n";
		const char* fsShader = "#version 330\n"
			"in vec2 outUV;\n"
			"uniform sampler2D tex;\n"
			"out vec4 fragColor;\n"
			"void main() {\n"
			"	fragColor = texture(tex, outUV);\n"
			"};\n";
		_program->loadFromText(vsShader, fsShader);
		_program->compileAndLink();
		_program->autocatching();

    Cull = false;
	}
};

void renderFunc(float dt);

int main()
{
  mb::GLContext context(3, 3, 1024, 768, "Heightmap");

  auto engine = new mb::Engine(&context, false);
  scene = new mb::Scene(engine, new mb::SimpleCamera(mb::Vect3(-0.6f, 5.0f, 14.8f)));

  float amount = 5.0f;
	auto mbNode = new mb::Node("plane");
	mb::Drawable* plane = new mb::Plane(26.0f, 20.0f, 200, 200);
	mbNode->addComponent(new mb::MeshRenderer(plane, 
    new HeightmapMaterial(amount)));
  mbNode->addComponent(new HeightMapController(amount));

	scene->root()->addChild(mbNode);

	mb::TexOptions opts;
	opts.minFilter = mb::ctes::TextureFilter::Nearest;
	opts.magFilter = mb::ctes::TextureFilter::Nearest;
	opts.wrapS = mb::ctes::WrapMode::Clamp2Edge;
	opts.wrapT = mb::ctes::WrapMode::Clamp2Edge;
	mb::Texture* tex = new mb::Texture2D(opts, 
		MB_TEXTURE_ASSETS + std::string("/heightmap.jpg"));
	
	mbNode->getMesh()->getMaterial()->uniform("tex")->value(tex);

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
