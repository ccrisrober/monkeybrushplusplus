#version 440

layout(triangles, equal_spacing) in;
in vec3 tcPosition[];
out vec3 tePosition;
uniform mat4 proj;
uniform mat4 view;

void main()
{
    vec3 p0 = gl_TessCoord.x * tcPosition[0];
    vec3 p1 = gl_TessCoord.y * tcPosition[1];
    vec3 p2 = gl_TessCoord.z * tcPosition[2];
    tePosition = normalize(p0 + p1 + p2);
    gl_Position = proj * view * vec4(tePosition, 1.0);
}
