#version 330

out vec4 fragColor;
uniform float iGlobalTime;
in vec2 uv;

uniform sampler2D tex;

const float
      h = 1./512.,
     dt = 0.01,
    tau = dt/h;

void main() {
    vec2 t = texture(tex, uv).xy;
    vec2 D = -t*tau;
    vec2 Df = floor(D);
    vec2 Dd = D - Df;
    vec2 tc1 = uv + Df * h;
    float mov =    // bilinear interpolation of the 4 closest texels
        (texture(tex, tc1).z*(1. - Dd.y) +
         texture(tex, vec2(tc1.x, tc1.y + h)).z*Dd.y)*(1. - Dd.x) +
        (texture(tex, vec2(tc1.x + h, tc1.y)).z*(1. - Dd.y) +
         texture(tex, vec2(tc1.x + h, tc1.y + h)).z*Dd.y)*Dd.x;
    fragColor = vec4(t, mov, 1.0 );
}