#version 440

in vec3 position;
out vec3 outPosition;

uniform mat4 model;

void main()
{
    outPosition = vec3(model * vec4(outPosition, 1.0));
}