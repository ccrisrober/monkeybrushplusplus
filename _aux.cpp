#include <iostream>

#include "Includes.hpp"

#include "cameras/Camera.hpp"
#include "cameras/PerspectiveCamera.hpp"
#include "cameras/OrthographicCamera.hpp"


#include "others/Exception.hpp"
#include "resources/ResourceShader.hpp"
#include "resources/ResourceDrawable.hpp"


#include "maths/Sphere2D.hpp"
#include "maths/Sphere3D.hpp"
#include "maths/Box2D.hpp"
#include "maths/Box3D.hpp"
#include "maths/Curves.hpp"
#include "maths/Spline.hpp"


#include "core/GeometryFunctions.hpp"
#include "core/GLContext.hpp"
#include "extras/CustomPingPong.hpp"
#include "materials/PostProcessMaterial.hpp"
#include "core/Query.hpp"
#include "scene/Engine.hpp"
#include "scene/Node.hpp"
#include "maths/Vect3.hpp"
#include "maths/Mathf.hpp"
#include "textures/Texture.hpp"
#include "textures/Texture2D.hpp"
#include "textures/Texture2DArray.hpp"
#include "textures/Texture3D.hpp"
#include "constants/Constants.hpp"
#include "core/Input.hpp"
#include "core/VertexArray.hpp"
#include "core/VertexBuffer.hpp"
#include "scene/Scene.hpp"
#include "scene/MeshRenderer.hpp"
#include "core/Color3.hpp"
#include "models/Cube.hpp"
#include "models/Disc.hpp"
#include "models/Capsule.hpp"
#include "models/Cylinder.hpp"
#include "models/Torus.hpp"
#include "models/Prism.hpp"
#include "materials/NormalMaterial.hpp"
#include "materials/SimpleShadingMaterial.hpp"
#include "materials/ShaderMaterial.hpp"
#include "utils/any.hpp"
#include "extras/Easing.hpp"
#include "extras/EventDispatcher.hpp"


/*
http://gamedev.stackexchange.com/questions/55950/entity-component-systems-with-c-accessing-components
#include <typeinfo>
#include <typeindex>

std::unordered_map<std::type_index, std::shared_ptr<MB::Component> > components2;

template <typename T>
std::shared_ptr<T> getComponent2()
{
	std::type_index index(typeid(T));
	if (components2.count(std::type_index(typeid(T)) != 0))
	{
		return static_pointer_cast<T>(components2[index]);
	}
	else
	{
		return nullptr;
	}
}

components2[std::type_index(typeid(*component2))] = component2;
*/

MB::Engine* engine;
MB::Scene* scene;
MB::Drawable* cube;
MB::Capsule* capsule;
MB::Cylinder* cylinder;
MB::Prism* prism;
void renderFunc(float dt);

MB::PostProcessMaterial* ppm;

