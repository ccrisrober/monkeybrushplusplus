#include <iostream>
#include <mb/mb.h>
#include <random>

MB::Engine* engine;
MB::Scene* scene;

void renderFunc(float dt);

class BrownianMovement: public MB::Component
{
public:
	BrownianMovement()
	: MB::Component()
	, _generator(std::default_random_engine(0))
	, _distribution(std::normal_distribution<float> (0.0f, 1.0f))
	{
		_yPos = _node->transform().position().y();
	}
	virtual void update(float dt)
	{
		_node->transform().position().y(_yPos + _distribution(_generator) * dt);
	}
protected:
	std::default_random_engine _generator;
	std::normal_distribution<float> _distribution;

	float _yPos;
};

int main(void)
{
    MB::GLContext context(3, 3, 1024, 768, "Brownian Motion");

    engine = new MB::Engine(&context, false);
	scene = new MB::Scene();

	MB::Cube* cube = new MB::Cube(1.0f);

	MB::SimpleShadingMaterial material;
	material.uniform("color")->value(MB::Vect3(MB::Color3::Blue));

	MB::Node* mbCube = new MB::Node(std::string("cube"));
	mbCube->addComponent(new MB::MeshRenderer(cube, &material));
	mbCube->addComponent(new MoveComponent());
	mbCube->addComponent(new RotateComponent(Axis::z));
	mbCube->addComponent(new BrownianMovement());
	mbCube->transform().position().set(0.0f, 3.0f, 0.0f);

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
		engine->state()->depth.setStatus(false);
	}
	if (MB::Input::isKeyClicked(GLFW_KEY_X))
	{
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
