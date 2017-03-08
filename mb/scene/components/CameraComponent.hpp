/*
 * Copyright (c) 2017 maldicion069
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

#ifndef __MB_CAMERA_COMPONENT__
#define __MB_CAMERA_COMPONENT__

#include <mb/api.h>

#include "Component.hpp"
#include "../../maths/Mat4.hpp"
#include "../../maths/Frustum.hpp"

namespace mb
{
	class CameraComponent: public Component
	{
	public:
		MB_API
		explicit CameraComponent( void );
		MB_API
		CameraComponent( float fov, float aspect, float near, float far );
		MB_API
		virtual ~CameraComponent( void );
		MB_API
		bool isMainCamera( void ) const {
			return _isMainCamera;
		}
		MB_API
		void setIsMainCamera( bool value )
		{
			_isMainCamera = value;
		}
		MB_API
		const mb::Frustum &getFrustum(void) const { return _frustum; }
		MB_API
		void setFrustum(const Frustum& f);
		MB_API
		void setAspectRatio(const float& width, const float& height)
		{
			setAspectRatio(width / height);
		}
		MB_API
		void setAspectRatio(const float& aspect)
		{
			auto &f = getFrustum();
			setFrustum(mb::Frustum(
				-aspect * f.getUMax(),
				aspect * f.getUMax(),
				f.getUMin(),
				f.getUMax(),
				f.getDMin(),
				f.getDMax())
			);
		}
	private:
		bool _isMainCamera = false;
		mb::Frustum _frustum;
		mb::Mat4 _projectionMatrix;
		mb::Mat4 _orthographicMatrix;
		mb::Mat4 _viewMatrix;
	public:
		static CameraComponent* getMainCamera( void ) { return _mainCamera; }
		static void setMainCamera( CameraComponent* camera ) {
			_mainCamera = camera;
			camera->setIsMainCamera( true );
		}
	private:
		static CameraComponent* _mainCamera;
	};
}

#endif /* __MB_CAMERA_COMPONENT__ */
