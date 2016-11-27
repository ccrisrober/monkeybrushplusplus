#version 440

layout(vertices = 3) out;
in vec3 outPosition[];
out vec3 tcPosition[];

float TessLevelInner = 3.0;

float TessLevelOuter = 2.0;

#define ID gl_InvocationID

void main()
{
    tcPosition[ID] = outPosition[ID];
    
    // Tesselation level inner
    gl_TessLevelInner[0] = TessLevelInner;

    // Tesselation level outer
    gl_TessLevelOuter[0] = TessLevelOuter;
    gl_TessLevelOuter[1] = TessLevelOuter;
    gl_TessLevelOuter[2] = TessLevelOuter;
}
