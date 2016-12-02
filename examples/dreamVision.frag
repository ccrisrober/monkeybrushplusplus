#version 330
out vec4 fragColor;
in vec2 uv;

uniform float amount;
uniform sampler2D tex;

const float offset[6] = float[] ( 0.001, 0.003, 0.005, 0.007, 0.009, 0.011 );

void main() {
    fragColor = texture(tex, uv);
    if (uv.x >= amount) {
        for (int i = 0; i < 6; ++i) {
            fragColor += texture(tex, uv + offset[i]);
            fragColor += texture(tex, uv - offset[i]);
        }
        fragColor.rgb = vec3((fragColor.r + fragColor.g + fragColor.b)/3.0);
        fragColor.rgb /= 9.5;
    }
}