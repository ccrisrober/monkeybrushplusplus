#include <iostream>
#include <mb/mb.h>

MB::Engine* engine;
MB::Scene* scene;

void renderFunc(float dt);


MB::PostProcessMaterial* ppm;

int main(void)
{
    MB::GLContext context(3, 3, 1024, 768, "Quasicrystal demo");

    engine = new MB::Engine(&context, false);
	scene = new MB::Scene();

	ppm = new MB::PostProcessMaterial(
		"#version 330\n"
		"out vec4 fragColor;\n"
		"uniform float iGlobalTime;\n"
		"uniform bool useColor;\n"
		"in vec2 uv;\n"
		"void main() {\n"
        "    vec2 p = -1. + 2. * uv;\n"
        "    float t = iGlobalTime * 0.5;\n"
        "    vec2 off1 = vec2(0.5 * cos(5.0 * t), 0.5 * sin(3.0 * t));\n"
        "    vec2 off2 = vec2(0.6 * sin(3.0 * t), 0.4 * cos(2.0 * t));\n"
        "    // Cartesian equation\n"
        "    float r1 = sqrt(dot(p - off1, p - off1));\n"
        "    float r2 = sqrt(dot(p - off2, p - off2));\n"
        "    bool t1 = mod(r1, 0.2) > 0.1;\n"
        "    bool t2 = mod(r2, 0.2) > 0.1;\n"
        "    // XOR time\n"
        "    float c = 0.0;\n"
        "    if (t1) c = 1.0;\n"
        "    if (t2) c = 1.0;\n"
        "    if ((t1) && (t2)) c = 0.0;\n"
        "    if(useColor)"
        "    	fragColor = vec4(vec3(c),1.0);\n"
        "    else\n"
        "		fragColor = vec4(t1, t2, 0.0, 1.0);\n"
        "}\n");

	ppm->addUniform("iGlobalTime", new MB::Uniform(MB::Float));
	ppm->addUniform("useColor", new MB::Uniform(MB::Boolean, false));

	engine->run(renderFunc);
    
	delete(scene);
	delete(engine);

    return 0;
}

float globalTime = 0.0f;
void renderFunc(float dt)
{
	globalTime += dt;
	ppm->uniform("iGlobalTime")->value(globalTime);
	if (MB::Input::isKeyPressed(GLFW_KEY_Z))
	{
		ppm->uniform("useColor")->value(false);
	}
	else if (MB::Input::isKeyPressed(GLFW_KEY_X))
	{
		ppm->uniform("useColor")->value(true);
	}
	ppm->renderPP();
}
