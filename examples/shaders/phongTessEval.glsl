#version 420 core

layout(triangles, fractional_odd_spacing, ccw) in;

struct PhongPatch
{
  float termIJ;
  float termJK;
  float termIK;
};

layout(location=0) in vec3 iNormal[];
layout(location=3) in vec2 iTexCoord[];
layout(location=6) in PhongPatch iPhongPatch[];

layout(location=0) out vec3 outPosition;
layout(location=1) out vec3 oNormal;
layout(location=2) out vec2 oTexCoord;

uniform float uTessAlpha;
uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

#define Pi  gl_in[0].gl_Position.xyz
#define Pj  gl_in[1].gl_Position.xyz
#define Pk  gl_in[2].gl_Position.xyz
#define tc1 gl_TessCoord

void main()
{
  // precompute squared tesscoords
  vec3 tc2 = tc1*tc1;
  mat4 uModelViewProjection = proj * view * model;

  // compute texcoord and normal
  oTexCoord = gl_TessCoord[0]*iTexCoord[0]
            + gl_TessCoord[1]*iTexCoord[1]
            + gl_TessCoord[2]*iTexCoord[2];
  oNormal   = gl_TessCoord[0]*iNormal[0]
            + gl_TessCoord[1]*iNormal[1]
            + gl_TessCoord[2]*iNormal[2];

  // interpolated position
  vec3 barPos = gl_TessCoord[0]*Pi
              + gl_TessCoord[1]*Pj
              + gl_TessCoord[2]*Pk;

  // build terms
  vec3 termIJ = vec3(iPhongPatch[0].termIJ,
                     iPhongPatch[1].termIJ,
                     iPhongPatch[2].termIJ);
  vec3 termJK = vec3(iPhongPatch[0].termJK,
                     iPhongPatch[1].termJK,
                     iPhongPatch[2].termJK);
  vec3 termIK = vec3(iPhongPatch[0].termIK,
                     iPhongPatch[1].termIK,
                     iPhongPatch[2].termIK);

  // phong tesselated pos
  vec3 phongPos   = tc2[0]*Pi
                  + tc2[1]*Pj
                  + tc2[2]*Pk
                  + tc1[0]*tc1[1]*termIJ
                  + tc1[1]*tc1[2]*termJK
                  + tc1[2]*tc1[0]*termIK;

  // final position
  vec3 finalPos = (1.0-uTessAlpha)*barPos + uTessAlpha*phongPos;
  outPosition = vec3(view * model * vec4(finalPos, 1.0));
  gl_Position   = uModelViewProjection * vec4(finalPos,1.0);
}
