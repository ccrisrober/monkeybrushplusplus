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

#include "Window.hpp"
#include "Input.hpp"
#include <string>

namespace mb
{
  WindowParams::WindowParams( int width_, int height_ )
  {
    this->width = width_;
    this->height = height_;
    this->displayFPS = true;
    this->displayMouse = true;
    this->debugWindowEvents = true;
    this->minVersion = 3;
    this->maxVersion = 3;
    this->resizable = true;
    this->depthBufferBit = 24;
    this->multiSample = 4;
  }
  bool GLFWWindow2::init( )
  {
    mb::LOG( mb::LOG::INFO ) << "Initializing GLFW";
    if ( !glfwInit( ) )
    {
      throw "Failed to initialise GLFW";
    }
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, _params.maxVersion );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, _params.minVersion );
    glfwWindowHint( GLFW_SAMPLES, ( int ) _params.multiSample );
    glfwWindowHint( GLFW_DEPTH_BITS, ( int ) _params.depthBufferBit );
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint( GLFW_RESIZABLE, _params.resizable );

    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE );


    this->_handle = glfwCreateWindow( _params.width, _params.height, _params.title, nullptr, nullptr );

    if ( _handle == nullptr )
    {
      glfwTerminate( );
      throw "Failed to create window with GLFW.";
    }

    glfwSetKeyCallback( _handle, []( GLFWwindow*, int key, int, int action, int )
    {
      if ( action == GLFW_PRESS )
      {
        static_cast<GLFWKeyboard*>( Input::Keyboard( ) )->onKeyDown( key );
      }
      else if ( action == GLFW_RELEASE )
      {
        static_cast<GLFWKeyboard*>( Input::Keyboard( ) )->onKeyUp( key );
      }
    } );

    glfwSetCursorPosCallback( _handle, []( GLFWwindow*, double xpos, double ypos )
    {
      static_cast<GLFWMouse*>( Input::Mouse( ) )->onMouseMove( static_cast<int>( xpos ), static_cast<int>( ypos ) );
    } );

    glfwSetMouseButtonCallback( _handle, []( GLFWwindow*, int button, int action, int )
    {
      static_cast<GLFWMouse*>( Input::Mouse( ) )->onMouseButtonEvent( button, action );
    } );

    glfwSetScrollCallback( _handle, []( GLFWwindow*, double xoffset, double yoffset )
    {
      static_cast<GLFWMouse*>( Input::Mouse( ) )->onMouseWheelEvent( static_cast<int>( xoffset ), static_cast<int>( yoffset ) );
    } );

    glfwSetWindowSizeCallback( _handle, ( []( GLFWwindow* window, int width, int height )
    {
      glViewport( 0, 0, width, height );
      // TODO: Send event and set width and height from _params
    } ) );

    glfwSetInputMode( _handle, GLFW_STICKY_KEYS, GL_TRUE );
    glfwMakeContextCurrent( _handle );

    mb::LOG( mb::LOG::INFO ) << "GLFW initialized";


    mb::LOG( mb::LOG::INFO ) << "Initializing GLEW";
    // Initialize GLEW to setup the OpenGL Function pointers
    glewExperimental = ( GLboolean ) true;
    if ( glewInit( ) != GLEW_OK )
    {
      glfwTerminate( );
      throw "Failed to initialise GLEW";
    }

    mb::LOG( mb::LOG::INFO ) << "OpenGL functions succesfully loaded.";
    mb::LOG( mb::LOG::INFO ) << "Version - Major: " << std::to_string( _params.maxVersion )
      << " Minor: " << std::to_string( _params.minVersion );
    mb::LOG( mb::LOG::INFO ) << "Driver: " << ( char* ) glGetString( GL_VENDOR ) << " Renderer: " << ( char* ) glGetString( GL_RENDERER );

    mb::LOG( mb::LOG::INFO ) << "GLEW initialized";

    return true;
  }
  void* GLFWWindow2::getWindow( )
  {
    return this->_handle;
  }
  GLFWWindow2::GLFWWindow2( const WindowParams& params )
    : mb::Window( params )
  {
    _handle = nullptr;
  }
  GLFWWindow2::~GLFWWindow2( )
  {
    glfwTerminate( );
  }
  void GLFWWindow2::setTitle( const char* title )
  {
    glfwSetWindowTitle( _handle, title );
  }
  bool GLFWWindow2::isRunning( )
  {
    return glfwWindowShouldClose( _handle ) == 0;
  }
  void GLFWWindow2::pollEvents( )
  {
    glfwPollEvents( );
  }
  void GLFWWindow2::close( )
  {
    glfwTerminate( );
  }
  void GLFWWindow2::swapBuffers( )
  {
    glfwSwapBuffers( _handle );
  }
}
