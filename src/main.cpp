#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "core/GLContext.hpp"
#include "scene/Engine.hpp"
//#include "textures/Texture.hpp"

void renderFunc(float dt)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    std::cout << "Pinto con tiempo " << dt << std::endl;
}

int main(void)
{
    MB::GLContext context(3, 3, "Hello MB");

    MB::Engine e(&context);
    e.run(renderFunc);
    
    glfwTerminate();
    return 0;
}
