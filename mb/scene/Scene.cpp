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

// TODO: http://gameprogrammingpatterns.com/dirty-flag.html

#include "Scene.hpp"
#include <iostream>
#include "MeshRenderer.hpp"
#include "Engine.hpp"


#include "../materials/ShaderMaterial.hpp"
#include <typeindex>
#include <typeinfo>
#include <vector>
#include <algorithm>
#include <iostream>

namespace mb
{
  Scene::Scene( EnginePtr engine, SimpleCamera* camera )
    : _sceneGraph( std::make_shared<Node>( std::string( "root" ) ) )
    , _engine( engine )
    , _update( true )
  {
    mainCamera = camera;
  }
  Scene::~Scene( )
  {
    std::cout << "REMOVE SCENE" << std::endl;
    //delete _sceneGraph;
  }
  mb::NodePtr Scene::root( ) const
  {
    return this->_sceneGraph;
  }
  void Scene::registerBeforeRender( const std::function<void( )>& cb,
    bool recyclable )
  {
    this->_beforeRender.push_back( std::make_pair( cb, recyclable ) );
  }
  void Scene::registerAfterRender( const std::function<void( )>& cb,
    bool recyclable )
  {
    this->_afterRender.push_back( std::make_pair( cb, recyclable ) );
  }
  void Scene::applyQueue( std::vector<std::pair<std::function<void( )>,
    bool> >& queue )
  {
    auto i = std::begin( queue );
    while ( i != std::end( queue ) )
    {
      i->first( );
      if ( i->second == false )
      {
        i = queue.erase( i );
      }
      else
      {
        ++i;
      }
    }
  }
  void Scene::render( float dt )
  {
    profiler.reset( );

    if ( !_update )
    {
      return;
    }

    _batch.clear( );

    // Before render functions
    applyQueue( _beforeRender );


    // http://www.mel-georgiou.co.uk/category/unity3d-tutorials/unity3d-optimization-techniques/
    _fixedUpdateTime += dt;
    if ( _fixedUpdateTime > 0.02f )
    {
      _subFixedUpdate( root( ), _fixedUpdateTime );
      _fixedUpdateTime = 0.0f;
    }

    _subUpdate( root( ), dt );

    mainCamera->update( dt );
    updateCamera( );

    projectObject( );

    if ( sort )
    {
      std::sort( _batch.begin( ), _batch.end( ), []( NodePtr& mm1, NodePtr& mm2 )
      {
        MaterialPtr m1 = mm1.get( )->getMesh( )->getMaterial( );
        MaterialPtr m2 = mm2.get( )->getMesh( )->getMaterial( );
        static auto smType = std::type_index( typeid( mb::ShaderMaterial ) );

        auto type1 = std::type_index( typeid( *m1 ) );
        auto type2 = std::type_index( typeid( *m2 ) );

        if ( type1 == type2 )
        {
          if (
            ( type1 == smType )
            &&
            ( type2 == smType )
            )
          {
            mb::ShaderMaterial* sm1 = dynamic_cast<mb::ShaderMaterial*>( m1.get( ) );
            mb::ShaderMaterial* sm2 = dynamic_cast<mb::ShaderMaterial*>( m2.get( ) );

            if ( sm1->name( ) != sm2->name( ) )
            {
              return sm1->name( ) < sm2->name( );
            }
          }

          VertexArray* v1 = mm1->getMesh( )->getMesh( )->vertexArray( );
          VertexArray* v2 = mm2->getMesh( )->getMesh( )->vertexArray( );

          return v1->handler( ) < v2->handler( );
        }
        return type1 < type2;
      } );
    }
    for ( const auto& node : _batch )
    {
      auto mr = node->getMesh( );
      if ( mr->getMaterial( )->hasUniform( "projection" ) )
      {
        mr->getMaterial( )->uniforms( )["projection"]->value( _projection );
      }
      if ( mr->getMaterial( )->hasUniform( "view" ) )
      {
        mr->getMaterial( )->uniforms( )["view"]->value( _view );
      }
      if ( mr->getMaterial( )->hasUniform( "viewPos" ) )
      {
        mr->getMaterial( )->uniform( "viewPos" )->value( this->mainCamera->GetPos( ) );
      }
      mr->render( );
      ++profiler.totalMeshes;
      profiler.totalIndices += mr->getMesh( )->indicesLen( );
      profiler.totalVertices += mr->getMesh( )->verticesLen( );
    }

    // After render functions
    applyQueue( _afterRender );

    // Restore state
    this->_engine->state( )->depth.setStatus( true );
    this->_engine->state( )->depth.setMask( true );
  }
  void Scene::_subFixedUpdate( mb::NodePtr n, float dt )
  {
    if ( !n.get( )->isVisible( ) )
    {
      return;
    }
    for ( const auto& comp : n.get( )->getComponents( ) )
    {
      if ( comp.get( )->isEnabled( ) )
      {
        comp.get( )->fixedUpdate( dt );
      }
    }
    for ( auto& child : n.get( )->children( ) )
    {
      this->_subFixedUpdate( child, dt );
    }
  }
  void Scene::_subUpdate( mb::NodePtr n, float dt )
  {
    if ( !n->isVisible( ) )
    {
      return;
    }
    for ( const auto& comp : n->getComponents( ) )
    {
      if ( comp.get( )->isEnabled( ) )
      {
        comp.get( )->update( dt );
      }
    }
    n->_updateMatrixWorld( );

    if ( ( mainCamera->layer( ).check( n->layer( ) ) ) && ( n->getMesh( ) != nullptr ) )
    {
      _batch.push_back( n );
    }
    for ( auto& child : n->children( ) )
    {
      this->_subUpdate( child, dt );
    }
  }
  void Scene::updateCamera( )
  {
    _projection = this->mainCamera->projectionMatrix(
      this->_engine->context( )->getWidth( ),
      this->_engine->context( )->getHeight( ) );
    _view = this->mainCamera->viewMatrix( );
  }
  void Scene::addLight( mb::LightPtr light )
  {
    for ( const auto& l : _lights )
    {
      if ( l == light )
      {
        return;
      }
    }
    _lights.push_back( light );
  }
  std::vector<mb::LightPtr> Scene::lights( ) const
  {
    return this->_lights;
  }
  bool Scene::update( ) const
  {
    return _update;
  }
  void Scene::update( const bool upd )
  {
    _update = upd;
  }
}
