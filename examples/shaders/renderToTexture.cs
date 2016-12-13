#version 430
layout (local_size_x = 32, local_size_y = 32) in;
layout (rgba8, binding = 0) uniform image2D img_output;

uniform float time;

void main ()
{
  ivec2 uv = ivec2(gl_GlobalInvocationID.xy);
  vec4 color = vec4(gl_WorkGroupID / vec3(gl_NumWorkGroups), 1.0);

  color = vec4(color.xy, 0.5 + 0.5 * sin(time), 1.0);

  imageStore(img_output, uv, color);
}
