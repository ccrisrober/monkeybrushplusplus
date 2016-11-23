#version 330

out vec4 fragColor;
in vec2 uv;
uniform float iGlobalTime;

#define PI 3.141592653589793
const float FPS = 8.0;
const float WEIGHT = 0.7;
const float CIRCLE = 1.0;
const float rho = 0.9;
const vec2 center = vec2(0.5, 0.5);
const vec4 color = vec4(0.0, 0.0, 0.0, 1.0);

float noise( vec2 val ) {
    return fract(sin(dot(val.xy ,vec2(12.9898,78.233))) * 437.5453);
}

float getFrameTime() {
    return floor(iGlobalTime * FPS) / FPS;
}

void main ( void ) {
    vec2 vecToCenter = uv - center;
    float t = getFrameTime();
    float l = length(vecToCenter) / length(vec2(0.0) - vec2(0.0, 0.5));
    float r = (atan(vecToCenter.y, vecToCenter.x) + PI) / (2.0 * PI);
    float w = mix(3000.0,70.0,WEIGHT);
    float r2 = floor(r * w) / w * max(mod(t,10.0), 0.1);
    float den = mix(10.0,0.01,rho);
    float ran = noise( vec2(r2, r2) ) * den + (CIRCLE * 0.5);

    if( l > ran ) {
        fragColor = vec4(color.rgb, color.a * (l - ran));
    } else {
        fragColor = vec4(1.0);
    }
}
