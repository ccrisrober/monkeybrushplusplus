#version 330
uniform isampler2D tex;

in vec2 uv;

out vec4 fragColor;

void main() {
    float c = .00000002 * float(texture(tex, uv).r);
    float b = 0.;
    if(c < 0.) b = -c;
    fragColor = vec4(.0, b, c, 1.);
}