int main(void)
{
    MB::GLContext context(3, 3, 1024, 768, "Hello MB");

	ppm = new MB::PostProcessMaterial(
		"#version 330\n"
		"uniform vec3 color;\n"
		"out vec4 fragColor;\n"
		"in vec2 uv;\n"
		""
		"void main()\n"
		"{\n"
		"    fragColor = vec4(uv, 0.5, 1.0);\n"
		"}\n");

	MB::SimpleShadingMaterial material;
	material.uniform("color")->value(MB::Vect3(MB::Color3::Red));
	MB::SimpleShadingMaterial material2;
	material2.uniform("color")->value(MB::Vect3(MB::Color3::Gold));
	MB::SimpleShadingMaterial material3;
	material3.uniform("color")->value(MB::Vect3(MB::Color3::Blue));
	MB::SimpleShadingMaterial material4;
	material4.uniform("color")->value(MB::Vect3(MB::Color3::Green));
	MB::NormalMaterial material6;

	unsigned int texSize = 1024;
	unsigned int *data = new unsigned int[texSize * texSize * 3];
	unsigned int n = 0;
	// Generate some checker board pattern
	for (unsigned int yy = 0; yy < texSize; ++yy) {
		for (unsigned int xx = 0; xx < texSize; ++xx) {
			if ((xx + yy) / 4 % 4 == 1) {
				data[n++] = 128;
				data[n++] = 128;
				data[n++] = 128;
			}
			else {
				data[n++] = 255;
				data[n++] = 255;
				data[n++] = 255;
			}
		}
	}
	MB::TexOptions options;
	options.internalFormat = GL_RGB8;
	options.format = GL_RGB;
	options.type = GL_UNSIGNED_BYTE;
	MB::Texture* tex = new MB::Texture2D(options, data, texSize, texSize);

	std::vector<std::pair<MB::ShaderType, const char*> > shaders;
	const char* vertexShader = 
		"#version 330\n"
		"layout(location = 0) in vec3 position;"
		"layout(location = 1) in vec3 normal;"
		"out vec3 outPosition;"
		"out vec3 outNormal;"
		"uniform mat4 projection;"
		"uniform mat4 view;"
		"uniform mat4 model;"
		"void main() {"
		"	outPosition = vec3(model * vec4(position, 1.0));"
		"	gl_Position = projection * view * vec4(outPosition, 1.0);"
		"	mat3 normalMatrix = mat3(inverse(transpose(model)));"
		"	outNormal = normalize(normalMatrix * normal);"
		"}";
	const char* fragmentShader =
		"#version 330\n"
		"in vec3 outPosition;"
		"in vec3 outNormal;"
		"out vec4 fragColor;"
		"uniform vec3 viewPos;"
		"uniform vec3 color;"
		"void main() {"
		"	vec3 N = normalize(outNormal);"
		"	vec3 L = normalize(viewPos - outPosition);"
		"	float dif = dot(N, L);"
		"	dif = clamp(dif, 0.0, 1.0);"
		"	fragColor = vec4(color * dif, 1.0) + vec4(color * 0.1, 1.0);"
		"}";

	shaders.push_back(std::make_pair(MB::VertexShader, vertexShader));
	shaders.push_back(std::make_pair(MB::FragmentShader, fragmentShader));


	std::vector<std::pair<const char*, MB::Uniform*> > uniforms;
	uniforms.push_back(std::make_pair("projection", new MB::Uniform(MB::Matrix4)));
	uniforms.push_back(std::make_pair("view", new MB::Uniform(MB::Matrix4)));
	uniforms.push_back(std::make_pair("model", new MB::Uniform(MB::Matrix4)));
	uniforms.push_back(std::make_pair("color", new MB::Uniform(MB::Vector3, MB::Vect3::createFromScalar(1.0f))));
	uniforms.push_back(std::make_pair("viewPos", new MB::Uniform(MB::Vector3)));

	MB::ShaderMaterial material5(shaders, uniforms);

	cube = new MB::Cube(1.0f);
	capsule = new MB::Capsule(1.0f);
	cylinder = new MB::Cylinder(1.0f, 1.5f, 25, 15);
	MB::ResourceDrawable::add("torito", new MB::Torus(0.5f, 0.25f, 25, 40));
	prism = new MB::Prism(1.0f, 1.5f, 5);

	MB::Node* mbCube = new MB::Node(std::string("cube"));
	mbCube->addComponent(new MB::MeshRenderer(cube, &material));
	mbCube->addComponent(new MoveComponent());
	mbCube->addComponent(new RotateComponent(Axis::z));

	auto cmps = mbCube->getComponents();
	//mbCube->addComponent(new ScaleComponent());
	//mbCube->addComponent(new PrintPosition());

	mbCube->transform().position().set(0.0f, 3.15f, -8.98f);
	mbCube->transform().scale().set(2.0f, 2.0f, 1.0f);
	//mbCube->transform().rotation().set(0.0f, 1.0f, 0.0f);

	MB::Node* mbSphere = new MB::Node(std::string("sphere"));
    mbSphere->addComponent(new MB::MeshRenderer(prism, &material6));

	mbSphere->transform().position().set(-0.44f, -2.0f, 2.35f);
	mbSphere->transform().scale().set(0.5f, 0.5f, 1.0f);

	//mbSphere->setEnabled(false);

	mbCube->addChild(mbSphere);

	MB::Node* mbCapsule = new MB::Node(std::string("capsule"));
    mbCapsule->addComponent(new MB::MeshRenderer(capsule, &material3));

	mbCapsule->transform().position().set(-1.44f, -2.5f, 0.87f);

	mbSphere->addChild(mbCapsule);

	MB::Node* mbCylinder = new MB::Node(std::string("cylinder"));
    mbCylinder->addComponent(new MB::MeshRenderer(MB::ResourceDrawable::get("torito"), &material6));

	mbCylinder->transform().position().set(1.1f, -1.91f, -1.08f);
	mbCylinder->transform().scale().set(1.0f, 0.5f, 1.0f);

	mbCube->addChild(mbCylinder);

	MB::Node* mbCapsule2 = new MB::Node(std::string("capsule2"));
    mbCapsule2->addComponent(new MB::MeshRenderer(cylinder, &material6));

	mbCapsule2->transform().position().set(1.44f, -2.5f, 0.8f);
	mbCapsule2->transform().scale().set(0.5f, 1.0f, 2.0f);

	mbCylinder->addChild(mbCapsule2);

    engine = new MB::Engine(&context, false);
	scene = new MB::Scene();
	scene->root()->addChild(mbCube);

	engine->run(renderFunc);
    
	delete(scene);
	delete(engine);

    return 0;
}

void renderFunc(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->camera->update(dt);
	if (MB::Input::isKeyPressed(GLFW_KEY_ESCAPE))
	{
		engine->close();
		return;
	}
	if (MB::Input::isKeyClicked(GLFW_KEY_Z))
	{
		std::cout << "DEPTH OFF" << std::endl;
		engine->state()->depth.setStatus(false);
	}
	if (MB::Input::isKeyClicked(GLFW_KEY_X))
	{
		std::cout << "DEPTH OK" << std::endl;
		engine->state()->depth.setStatus(true);
	}
	if (MB::Input::isKeyClicked(GLFW_KEY_K))
	{
		engine->state()->culling.setStatus(false);
	}
	if (MB::Input::isKeyClicked(GLFW_KEY_L))
	{
		engine->state()->culling.setStatus(true);
	}
	if (MB::Input::isKeyClicked(GLFW_KEY_M))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (MB::Input::isKeyClicked(GLFW_KEY_N))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	scene->render(dt);
	//ppm->renderPP();
}
