#include <iostream>
#include <mb/mb.h>

MB::Engine* engine;
MB::Scene* scene;

void renderFunc(float dt);

int main(void)
{
    MB::GLContext context(3, 3, 1024, 768, "Hello MB");

    engine = new MB::Engine(&context, false);
	scene = new MB::Scene();

	MB::Cube* cube = new MB::Cube(1.0f);

	MB::SimpleShadingMaterial material;
	material.uniform("color")->value(MB::Vect3(MB::Color3::Blue));

	MB::Node* mbCube = new MB::Node(std::string("cube"));
	mbCube->addComponent(new MB::MeshRenderer(cube, &material));
	mbCube->addComponent(new MoveComponent());
	mbCube->addComponent(new RotateComponent(Axis::x));

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
