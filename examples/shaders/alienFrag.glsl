#version 330
in vec3 outPosition;
in vec3 outNormal;

out vec4 fragColor;

uniform vec3 viewPos;
uniform float base_freq;

const vec3 SkinColor1 = vec3(0.3, 0.5, 0.2);
const vec3 SkinColor2 = vec3(0.8, 0.8, 0.5);
const vec3 SkinColor3 = vec3(0.7, 0.8, 0.8);

#import<SimpleNoise3D>

void main() {
    float noise =
        snoise(outPosition * base_freq) * 8.0 +
        snoise(outPosition * base_freq * 2.0) * 4.0 +
        snoise(outPosition * base_freq * 4.0) * 2.0 +
        snoise(outPosition * base_freq * 8.0);
    noise = (noise / 8.0 + 1.0) / 2.0;

    noise -= 0.3;
    noise *= 2.0;

    float intensity = noise;
    vec3 color;

    intensity = clamp(intensity, 0.0, 1.0);

    if (intensity < 0.50)
        color = mix(SkinColor1, SkinColor2, intensity/0.50);
    else
        color = mix(SkinColor1, SkinColor3, (intensity - 0.50)/0.50);

    vec3 N=normalize(outNormal);
    vec3 L = normalize(viewPos - outPosition);
    float dif=dot(N,L);
    dif=clamp(dif,0.0,1.0);
    fragColor = vec4(color*dif,1.0)+vec4(color*0.3,1.0);
}