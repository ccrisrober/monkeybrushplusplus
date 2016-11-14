#include <iostream>

//OpenGL
#ifndef SKIP_GLEW_INCLUDE
#include <GL/glew.h>
#endif
#ifdef Darwin
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <GLFW/glfw3.h>

#include "core/GLContext.hpp"
#include "scene/Engine.hpp"
#include "scene/Node.hpp"
#include "maths/Vect3.hpp"
#include "textures/Texture.hpp"
#include "constants/Constants.hpp"
#include "core/Input.hpp"

void renderFunc(float dt);

int main(void)
{
	//MB::Input::isButtonClicked(5);
	MB::Vect3 v(1.0f, 1.0f, 1.0f);
	MB::Vect3 v2(1.0f, 1.0f, 1.0f);

	auto vf = v.add(v2);

    MB::GLContext context(3, 3, "Hello MB");

	MB::Node* n = new MB::Node("HelloNode", "HelloTag");
	MB::Node* n2 = new MB::Node("HelloNode2", "HelloTag2");
	n->addChild(n2);

	n->transform().position().x(5.0f);

    MB::Engine e(&context);
    e.run(renderFunc);
    
    glfwTerminate();
    return 0;
}

void renderFunc(float dt)
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	std::cout << "Pinto con tiempo " << dt << std::endl;
}
