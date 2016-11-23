#version 330

out vec4 fragColor;
uniform float iGlobalTime;
in vec2 uv;

uniform sampler2D tex;

void main() {
    float c = texture(tex, uv).b;
    fragColor = vec4(uv * c, 0.0, 1.0);
}