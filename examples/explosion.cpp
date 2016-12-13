/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus <https://github.com/maldicion069/monkeybrushplusplus>
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
#include <vector>

mb::Scene* scene;

void renderFunc(float dt);

class ExplosionComponent : public mb::Component
{
public:
  ExplosionComponent()
    : mb::Component()
    , _globalTime(0.0f)
  {}
  virtual void update(const float dt) override
  {
    _globalTime += dt;
    getNode()->getMesh()->getMaterial()->uniform("time")->value(_globalTime);
  }
protected:
  float _globalTime;
};

int main(void)
{
  mb::GLContext context(3, 3, 1024, 768, "Model explosion");

  auto engine = new mb::Engine(&context, false);
  scene = new mb::Scene(engine,
    new mb::SimpleCamera(mb::Vect3(0.2f, 0.18f, 18.44f)));

  std::vector<std::pair<mb::ShaderType, const char*> > shaders;
  const char* vertexShader =
    "#version 330 core\n"
    "layout(location = 0) in vec3 position;\n"
    "layout(location = 2) in vec2 texCoords;\n"
    "out VS_OUT {\n"
    " vec2 texCoords;\n"
    "} vs_out;\n"
    "uniform mat4 projection;\n"
    "uniform mat4 view;\n"
    "uniform mat4 model;\n"
    "void main() {\n"
    " gl_Position = projection * view * model * vec4(position, 1.0f);\n"
    " vs_out.texCoords = texCoords;\n"
    "}";
  const char* geometryShader =
    "#version 330 core\n"
    "layout (triangles) in;\n"
    "layout (triangle_strip, max_vertices = 3) out;\n"
    "in VS_OUT {\n"
    "    vec2 texCoords;\n"
    "} gs_in[];\n"
    "out vec2 TexCoords; \n"
    "uniform float time;\n"
    "vec4 explode(vec4 position, vec3 normal) {\n"
    "    float magnitude = 2.0f;\n"
    "    vec3 direction = normal * ((sin(time) + 1.0f) / 2.0f) * magnitude; \n"
    "    return position + vec4(direction, 0.0f);\n"
    "}\n"
    "vec3 GetNormal() {\n"
    "    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);\n"
    "    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);\n"
    "    return normalize(cross(a, b));\n"
    "}\n"
    "void main() {\n"
    "    vec3 normal = GetNormal();\n"
    "    gl_Position = explode(gl_in[0].gl_Position, normal);\n"
    "    TexCoords = gs_in[0].texCoords;\n"
    "    EmitVertex();\n"
    "    gl_Position = explode(gl_in[1].gl_Position, normal);\n"
    "    TexCoords = gs_in[1].texCoords;\n"
    "    EmitVertex();\n"
    "    gl_Position = explode(gl_in[2].gl_Position, normal);\n"
    "    TexCoords = gs_in[2].texCoords;\n"
    "    EmitVertex();\n"
    "    EndPrimitive();\n"
    "}";
  const char* fragmentShader =
    "#version 330\n"
    "out vec4 fragColor;\n"
    "uniform vec3 color;\n"
    "void main() {\n"
    " fragColor = vec4(color, 1.0);\n"
    "}";

  shaders.push_back(std::make_pair(mb::VertexShader, vertexShader));
  shaders.push_back(std::make_pair(mb::GeometryShader, geometryShader));
  shaders.push_back(std::make_pair(mb::FragmentShader, fragmentShader));

  std::vector<std::pair<const char*, mb::Uniform*> > uniforms = {
    std::make_pair("projection", new mb::Uniform(mb::Matrix4)),
    std::make_pair("view", new mb::Uniform(mb::Matrix4)),
    std::make_pair("model", new mb::Uniform(mb::Matrix4)),
    std::make_pair("color", new mb::Uniform(mb::Vector3, mb::Vect3(0.0f, 1.0f, 1.0f))),
    std::make_pair("time", new mb::Uniform(mb::Float, 0.015f))
  };

  auto material = new mb::ShaderMaterial("geomExplosion", shaders, uniforms);

  mb::Drawable* draw1 = new mb::Torus(0.5f, 0.25f, 25, 40);
  mb::Drawable* draw2 = new mb::Octahedron(0.5f, 2);
  mb::Drawable* draw3 = new mb::Cone(0.5f, 0.25f, 1.0f, 25, 25);

  auto mbObj = new mb::Node(std::string("torus"));
  mbObj->addComponent(mb::ComponentPtr(new mb::MeshRenderer(draw1, material)));
  mbObj->addComponent(mb::ComponentPtr(new mb::MoveComponent()));
  mbObj->addComponent(mb::ComponentPtr(new mb::RotateComponent(mb::Axis::x)));
  mbObj->addComponent(mb::ComponentPtr(new ExplosionComponent()));
  mbObj->transform().position().y(3.5f);
  mbObj->transform().rotation().y(-1.44f);

  auto mbObj2 = new mb::Node(std::string("torus"));
  mbObj2->addComponent(mb::ComponentPtr(new mb::MeshRenderer(draw2, material)));
  mbObj2->addComponent(mb::ComponentPtr(new mb::MoveComponent()));
  mbObj2->addComponent(mb::ComponentPtr(new mb::RotateComponent(mb::Axis::y)));
  mbObj2->addComponent(mb::ComponentPtr(new ExplosionComponent()));
  mbObj2->transform().position().y(0.0f);

  auto mbObj3 = new mb::Node(std::string("torus"));
  mbObj3->addComponent(mb::ComponentPtr(new mb::MeshRenderer(draw3, material)));
  mbObj3->addComponent(mb::ComponentPtr(new mb::MoveComponent()));
  mbObj3->addComponent(mb::ComponentPtr(new mb::RotateComponent(mb::Axis::z)));
  mbObj3->addComponent(mb::ComponentPtr(new ExplosionComponent()));
  mbObj3->transform().position().y(-3.5f);
  mbObj3->transform().rotation().x(1.44f/2.0f);

  scene->root()->addChild(mb::NodePtr(mbObj));
  scene->root()->addChild(mb::NodePtr(mbObj2));
  scene->root()->addChild(mb::NodePtr(mbObj3));

  engine->run(renderFunc);

  delete(scene);
  delete(engine);

  return 0;
}
void renderFunc(float dt)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  scene->render(dt);
}
