#version 330
out vec4 fragColor;
in vec2 uv;

precision mediump float;

uniform sampler2D tex;

uniform float blockCount;
uniform float blockSize;

void main()
{
  vec2 blockPos = floor(uv * vec2(blockCount));
  vec2 blockCenter = blockPos * vec2(blockSize) + vec2(blockSize) * 0.5;
  fragColor = texture(tex, blockCenter);
}
