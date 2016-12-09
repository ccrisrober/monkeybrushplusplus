#version 420 core

layout(location = 0) in vec3 iPosition;
layout(location = 1) in vec3 iNormal;
layout(location = 2) in vec2 iTexCoord;

layout(location = 0) out vec3 oNormal;
layout(location = 1) out vec2 oTexCoord;

void main()
{
  gl_Position.xyz = iPosition;
  oNormal         = iNormal;
  oTexCoord       = iTexCoord;
}
