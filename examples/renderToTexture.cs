#version 430                                                               
layout (local_size_x = 32, local_size_y = 32) in;                       
layout (rgba8, binding = 0) uniform image2D img_output;      
                                                                            
void main ()
{    
  ivec2 uv = ivec2(gl_GlobalInvocationID.xy);
  vec4 color = vec4(gl_WorkGroupID / vec3(gl_NumWorkGroups), 1.0);
  imageStore(img_output, uv, color);        
}