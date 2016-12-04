#version 330
flat in vec3 outNormal;

out vec4 fragColor;

uniform vec3 color;

void main() {
    vec3 N = normalize(outNormal);
    fragColor = vec4(N, 1.0);
}