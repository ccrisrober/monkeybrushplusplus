#include <iostream>

#include "Includes.hpp"

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
#include "models/Drawable.hpp"
#include "materials/SimpleShadingMaterial.hpp"
#include "utils/any.hpp"
#include "extras/Easing.hpp"
#include "extras/EventDispatcher.hpp"

class MoveComponent : public MB::Component
{
public:
	MoveComponent()
		: MB::Component()
		, _delta(0.01f)
		, _sign(1)
	{
		std::cout << "Creando MoveComponent component" << std::endl;
	}
	virtual void update(float /*dt*/)
	{
		if (this->_delta > 2.5f || this->_delta < -2.5f) {
			this->_sign *= -1;
		}
		this->_delta += 0.025 * this->_sign;
		this->_node->transform().position().x(this->_delta);
	}
protected:
	float _delta;
	int _sign;
};

class ScaleComponent : public MB::Component
{
public:
	ScaleComponent()
	: MB::Component()
		, _inc(0.0f)
	{
		std::cout << "Creando ScaleComponent component" << std::endl;
	}
	virtual void update(float /*dt*/)
	{
		this->_node->transform().scale().set(
			this->_inc * 0.01,
			this->_inc * 0.01,
			this->_inc * 0.01
		);
		this->_inc += 1.0f;
	}
protected:
	float _inc;
};

class PrintPosition : public MB::Component
{
public:
	PrintPosition()
	: MB::Component()
	{
		std::cout << "Creando PrintPosition component" << std::endl;
	}
	virtual void update(float /*dt*/)
	{
		//MB::Vect3 pos = this->_node->transform().position();
		//std::cout << "POSITION: " << pos.x() << ", " << pos.y() << ", " << pos.z() << std::endl;
	}
};

MB::Engine* engine;
MB::Scene* scene;
MB::Drawable* cube;
void renderFunc(float dt);


MB::PostProcessMaterial* ppm;

int main(void)
{
    MB::GLContext context(3, 3, 500, 500, "Hello MB");

	MB::CustomPingPong<float> cpp(1.0f, 2.0f);
	std::cout << cpp.first() << " - " << cpp.last() << std::endl;
	cpp.swap();
	std::cout << cpp.first() << " - " << cpp.last() << std::endl;
	cpp.swap();
	std::cout << cpp.first() << " - " << cpp.last() << std::endl;

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

	MB::SimpleShadingMaterial ssm;
    auto uniforms = ssm.uniforms();
    MB::Uniform* color = uniforms["color"];
    color->value(5.1f);
    auto cv = color->value().cast<float>();
    std::cout << cv << std::endl;
    color->value(-25);
    auto cv2 = color->value().cast<int>();
    std::cout << cv2 << std::endl;
	
    cube = new MB::Drawable(1.0f);

	MB::Vect3 v(1.0f, 1.0f, 1.0f);
	MB::Vect3 v2(1.0f, 1.0f, 1.0f);

    MB::Color3 c(1.0f, 0.0f, 0.0f);

    auto blueColor = MB::Color3::createFromHex(0x0000FF);

	auto vf = v.add(v2);

	MB::Node* mbCube = new MB::Node(std::string("cube"));
	mbCube->addComponent(new MB::MeshRenderer(cube, &ssm));
	mbCube->addComponent(new MoveComponent());
	mbCube->addComponent(new ScaleComponent());
	mbCube->addComponent(new PrintPosition());

	MB::Node* mbSphere = new MB::Node(std::string("sphere"));
    mbSphere->addComponent(new MB::MeshRenderer(cube, &ssm));
	mbCube->addChild(mbSphere);

	MB::Node* mbCapsule = new MB::Node(std::string("capsule"));
    mbCapsule->addComponent(new MB::MeshRenderer(cube, &ssm));
	mbSphere->addChild(mbCapsule);

	MB::Node* mbCylinder = new MB::Node(std::string("cylinder"));
    mbCylinder->addComponent(new MB::MeshRenderer(cube, &ssm));
	mbCube->addChild(mbCylinder);

	MB::Node* mbCapsule2 = new MB::Node(std::string("capsule2"));
    mbCapsule2->addComponent(new MB::MeshRenderer(cube, &ssm));
	mbCylinder->addChild(mbCapsule2);

	mbCube->transform().position().set(0.0f, 3.15f, -8.98f);
	mbCube->transform().scale().set(2.0f, 2.0f, 1.0f);

    engine = new MB::Engine(&context);
	scene = new MB::Scene();
	scene->root()->addChild(mbCube);

	// std::cout << (scene->root() == n->parent()) << std::endl;
	auto node = scene->findByName(std::string("capsule"));

	std::cout << (*node) << std::endl;

	/*for (auto c : mbCube->components())
	{
		std::cout << (*c) << std::endl;
	}*/

	/*std::function<void()> f0([=]() {
		std::cout << "BEFORE NO REUSABLE" << std::endl;
	});
	std::function<void()> f1([=]() {
		std::cout << "BEFORE REUSABLE" << std::endl;
	});

	std::function<void()> f2([=]() {
		std::cout << "AFTER NO REUSABLE" << std::endl;
	});
	std::function<void()> f3([=]() {
		std::cout << "AFTER REUSABLE" << std::endl;
	});

	scene->registerBeforeRender(f0);
	scene->registerBeforeRender(f1, true);
	scene->registerAfterRender(f2);
	scene->registerAfterRender(f3, true);*/

	engine->run(renderFunc);
	//ppm.renderPP();
    
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
	scene->render(dt);
	//ppm->renderPP();
}
