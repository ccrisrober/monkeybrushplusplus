#version 330

out vec4 fragColor;
in vec2 uv;

uniform float sides;
uniform float angle;
uniform float iGlobalTime;
uniform sampler2D tex;

void main() {
    vec2 p = uv - 0.5;
    float r = length(p);
    float a = atan(p.y, p.x) + angle;
    float tau = 2. * 3.1416;
    a = mod(a, tau/sides);
    a = abs(a - tau/sides/2.);
    p = r * vec2(cos(a), sin(a));
    vec4 color = texture(tex, p - cos(iGlobalTime) + 0.5);
    fragColor = color;
}