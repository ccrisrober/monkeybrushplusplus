#include "Includes.hpp"
#include "core/GLContext.hpp"
#include "scene/Engine.hpp"
#include "scene/MeshRenderer.hpp"
#include "scene/Scene.hpp"

#include "resources/MaterialCache.hpp"
#include "resources/ResourceDrawable.hpp"

#include "materials/ShaderMaterial.hpp"
#include "materials/NormalMaterial.hpp"
#include "materials/SimpleShadingMaterial.hpp"

#include "models/Capsule.hpp"
#include "models/Cube.hpp"
#include "models/Cylinder.hpp"
#include "models/Prism.hpp"
#include "models/Torus.hpp"

MB::Engine* engine;
MB::Scene* scene;

MB::Cube* cube;
MB::Cylinder* cylinder;
MB::Prism* prism;

void renderFunc(float dt);

#include "Helpers.hpp"

int main(void)
{
	MB::LOG::headers = false;
	MB::LOG::level = MB::LOG::INFO;
	MB::LOG::date = true;

    MB::GLContext context(3, 3, 1024, 768, "Hello MB");

    engine = new MB::Engine(&context, false);
	scene = new MB::Scene();

	MB::ResourceDrawable::add("capsule", new MB::Capsule(0.5f, 1.0f));

	cube = new MB::Cube(1.0f);
	cylinder = new MB::Cylinder(1.0f, 1.5f, 25, 15);
	prism = new MB::Prism(1.0f, 1.5f, 5);
	MB::ResourceDrawable::add("torus", new MB::Torus(0.5f, 0.25f, 25, 40));

	MB::SimpleShadingMaterial material;
	material.uniform("color")->value(MB::Vect3(MB::Color3::Red));
	MB::NormalMaterial normalMat;

	std::vector<std::pair<MB::ShaderType, const char*> > shaders;
	const char* vertexShader =
		"#version 330\n"
		"layout(location = 0) in vec3 position;"
		"layout(location = 1) in vec3 normal;"
		"layout(location = 2) in vec2 texCoord;"
		"out vec3 outPosition;"
		"out vec3 outNormal;"
		"out vec2 outTexCoord;"
		"uniform mat4 projection;"
		"uniform mat4 view;"
		"uniform mat4 model;"
		"void main() {"
		"	outPosition = vec3(model * vec4(position, 1.0));"
		"	gl_Position = projection * view * vec4(outPosition, 1.0);"
		"	mat3 normalMatrix = mat3(inverse(transpose(model)));"
		"	outNormal = normalize(normalMatrix * normal);"
		"	outTexCoord = texCoord;"
		"}";
	const char* fragmentShader =
		"#version 330\n"
		"in vec3 outPosition;"
		"in vec3 outNormal;"
		"in vec2 outTexCoord;"
		"out vec4 fragColor;"
		"uniform vec3 viewPos;"
		"uniform vec3 color;"
		"void main() {"
		"	vec3 N = normalize(outNormal);"
		"	vec3 L = normalize(viewPos - outPosition);"
		"	float dif = dot(N, L);"
		"	dif = clamp(dif, 0.0, 1.0);"
		"	fragColor = vec4(color * dif, 1.0) + vec4(color * 0.1, 1.0);"
		"	fragColor.rgb -= vec3(outTexCoord, 0.0);"
		"}";

	shaders.push_back(std::make_pair(MB::VertexShader, vertexShader));
	shaders.push_back(std::make_pair(MB::FragmentShader, fragmentShader));


	std::vector<std::pair<const char*, MB::Uniform*> > uniforms;
	uniforms.push_back(std::make_pair("projection", new MB::Uniform(MB::Matrix4)));
	uniforms.push_back(std::make_pair("view", new MB::Uniform(MB::Matrix4)));
	uniforms.push_back(std::make_pair("model", new MB::Uniform(MB::Matrix4)));
	uniforms.push_back(std::make_pair("color", new MB::Uniform(MB::Vector3, MB::Vect3::createFromScalar(1.0f))));
	uniforms.push_back(std::make_pair("viewPos", new MB::Uniform(MB::Vector3)));

	MB::ShaderMaterial shaderMat("shaderMat", shaders, uniforms);

	MB::Node* mbCube = new MB::Node(std::string("cube"));
	mbCube->addComponent(new MB::MeshRenderer(cube, MB::MaterialCache::get("shaderMat")));
	mbCube->addComponent(new MoveComponent());
	mbCube->addComponent(new RotateComponent(Axis::x));
	mbCube->transform().position().set(0.0f, 3.15f, -8.98f);
	mbCube->transform().scale().set(2.0f, 2.0f, 1.0f);

	MB::Node* mbPrism = new MB::Node(std::string("prism"));
	mbPrism->addComponent(new MB::MeshRenderer(prism, &normalMat));
	mbPrism->transform().position().set(-0.44f, -2.0f, 2.35f);
	mbPrism->transform().scale().set(0.5f, 0.5f, 1.0f);
	mbCube->addChild(mbPrism);

	MB::Node* mbCapsule = new MB::Node(std::string("capsule"));
	mbCapsule->addComponent(new MB::MeshRenderer(MB::ResourceDrawable::get("capsule"), &normalMat));
	mbCapsule->transform().position().set(-1.44f, -2.5f, 0.87f);
	mbPrism->addChild(mbCapsule);

	MB::Node* mbTorus = new MB::Node(std::string("torus"));
	mbTorus->addComponent(new MB::MeshRenderer("torus", &normalMat));
	mbTorus->transform().position().set(1.1f, -1.91f, -1.08f);
	mbTorus->transform().scale().set(1.0f, 0.5f, 1.0f);
	mbCube->addChild(mbTorus);

	MB::Node* mbCylinder = new MB::Node(std::string("cylinder"));
	mbCylinder->addComponent(new MB::MeshRenderer(cylinder, &material));
	mbCylinder->transform().position().set(1.44f, -2.5f, 0.8f);
	mbCylinder->transform().scale().set(0.5f, 1.0f, 2.0f);
	mbTorus->addChild(mbCylinder);

	std::function<void()> f0([&]() {
		std::cout << "SCENE HAS " << scene->root()->children().size() << " CHILDREN" << std::endl;
	});

	std::function<void()> f1([&]() {
		MB::LOG(MB::LOG::INFO) << "FIRST RENDER FINISHED";
	});

	scene->registerBeforeRender(f0);
	scene->registerAfterRender(f1);

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
		engine->state()->setPolygonMode(GL_FILL);
	}
	if (MB::Input::isKeyClicked(GLFW_KEY_N))
	{
		engine->state()->setPolygonMode(GL_LINE);
	}
	if (MB::Input::isKeyClicked(GLFW_KEY_1))
	{
		engine->state()->culling.setFlipSided(GL_CCW);
	}
	if (MB::Input::isKeyClicked(GLFW_KEY_2))
	{
		engine->state()->culling.setFlipSided(GL_CW);
	}
	scene->render(dt);
}
