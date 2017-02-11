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

#ifndef __MB_LIGHT__
#define __MB_LIGHT__

#include <mb/api.h>

#include "../core/Color3.hpp"
#include "../Includes.hpp"

namespace mb
{
  /*template<typename T>
  inline std::shared_ptr<T> make_shared()
  {
  struct Derived : public T { };
  return std::make_shared<Derived>();
  }
  template <typename T, typename... Args>
  inline std::shared_ptr<T> make_shared(Args&& ... args)
  {
  return std::make_shared<Derived<T>>(std::move(args)...);
  }*/

  enum class ShadowType
  {
    None,
    Hard,
    Soft
  };

  class Light
  {
  public:
    MB_API
      float intensity( ) const;
    MB_API
      Vect3 attenuation( ) const;
    MB_API
      bool isEnable( ) const;
    MB_API
      Color3 color( ) const;
    MB_API
      Color3 specColor( ) const;
    MB_API
      void intensity( const float i );
    MB_API
      void attenuation( const Vect3 att );
    MB_API
      void enabled( const bool e );
    MB_API
      void color( const Color3& c );
    MB_API
      void specColor( const Color3& sc );
    MB_API
      ShadowType getShadowType( ) const;
    MB_API
      void setShadowType( ShadowType shadow );
  protected:
    Light( );
    float _intensity;
    bool _enable;
    Vect3 _attenuation;
    Color3 _color;
    Color3 _specColor;
    ShadowType _shadowType;
  };
  typedef std::shared_ptr<Light> LightPtr;
}

#endif /* __MB_LIGHT__ */
