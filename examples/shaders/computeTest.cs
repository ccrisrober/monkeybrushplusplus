#version 430                                     

uniform float roll;                          
layout (local_size_x = 16, local_size_y = 16) in;                       
layout (r32f, binding = 0) uniform image2D img_output;      
                                                                            
void main ()
{    
    ivec2 uv = ivec2(gl_GlobalInvocationID.xy);
	float val = 0.5 + 0.5 * sin((uv.x + uv.y) / 30.0 + roll);
    imageStore(img_output, uv, vec4(val, val, val, 1.0));  
}