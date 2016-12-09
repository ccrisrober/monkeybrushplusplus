#version 420 core
layout(location = 0) in vec3 outPosition;
layout(location = 1) in vec3 iNormal;
layout(location = 2) in vec2 iTexCoord;

uniform vec3 viewPos;
uniform vec3 color;

out vec4 fragColor;

void main() {
  vec3 N = normalize(iNormal);
  vec3 L = normalize(viewPos - outPosition);
  float dif = dot(N, L);
  dif = clamp(dif, 0.0, 1.0);
  fragColor = vec4(color * dif, 1.0) + vec4(color * 0.3, 1.0);
}
