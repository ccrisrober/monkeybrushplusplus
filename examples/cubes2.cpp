#include <iostream>
#include <mb/mb.h>

MB::Engine* engine;
MB::Scene* scene;

void renderFunc(float dt);

class Rotate : public MB::Component
{
public:
	Rotate()
		: MB::Component()
		, _rotate(false)
	{
	}
	virtual void update(float dt)
	{
		if (MB::Input::isKeyClicked(GLFW_KEY_SPACE))
		{
			this->_rotate = !this->_rotate;
		}
		if (this->_rotate)
		{
			auto xRot = _node->transform().rotation().y();
			auto yRot = _node->transform().rotation().y();
			_node->transform().rotation().x(xRot + dt);
			_node->transform().rotation().y(yRot + dt);
		}
	}
protected:
	bool _rotate;
};

int main(void)
{
    MB::GLContext context(3, 3, 1024, 768, "Hello MB");

    engine = new MB::Engine(&context, false);
	scene = new MB::Scene();

	MB::Cube* cube = new MB::Cube(2.0f);

	unsigned int MAX = 10;
    for (unsigned int zz = 0; zz < MAX; ++zz)
    {
	    for (unsigned int yy = 0; yy < MAX; ++yy)
	    {
	        for (unsigned int xx = 0; xx < MAX; ++xx)
	        {
	        	MB::Node* mbCube = new MB::Node(std::string("cube"));

				MB::SimpleShadingMaterial* material = new MB::SimpleShadingMaterial();
				material->uniform("color")->value(MB::Vect3(MB::Color3((float)xx/MAX, (float)yy/MAX, (float)zz/MAX)));

				mbCube->addComponent(new MB::MeshRenderer(cube, material));
				mbCube->addComponent(new Rotate());
				mbCube->transform().position().set(
	        		-15.0f + xx * + 6.0f,
	                -15.0f + yy * + 6.0f,
	                zz * 6.0);
				mbCube->transform().rotation().y(xx * 0.21f + yy + 0.37f);
	        	scene->root()->addChild(mbCube);
	                    //.rotate(this.angle + xx * 0.21 + yy * 0.37, MB.Vect3.zAxis);
	        }
    	}
    }

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
