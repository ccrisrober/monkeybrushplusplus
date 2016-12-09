#version 420 core

layout(vertices=3) out;
uniform float uTessLevels;

struct PhongPatch
{
  float termIJ;
  float termJK;
  float termIK;
};

layout(location = 0) in vec3 iNormal[];
layout(location = 1) in vec2 iTexCoord[];

layout(location=0) out vec3 oNormal[3];
layout(location=3) out vec2 oTexCoord[3];
layout(location=6) out PhongPatch oPhongPatch[3];

#define Pi  gl_in[0].gl_Position.xyz
#define Pj  gl_in[1].gl_Position.xyz
#define Pk  gl_in[2].gl_Position.xyz

float PIi(int i, vec3 q)
{
  vec3 q_minus_p = q - gl_in[i].gl_Position.xyz;
  return q[gl_InvocationID] - dot(q_minus_p, iNormal[i])
                            * iNormal[i][gl_InvocationID];
}

void main()
{
  // get data
  gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
  oNormal[gl_InvocationID]   = iNormal[gl_InvocationID];
  oTexCoord[gl_InvocationID] = iTexCoord[gl_InvocationID];

  // compute patch data
  oPhongPatch[gl_InvocationID].termIJ = PIi(0,Pj) + PIi(1,Pi);
  oPhongPatch[gl_InvocationID].termJK = PIi(1,Pk) + PIi(2,Pj);
  oPhongPatch[gl_InvocationID].termIK = PIi(2,Pi) + PIi(0,Pk);

  // tesselate
  gl_TessLevelOuter[gl_InvocationID] = uTessLevels;
  gl_TessLevelInner[0] = uTessLevels;
}
