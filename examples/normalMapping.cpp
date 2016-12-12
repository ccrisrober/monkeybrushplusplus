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

void renderFunc(float dt);

class NormalController : public mb::Component
{
public:
	NormalController(const float& normalScale)
		: mb::Component()
		, _normScale(normalScale) 
	{
	}
	virtual void update(const float) override
	{
		if (mb::Input::isKeyPressed(mb::Keyboard::Key::Plus))
		{
			_normScale += 0.1f;
			getNode()->getMesh()->getMaterial()->uniform("normalScale")->value(_normScale);
		}
		if (mb::Input::isKeyPressed(mb::Keyboard::Key::Minus))
		{
			_normScale -= 0.1f;
			getNode()->getMesh()->getMaterial()->uniform("normalScale")->value(_normScale);
		}
	}
	MB_SYNTHESIZE_PASS_BY_REF(float, _normScale, normalScale)
};

mb::ShaderMaterial* material;
int main(void)
{
	mb::GLContext context(3, 3, 1024, 768, "Normal mapping");

    auto engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine,
		new mb::SimpleCamera(mb::Vect3(0.2f, 0.18f, 8.44f)));

	mb::Drawable* model = new mb::Cube(2.0f);

	std::vector<std::pair<mb::ShaderType, const char*> > shaders = {
		{
			mb::VertexShader,
			"#version 330\n"
			"layout(location = 0) in vec3 position;\n"
			"layout(location = 1) in vec3 normal;\n"
			"layout(location = 2) in vec2 uv;\n"
			"out vec3 outPosition;\n"
			"out vec2 outUV;\n"
			"uniform mat4 projection;\n"
			"uniform mat4 view;\n"
			"uniform mat4 model;\n"
			"out vec3 outNormal;\n"
			"void main() {\n"
			"	outPosition = vec3(view * model * vec4(position, 1.0));\n"
			"	gl_Position = projection * vec4(outPosition, 1.0);\n"
			"	outUV = uv;\n"
			"	outNormal = normal;\n"
			"}"
		},{
			mb::FragmentShader,
			"#version 330\n"
			"in vec3 outPosition;\n"
			"in vec2 outUV;\n"
			"out vec4 fragColor;\n"
			"uniform sampler2D texNormal;\n"
			"uniform sampler2D texDiffuse;\n"
			"uniform mat4 view;\n"
			"uniform float normalScale;\n"
			"uniform vec3 viewPos;\n"
			"in vec3 outNormal;\n"
			"// Code based on http://www.thetenthplanet.de/archives/1180\n"
			"vec3 perturb_normal(vec3 p, vec3 n) {\n"
			"    vec3 dp1 = dFdx(p);\n"
			"    vec3 dp2 = dFdy(p);\n"
			"    vec2 duv1 = dFdx(outUV);\n"
			"    vec2 duv2 = dFdy(outUV);\n"
			"    vec3 S = normalize(dp1 * duv2.t - dp2 * duv1.t);\n"
			"    vec3 T = normalize(-dp1 * duv2.s + dp2 * duv1.s);\n"
			"    vec3 N = normalize(n);\n"
			"    vec3 mapN = texture(texNormal, outUV).xyz * 2.0 - 1.0;\n"
			"    mapN.xy = normalScale * mapN.xy;\n"
			"    mat3 tsn = mat3(S, T, N);\n"
			"    return normalize(tsn * mapN);\n"
			"}\n"
			"void main() {\n"
		"    vec3 lightPosition = vec3(view * vec4(2.0, 15.0, 15.0, 1.0));\n"
		"    vec3 color = texture(texDiffuse, outUV).rgb;\n"
		"    // Ambient\n"
		"    vec3 ambient = vec3(0.4);\n"
		"    // Diffuse\n"
		"    vec3 norm = normalize(outNormal);\n"
		"    norm = perturb_normal(-outPosition, norm);\n"
		"    vec3 lightDir = normalize(lightPosition - outPosition);\n"
		"    float diff = max(dot(norm, lightDir), 0.0);\n"
		"    vec3 diffuse = vec3(1.0, 1.0, 0.0) * diff;\n"
		"    // Specular\n"
		"    vec3 viewDir = normalize(viewPos - outPosition);\n"
		"    vec3 reflectDir = reflect(-lightDir, norm);\n"
		"    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128.0);\n"
		"    vec3 specular = vec3(spec);\n"
		"    fragColor = vec4((ambient + diffuse + specular) * color, 1.0);\n"
			"}\n"
		}
	};
	mb::Texture* texDiffuse = new mb::Texture2D({}, MB_TEXTURE_ASSETS + std::string("/chesterfieldDiffuseMap.png"));
	mb::Texture* texNormal = new mb::Texture2D({}, MB_TEXTURE_ASSETS + std::string("/chesterfieldNormalMap.png"));

	float normalScale = 1.0f;

	std::vector<std::pair<const char*, mb::Uniform*> > uniforms = {
		std::make_pair("projection", new mb::Uniform(mb::Matrix4)),
		std::make_pair("view", new mb::Uniform(mb::Matrix4)),
		std::make_pair("model", new mb::Uniform(mb::Matrix4)),
		std::make_pair("viewPos", new mb::Uniform(mb::Vector3)),
		std::make_pair("normalScale", new mb::Uniform(mb::Float, normalScale)),
		std::make_pair("texDiffuse", new mb::Uniform(mb::TextureSampler, texDiffuse)),
		std::make_pair("texNormal", new mb::Uniform(mb::TextureSampler, texNormal)),
	};

	material = new mb::ShaderMaterial("material", shaders, uniforms);
	auto mbModel = new mb::Node(std::string("model"));
	mbModel->addComponent(new mb::MeshRenderer(model, material));
	mbModel->addComponent(new mb::RotateComponent(mb::Axis::y, 0.15f));
	mbModel->addComponent(new NormalController(normalScale));
	mbModel->getComponent<mb::RotateComponent>()->setRotate(true);

	scene->root()->addChild(mbModel);

	engine->run(renderFunc);
    
	delete(scene);
	delete(engine);

    return 0;
}
#include <FreeImage.h>

#define WIDTH 1024
#define HEIGHT 768
BYTE pixels[3 * WIDTH*HEIGHT];
void renderFunc(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->render(dt);
}
