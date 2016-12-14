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

mb::Scene* scene;

void renderFunc( float dt );

class ExplosionComponent : public mb::Component
{
public:
    ExplosionComponent()
        : mb::Component( )
        , _globalTime(0.0f)
    {
    }
    virtual void update( const float dt ) override
    {
        _globalTime += dt;
        this->_node->getMesh( )->getMaterial( )->uniform("time")->value(_globalTime);
    }
protected:
    float _globalTime;
};

int main(void)
{
  mb::GLContext context(3, 3, 1024, 768, "SceneGraph");

  auto engine = new mb::Engine(&context, false);
  scene = new mb::Scene(engine,
    new mb::SimpleCamera(mb::Vect3(0.2f, 0.18f, 11.44f)));

    mb::ResourceDrawable::add("capsule", new mb::Capsule(0.5f, 1.0f));

    auto cube = new mb::Cube(1.0f);
  auto cylinder = new mb::Cylinder(1.0f, 1.5f, 25, 15);
  auto prism = new mb::Prism(1.0f, 1.5f, 5);
    mb::ResourceDrawable::add("torus", new mb::Torus(0.5f, 0.25f, 25, 40));

    mb::SimpleShadingMaterial material;
    material.uniform("color")->value(mb::Vect3(mb::Color3::Red));
    material.DepthTest = true;

    mb::NormalMaterial normalMat;

    std::vector<std::pair<mb::ShaderType, const char*> > shaders = {
        {
            mb::VertexShader,
            "#version 330\n"
            "layout(location = 0) in vec3 position;"
            "layout(location = 1) in vec3 normal;"
            "layout(location = 2) in vec2 texCoord;"
            "out vec3 outPosition;"
            "out vec3 outNormal;"
            "out vec2 outTexCoord;"
            "uniform mat4 projection;"
            "uniform mat4 view;"
            "uniform mat4 model;"
            "void main( void ) {"
            "   outPosition = vec3(model * vec4(position, 1.0));"
            "   gl_Position = projection * view * vec4(outPosition, 1.0);"
            "   mat3 normalMatrix = mat3(inverse(transpose(model)));"
            "   outNormal = normalize(normalMatrix * normal);"
            "   outTexCoord = texCoord;"
            "}"
        }, {
            mb::FragmentShader,
            "#version 330\n"
            "in vec3 outPosition;"
            "in vec3 outNormal;"
            "in vec2 outTexCoord;"
            "out vec4 fragColor;"
            "uniform vec3 viewPos;"
            "uniform vec3 color;"
            "void main( void ) {"
            "   vec3 N = normalize(outNormal);"
            "   vec3 L = normalize(viewPos - outPosition);"
            "   float dif = dot(N, L);"
            "   dif = clamp(dif, 0.0, 1.0);"
            "   fragColor = vec4(color * dif, 1.0) + vec4(color * 0.1, 1.0);"
            "   fragColor.rgb += vec3(outTexCoord, 0.0);"
            "}"
        }
    };

    std::vector<std::pair<const char*, mb::Uniform*> > uniforms = {
        std::make_pair("projection", new mb::Uniform(mb::Matrix4)),
        std::make_pair("view", new mb::Uniform(mb::Matrix4)),
        std::make_pair("model", new mb::Uniform(mb::Matrix4)),
        std::make_pair("color", new mb::Uniform(mb::Vector3,
            mb::Vect3::createFromScalar(1.0f))),
        std::make_pair("viewPos", new mb::Uniform(mb::Vector3))
    };

    mb::ShaderMaterial shaderMat("shaderMat", shaders, uniforms);
    shaderMat.Cull = false;

    scene->mainCamera->layer().enable(1);
    scene->mainCamera->layer().enable(2);
    scene->mainCamera->layer().enable(3);

    std::vector<std::pair<mb::ShaderType, const char*> > shaders2 = {
        {
            mb::VertexShader,
            "#version 330 core\n"
            "layout(location = 0) in vec3 position;\n"
                "layout(location = 2) in vec2 texCoords;\n"
                "out VS_OUT {\n"
                "   vec2 texCoords;\n"
                "} vs_out;\n"
                "uniform mat4 projection;\n"
                "uniform mat4 view;\n"
                "uniform mat4 model;\n"
                "void main( void ) {\n"
                "   gl_Position = projection * view * model * vec4(position, 1.0f);\n"
                "   vs_out.texCoords = texCoords;\n"
                "}"
        }, {
            mb::GeometryShader,
            "#version 330 core\n"
            "layout (triangles) in;\n"
            "layout (triangle_strip, max_vertices = 3) out;\n"
            "in VS_OUT {\n"
            "    vec2 texCoords;\n"
            "} gs_in[];\n"
            "out vec2 TexCoords; \n"
            "uniform float time;\n"
            "vec4 explode(vec4 position, vec3 normal) {\n"
            "    float magnitude = 1.0;\n"
            "    vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * magnitude; \n"
            "    return position + vec4(direction, 0.0);\n"
            "}\n"
            "vec3 GetNormal() {\n"
            "    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);\n"
            "    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);\n"
            "    return normalize(cross(a, b));\n"
            "}\n"
            "void main( void ) {\n"
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
            "}"
        }, {
            mb::FragmentShader,
            "#version 330\n"
            "out vec4 fragColor;\n"
            "uniform vec3 color;\n"
            "void main( void ) {\n"
            "   fragColor = vec4(color, 1.0);\n"
            "}"
        }
    };

    std::vector<std::pair<const char*, mb::Uniform*> > uniforms2 = {
        std::make_pair("projection", new mb::Uniform(mb::Matrix4)),
        std::make_pair("view", new mb::Uniform(mb::Matrix4)),
        std::make_pair("model", new mb::Uniform(mb::Matrix4)),
        std::make_pair("color", new mb::Uniform(mb::Vector3, mb::Vect3(mb::Color3::Yellow))),
        std::make_pair("time", new mb::Uniform(mb::Float, 0.015f))
    };

    mb::ShaderMaterial material2("geomExplosion", shaders2, uniforms2);

    mb::Node* mbCube = new mb::Node(std::string("cube"));
    mbCube->addComponent(mb::ComponentPtr(new mb::MeshRenderer(cube, mb::MaterialCache::get("shaderMat"))));
    mbCube->addComponent(mb::ComponentPtr(new mb::MoveComponent()));
    mbCube->addComponent(mb::ComponentPtr(new mb::RotateComponent(mb::Axis::x)));
    mbCube->transform().position().set(0.0f, 3.15f, -8.98f);
    mbCube->transform().scale().set(2.0f, 2.0f, 1.0f);
    mbCube->layer().set(1);

    mb::Node* mbPrism = new mb::Node(std::string("prism"));
    mbPrism->addComponent(mb::ComponentPtr(new mb::MeshRenderer(prism, &normalMat)));
    mbPrism->transform().position().set(-0.44f, -2.0f, 2.35f);
    mbPrism->transform().scale().set(0.5f, 0.5f, 1.0f);
    mbCube->addChild(mb::NodePtr(mbPrism));
    mbPrism->layer().set(2);

    mb::Node* mbCapsule = new mb::Node(std::string("capsule"));
    mbCapsule->addComponent(mb::ComponentPtr(new mb::MeshRenderer(mb::ResourceDrawable::get("capsule"), &normalMat)));
    mbCapsule->transform().position().set(-1.44f, -2.5f, 0.87f);
    mbPrism->addChild(mb::NodePtr(mbCapsule));
    mbCapsule->layer().set(3);

    mb::Node* mbTorus = new mb::Node(std::string("torus"));
    mbTorus->addComponent(mb::ComponentPtr(new mb::MeshRenderer("torus", &material2)));
    mbTorus->addComponent(mb::ComponentPtr(new ExplosionComponent()));
    mbTorus->transform().position().set(1.1f, -1.91f, -1.08f);
    mbTorus->transform().scale().set(1.0f, 0.5f, 1.0f);
    mbCube->addChild(mb::NodePtr(mbTorus));
    mbTorus->layer().set(2);

    mb::Node* mbCylinder = new mb::Node(std::string("cylinder"));
    mbCylinder->addComponent(mb::ComponentPtr(new mb::MeshRenderer(cylinder, &material)));
    mbCylinder->transform().position().set(1.44f, -2.5f, 0.8f);
    mbCylinder->transform().scale().set(0.5f, 1.0f, 2.0f);
    mbTorus->addChild(mb::NodePtr(mbCylinder));
    mbCylinder->layer().set(3);

    std::function<void()> f0([&]() {
        std::cout << "SCENE HAS " << scene->root( )->children().size() << " CHILDREN" << std::endl;
    });

    std::function<void()> f1([&]() {
        mb::LOG(mb::LOG::INFO) << "FIRST RENDER FINISHED";
    });

    std::function<void()> f2([&]() {
        std::cout << "MESHES: " << scene->profiler.totalMeshes << ", ";
        std::cout << "VERTICES: " << scene->profiler.totalVertices << ", ";
        std::cout << "INDICES: " << scene->profiler.totalIndices << std::endl;
    });

    scene->registerBeforeRender(f0);
    scene->registerAfterRender(f1);
    scene->registerAfterRender(f2, true);

    scene->root( )->addChild(mb::NodePtr(mbCube));

  scene->root( )->traverse([](const mb::Node* n)
  {
    std::cout << n->name() << std::endl;
  });

    engine->run(renderFunc);

    delete(scene);
    delete(engine);

    return 0;
}

void renderFunc( float dt )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    if (mb::Input::isKeyClicked(mb::Keyboard::Key::Num1))
    {
        scene->mainCamera->layer().toggle(1);
    }
    if (mb::Input::isKeyClicked(mb::Keyboard::Key::Num2))
    {
        scene->mainCamera->layer().toggle(2);
    }
    if (mb::Input::isKeyClicked(mb::Keyboard::Key::Num3))
    {
        scene->mainCamera->layer().toggle(3);
    }
    scene->render( dt );
}