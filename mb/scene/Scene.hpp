/*
* Copyright (c) 2016 maldicion069
*
* Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
*
* This file is part of MonkeyBrushPlusPlus
* <https://github.com/maldicion069/monkeybrushplusplus>
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

#ifndef __MB_SCENE__
#define __MB_SCENE__

#include <mb/api.h>

#include "../SimpleCamera.hpp"
#include "Node.hpp"
#include "../lights/Light.hpp"

#include "Engine.hpp"

#include <vector>

namespace mb
{
  struct Profiler
  {
    unsigned int totalMeshes;
    unsigned int totalVertices;
    unsigned int drawCalls;
    unsigned int totalIndices;
    void reset( )
    {
      totalMeshes = totalVertices = drawCalls = totalIndices = 0u;
    }
  };
  class Engine;
  class Scene
  {
  public:
    MB_API
    Scene( EnginePtr engine, SimpleCamera* camera );
    MB_API
    virtual ~Scene( );
    MB_API
    void render( float dt );
    MB_API
    mb::NodePtr root( ) const;
    MB_API
    void registerBeforeRender( const std::function<void( )>& cb,
      bool recyclable = false );
    MB_API
    void registerAfterRender( const std::function<void( )>& cb,
      bool recyclable = false );
    MB_API
    void addLight( mb::LightPtr light );
    MB_API
    std::vector<mb::LightPtr> lights( ) const;
    MB_API
    bool update( ) const;
    MB_API
    void update( const bool upd );

    SimpleCamera* mainCamera;

    template<typename T>
    std::vector<T*> findComponents( )
    {
      // TODO
      return{ };
    }
    template<typename T>
    T* findComponent( )
    {
      // TODO
      return nullptr;
    }

  private:
    void applyQueue( std::vector<std::pair<std::function<void( )>,
      bool> >& queue );
  protected:
    //SimpleCamera* camera = new SimpleCamera(Vect3(0.2f, 0.18f, 8.44f));
    std::vector<std::pair<std::function<void( )>, bool>> _beforeRender;
    std::vector<std::pair<std::function<void( )>, bool>> _afterRender;
    void _subFixedUpdate( mb::NodePtr n, float dt );
    void _subUpdate( mb::NodePtr n, float dt );
    void updateCamera( );
    mb::NodePtr _sceneGraph;

    std::vector<mb::LightPtr> _lights;

  public:
    Profiler profiler;
    bool sort = true;
  protected:
    EnginePtr _engine;

    Mat4 _projection;
    Mat4 _view;

    std::vector<mb::NodePtr> _batch;

  protected:
    bool _update;
    float _fixedUpdateTime = 0.0f;

    std::vector<float> projectedObjects;

    void projectObject( )
    {
      /*projectedObjects.clear();
      for (auto batch : _batch)
      {
      mb::Node* node = batch.get();

      auto array_ = node->transform().matrixWorld()._values;

      unsigned int index = 3;
      unsigned int offset = index * 4;
      float x = array_[offset];
      float y = array_[offset + 1];
      float z = array_[offset + 2];

      mb::Vect3 vector3(x, y, z);

      auto e = mainCamera->projectionMatrix(512, 512)._values;

      float aux = e[3] * x;
      aux += e[7] * y;
      aux += e[11] * z;
      aux += e[15];
      float d = 1.0f / (e[3] * x + e[7] * y + e[11] * z + e[15]); // perspective divide

      float xx = (e[0] * x + e[4] * y + e[8] * z + e[12]) * d;
      float yy = (e[1] * x + e[5] * y + e[9] * z + e[13]) * d;
      float zz = (e[2] * x + e[6] * y + e[10] * z + e[14]) * d;

      vector3 = mb::Vect3(xx, yy, zz);

      std::cout << vector3 << std::endl;

      projectedObjects.push_back(zz);
      }*/
    }
  };

  typedef std::shared_ptr<mb::Scene> ScenePtr;
}

#endif /* __MB_SCENE__ */
