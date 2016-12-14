#version 440
layout (vertices = 3) out;

uniform float tess_level;

#define ID gl_InvocationID

void main(void)
{
  if (ID == 0)
  {
    gl_TessLevelInner[0] = tess_level;
    gl_TessLevelOuter[0] = tess_level;
    gl_TessLevelOuter[1] = tess_level;
    gl_TessLevelOuter[2] = tess_level;
  }
  gl_out[ID].gl_Position = gl_in[ID].gl_Position;
}
