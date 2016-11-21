#include <iostream>
#include <mb/mb.h>

MB::Engine* engine;
MB::Scene* scene;

void renderFunc(float dt);

MB::Node* mbCube;

int main(void)
{
    MB::GLContext context(3, 3, 1024, 768, "Hello MB");

    engine = new MB::Engine(&context, false);
	scene = new MB::Scene();

	MB::Cube* cube = new MB::Cube(1.0f);

	MB::SimpleShadingMaterial material;
	material.uniform("color")->value(MB::Vect3(MB::Color3::Blue));

	mbCube = new MB::Node(std::string("cube"));
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
	if (MB::Input::isKeyClicked(GLFW_KEY_X))
	{
		mbCube->getComponent<RotateComponent>()->setAxis(Axis::x);
	}
	else if (MB::Input::isKeyClicked(GLFW_KEY_Y))
	{
		mbCube->getComponent<RotateComponent>()->setAxis(Axis::y);
	}
	else if (MB::Input::isKeyClicked(GLFW_KEY_Z))
	{
		mbCube->getComponent<RotateComponent>()->setAxis(Axis::z);
	}
	scene->render(dt);
}
