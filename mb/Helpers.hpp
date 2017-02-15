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

#ifndef __MB_HELPERS__
#define __MB_HELPERS__

#include <mb/api.h>
#include "utils/macros.hpp"

#include "scene/Component.hpp"
#include "materials/Material.hpp"
#include <thread>

namespace mb
{
	class PointMaterial : public mb::Material
	{
		MB_API
		PointMaterial( void );
	};

  void setInterval(std::function<void(void)> function, int interval)
  {
    std::thread([=]( void )
    {
      while (true) {
        function();
        std::this_thread::sleep_for(
          std::chrono::milliseconds(interval));
      }
    }).detach();
  }

	class MoveComponent : public mb::Component
	{
	public:
    MB_API
    static std::shared_ptr<mb::MoveComponent> create( )
    {
      return std::make_shared<mb::MoveComponent>( );
    }
		MB_API
		MoveComponent( void );
		MB_API
    virtual void update(const float& dt) override;
	protected:
		float _delta;
		int _sign;
		float _velocity;
	};
	enum class Axis
	{
		x, y, z
	};
	class RotateComponent : public mb::Component
	{
	public:
	#ifdef MB_USE_RAPIDJSON
		MB_API
    RotateComponent(const rapidjson::Value& config);
	#endif
		MB_API
		RotateComponent(Axis axis, float velocity = 1.0f, bool rotate = false);
		MB_API
    virtual void update(const float& dt) override;
		MB_SYNTHESIZE_WRITEONLY(bool, _rotate, Rotate);
		MB_SYNTHESIZE_WRITEONLY(Axis, _axis, Axis);

  protected:
    Axis _axisFromString( const std::string& axis );
	protected:
		float _delta;
		float _velocity;
	};
	class ScaleComponent : public mb::Component
	{
	public:
		MB_API
		ScaleComponent( void );
		MB_API
		virtual void update(const float& dt) override;
	protected:
		float _inc;
	};
	class PrintPosition : public mb::Component
	{
	public:
		MB_API
		PrintPosition( void );
		MB_API
		virtual void fixedUpdate(const float& dt) override;
	};

	class ChangeTransformationComponent : public mb::Component
	{
	public:
		MB_API
		ChangeTransformationComponent( void );
		MB_API
		virtual void start( void ) override;
		MB_API
		virtual void fixedUpdate(const float& dt) override;
	protected:
		mb::MoveComponent* _moveComp;
		mb::RotateComponent* _rotateComp;
	};
};

#endif /* __MB_HELPERS__ */
