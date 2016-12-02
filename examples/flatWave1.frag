#version 330
uniform isampler2D tex;
in vec2 uv;
out ivec2 fragColor;
const float d = 1./512.;
void main(void) {
    int u0 = texture(tex, uv).g;
    int u  = texture(tex, uv).r;
    int u1 = u + u - u0 +
        (texture(tex, vec2(uv.x, uv.y + d) ).r +
         texture(tex, vec2(uv.x, uv.y - d) ).r +
         texture(tex, vec2(uv.x + d, uv.y) ).r +
         texture(tex, vec2(uv.x - d, uv.y) ).r - 4 * u) / 4;
    fragColor = ivec2(u1, u );
}