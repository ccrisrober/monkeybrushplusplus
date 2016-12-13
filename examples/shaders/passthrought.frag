#version 430

in vec2 uv;

layout(binding=0) uniform sampler2D tex;
layout( location = 0 ) out vec4 fragColor;

void main() {
  vec4 color = texture(tex, uv);
  fragColor = vec4(color.xyz, 1.0);
}
