/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus
 *    <https://github.com/maldicion069/monkeybrushplusplus>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include <iostream>
#include <mb/mb.h>
#include <assetsFiles.h>

mb::ScenePtr scene;

void renderFunc( float dt );

int main(void)
{
  mb::GLContext context( 3, 3, 1024, 768, "PBR" );

  auto engine = std::make_shared<mb::Engine>( &context, false );
  scene = std::make_shared<mb::Scene>( engine,
    new mb::SimpleCamera( mb::Vect3( 0.2f, 0.18f, 8.44f ) ) );


  mb::DrawablePtr mesh = std::make_shared<mb::Sphere>(1.0f, 25, 25); 
  /*mb::DrawablePtr mesh = std::make_shared<mb::Mesh>(
	  MB_MODEL_ASSETS + std::string("/suzanne.obj_"));*/

  std::vector<std::pair<mb::ShaderType, const char*> > shaders = {
	  {
		  mb::VertexShader,
		  R"(#version 330
		  layout(location = 0) in vec3 position;
		  layout(location = 1) in vec3 norm;
		  layout(location = 2) in vec2 uv;
		  out vec3 outPos;
		  out vec3 outNorm;
		  out vec2 outUV;
		  uniform mat4 projection;
		  uniform mat4 view;
		  uniform mat4 model;
		  void main( void )
		  {
			outPos = vec3(model * vec4(position, 1.0));
			gl_Position = projection * view * model * vec4(position, 1.0);
			outNorm = mat3(model) * norm;
			outUV = uv;
		  })"
	  }, {
		  mb::FragmentShader,
		  R"(#version 330
			out vec4 fragColor;
			in vec3 outPos;
			in vec3 outNorm;
			in vec2 outUV;

	
			uniform vec3 viewPos;

			vec3 albedo = vec3(0.5, 0.0, 0.0);
			float metallic = 3.2;
			float roughness = 0.25;
			float ao = 1.0;

			const float PI = 3.14159265359;

			vec3 lightPositions[4];
			vec3 lightColors[4];
  

			// ----------------------------------------------------------------------------
			float DistributionGGX(vec3 N, vec3 H, float roughness)
			{
				float a = roughness*roughness;
				float a2 = a*a;
				float NdotH = max(dot(N, H), 0.0);
				float NdotH2 = NdotH*NdotH;

				float nom   = a2;
				float denom = (NdotH2 * (a2 - 1.0) + 1.0);
				denom = PI * denom * denom;

				return nom / denom;
			}
			// ----------------------------------------------------------------------------
			float GeometrySchlickGGX(float NdotV, float roughness)
			{
				float r = (roughness + 1.0);
				float k = (r*r) / 8.0;

				float nom   = NdotV;
				float denom = NdotV * (1.0 - k) + k;

				return nom / denom;
			}
			// ----------------------------------------------------------------------------
			float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
			{
				float NdotV = max(dot(N, V), 0.0);
				float NdotL = max(dot(N, L), 0.0);
				float ggx2 = GeometrySchlickGGX(NdotV, roughness);
				float ggx1 = GeometrySchlickGGX(NdotL, roughness);

				return ggx1 * ggx2;
			}
			// ----------------------------------------------------------------------------
			vec3 fresnelSchlick(float cosTheta, vec3 F0)
			{
				return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
			}
			// ----------------------------------------------------------------------------

			void main( void )
			{
				lightPositions[0] = vec3(-10.0,  10.0, 10.0);
				lightPositions[1] = vec3( 10.0,  10.0, 10.0);
				lightPositions[2] = vec3(-10.0, -10.0, 10.0);
				lightPositions[3] = vec3(-10.0, -10.0, 10.0);

				lightColors[0] = vec3(1.0, 1.0, 1.0);
				lightColors[1] = vec3(1.0, 0.0, 0.0);
				lightColors[2] = vec3(0.0, 1.0, 0.0);
				lightColors[3] = vec3(0.0, 0.0, 1.0);

				vec3 N = normalize(outNorm);
				vec3 V = normalize(viewPos - outPos);
				vec3 R = reflect(-V, N); 

				// calculate reflectance at normal incidence; if dia-electric (like plastic) use F0 
				// of 0.04 and if it's a metal, use their albedo color as F0 (metallic workflow)    
				vec3 F0 = vec3(0.04); 
				F0 = mix(F0, albedo, metallic);

				// reflectance equation
				vec3 Lo = vec3(0.0);
				for(int i = 0; i < 4; ++i) 
				{
					// calculate per-light radiance
					vec3 L = normalize(lightPositions[i] - outPos);
					vec3 H = normalize(V + L);
					float distance = length(lightPositions[i] - outPos);
					float attenuation = 1.0 / (distance * distance);
					vec3 radiance = lightColors[i] * attenuation;

					// Cook-Torrance BRDF
					float NDF = DistributionGGX(N, H, roughness);   
					float G   = GeometrySmith(N, V, L, roughness);      
					vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);
           
					vec3 nominator    = NDF * G * F; 
					float denominator = 4 * max(dot(V, N), 0.0) * max(dot(L, N), 0.0) + 0.001; // 0.001 to prevent divide by zero.
					vec3 brdf = nominator / denominator;
        
					// kS is equal to Fresnel
					vec3 kS = F;
					// for energy conservation, the diffuse and specular light can't
					// be above 1.0 (unless the surface emits light); to preserve this
					// relationship the diffuse component (kD) should equal 1.0 - kS.
					vec3 kD = vec3(1.0) - kS;
					// multiply kD by the inverse metalness such that only non-metals 
					// have diffuse lighting, or a linear blend if partly metal (pure metals
					// have no diffuse light).
					kD *= 1.0 - metallic;	  

					// scale light by NdotL
					float NdotL = max(dot(N, L), 0.0);        

					// add to outgoing radiance Lo
					Lo += (kD * albedo / PI + brdf) * radiance * NdotL;  // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
				}   
    
				// ambient lighting (note that the next IBL tutorial will replace 
				// this ambient lighting with environment lighting).
				vec3 ambient = vec3(0.03) * albedo * ao;

				vec3 color = ambient + Lo;

				// HDR tonemapping
				color = color / (color + vec3(1.0));
				// gamma correct
				color = pow(color, vec3(1.0/2.2)); 

				fragColor = vec4(color, 1.0);
			})"
	  }
  };

  std::vector<std::pair<const char*, mb::Uniform*> > uniforms = {
	  std::make_pair("projection", new mb::Uniform(mb::Matrix4)),
	  std::make_pair("view", new mb::Uniform(mb::Matrix4)),
	  std::make_pair("model", new mb::Uniform(mb::Matrix4)),
	  std::make_pair("viewPos", new mb::Uniform(mb::Vector3))
  };

  auto material = std::make_shared<mb::ShaderMaterial>("material", shaders, uniforms);

  mb::NodePtr mbNode = std::make_shared<mb::Node>( std::string( "mesh" ) );
  mbNode->addComponent(std::make_shared<mb::MeshRenderer>(mesh, material));
  mbNode->addComponent(std::make_shared<mb::RotateComponent>(mb::Axis::y, 0.5f, true));

  scene->root( )->addChild( mb::NodePtr( mbNode ) );

  engine->run( renderFunc );

  return 0;
}

void renderFunc( float dt )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  scene->render( dt );
}
