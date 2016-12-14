#version 330
in vec3 outPosition;
in vec3 outNormal;

out vec4 fragColor;

uniform vec3 viewPos;
uniform float base_freq;

const vec3 Color1 = vec3(0.35, 0.3, 0.2);
const vec3 Color2 = vec3(0.7, 0.7, 0.7);

#import<SimpleNoise3D>

void main() {
  vec4 noisevec;
  noisevec.x = snoise(outPosition * base_freq*1.0) * 8.0;
  noisevec.y = snoise(outPosition * base_freq*2.0) * 4.0;
  noisevec.z = snoise(outPosition * base_freq*4.0) * 2.0;
  noisevec.w = snoise(outPosition * base_freq*8.0) * 1.0;
  noisevec = noisevec / 8.0;

  float intensity = min(1.0, noisevec[3] * 12.0);
  //float intensity = min(1.0, noisevec[2] * 12.0 + noisevec[3]*12.0);
  vec3 color = mix(Color1, Color2, intensity);

  // OR
  /*float intensity = abs(noisevec[0] - 0.20) +
                    abs(noisevec[1] - 0.10) +
                    abs(noisevec[2] - 0.05) +
                    abs(noisevec[3] - 0.025);
  float sineval = sin(outPosition.y * 12.0 + intensity * 8.0) * 0.5 + 0.5;
  vec3 color = mix(Color1, Color2, sineval);*/


  vec3 N=normalize(outNormal);
  vec3 L = normalize(viewPos - outPosition);
  float dif=dot(N,L);
  dif=clamp(dif,0.0,1.0);
  fragColor = vec4(color*dif,1.0)+vec4(color*0.3,1.0);
}
