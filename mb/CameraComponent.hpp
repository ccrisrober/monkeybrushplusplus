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

#ifndef __MB_CAMERA_COMPONENT__
#define __MB_CAMERA_COMPONENT__

#include <mb/api.h>

#include "scene/Component.hpp"
#include "maths/Mathf.hpp"

enum CameraType_t
{
	CAMERA_TYPE_ORTHO,
	CAMERA_TYPE_PERSPECTIVE
};

enum PlaneType_t {
	PLANE_LEFT = 0,
	PLANE_RIGHT,
	PLANE_BOTTOM,
	PLANE_TOP,
	PLANE_NEAR,
	PLANE_FAR,
	PLANE_NUM_PLANES
};

namespace mb
{
	class CameraComponent : public Component
	{
	public:
		MB_API
		CameraComponent(int width, int height)
		{
			cameraType = CAMERA_TYPE_PERSPECTIVE;

			// TODO: view and proj as identity matrix ??

			fov = mb::Mathf::degToRad(60.0f);

			ortho_bounds_x_min = 0.0f;
			ortho_bounds_x_max = width;
			ortho_bounds_y_min = -height;
			ortho_bounds_y_max = 0.0f;
			ortho_bounds_z_min = -500.0f;
			ortho_bounds_z_max = 500.0f;

			aspectRatio = (float)width / (float)height;
		
			updateMatrices();
		}

		Mat4 GetViewMatrix() const
		{
			return viewMatrix;
		}
		Mat4 GetProjectionMatrix() const
		{
			return projMatrix;
		}
		CameraType_t GetCameraType() const
		{
			return cameraType;
		}
		void SetCameraType(CameraType_t type)
		{
			cameraType = type;
			updateMatrices();
		}

		float getFOV() const
		{
			return fov;
		}
		void setFOV(const float& newFov)
		{
			fov = newFov;
			updateMatrices();
		}
		void SetOrthoBounds(float x_min, float x_max,
			float y_min, float y_max,
			float z_min, float z_max)
		{
			ortho_bounds_x_min = x_min;
			ortho_bounds_x_max = x_max;
			ortho_bounds_y_min = y_min;
			ortho_bounds_y_max = y_max;
			ortho_bounds_z_min = z_min;
			ortho_bounds_z_max = z_max;

			updateMatrices();
		}

		virtual void start()
		{

		}

	protected:
		void updateMatrices()
		{
			Node* node = this->getNode();
			
			Vect3 eyePosition = node->transform().position();
			Vect3 lookAt;
			Vect3 upVector;

			viewMatrix = Mat4::lookAt(eyePosition, lookAt, upVector);

			// TODO: Update width/height and aspectRatio

			switch (cameraType)
			{
			case CAMERA_TYPE_ORTHO: {
				projMatrix = Mat4::orthographic(
					ortho_bounds_x_min, ortho_bounds_x_max,
					ortho_bounds_y_min, ortho_bounds_y_max,
					ortho_bounds_z_min, ortho_bounds_z_max);
			}
			break;
			case CAMERA_TYPE_PERSPECTIVE: {
				projMatrix = Mat4::perspective(fov, aspectRatio, 0.3f, 250.0f);
			}
			break;
			default:
				throw "Unknow camera type";
			}
			updateFrustrum();
		}
		void updateFrustrum() {
			/*Mat4 viewProj = Mat4::mult2(projMatrix, viewMatrix);

			// Left plane
			frustumPlanes[PLANE_LEFT] = Vect4(
				viewProj._values[0][3] + viewProj._values[0][0],
				viewProj._values[1][3] + viewProj._values[1][0],
				viewProj._values[2][3] + viewProj._values[2][0],
				viewProj._values[3][3] + viewProj._values[3][0]);

			// Right plane
			frustumPlanes[PLANE_RIGHT] = Vect4(
				viewProj._values[0][3] - viewProj._values[0][0],
				viewProj._values[1][3] - viewProj._values[1][0],
				viewProj._values[2][3] - viewProj._values[2][0],
				viewProj._values[3][3] - viewProj._values[3][0]);


			// Top plane
			frustumPlanes[PLANE_TOP] = Vect4(
				viewProj._values[0][3] - viewProj._values[0][1],
				viewProj._values[1][3] - viewProj._values[1][1],
				viewProj._values[2][3] - viewProj._values[2][1],
				viewProj._values[3][3] - viewProj._values[3][1]);

			// Bottom plane
			frustumPlanes[PLANE_BOTTOM] = Vect4(
				viewProj._values[0][3] + viewProj._values[0][1],
				viewProj._values[1][3] + viewProj._values[1][1],
				viewProj._values[2][3] + viewProj._values[2][1],
				viewProj._values[3][3] + viewProj._values[3][1]);

			// Near plane
			frustumPlanes[PLANE_NEAR] = Vect4(
				viewProj._values[0][3] + viewProj._values[0][2],
				viewProj._values[1][3] + viewProj._values[1][2],
				viewProj._values[2][3] + viewProj._values[2][2],
				viewProj._values[3][3] + viewProj._values[3][2]);

			// Far plane
			frustumPlanes[PLANE_FAR] = Vect4(
				viewProj._values[0][3] - viewProj._values[0][2],
				viewProj._values[1][3] - viewProj._values[1][2],
				viewProj._values[2][3] - viewProj._values[2][2],
				viewProj._values[3][3] - viewProj._values[3][2]);
			
			for (int i = 0; i < PLANE_NUM_PLANES; ++i) {
				float magnitude = sqrt(this->frustumPlanes[i].x * this->frustumPlanes[i].x +
					this->frustumPlanes[i].y * this->frustumPlanes[i].y +
					this->frustumPlanes[i].z * this->frustumPlanes[i].z);
				this->frustumPlanes[i][0] /= magnitude;
				this->frustumPlanes[i][1] /= magnitude;
				this->frustumPlanes[i][2] /= magnitude;
				this->frustumPlanes[i][3] /= magnitude;
			}*/
		}

		CameraType_t cameraType;
		Mat4 viewMatrix;
		Mat4 projMatrix;

		Vect4 frustrumPlanes[PLANE_NUM_PLANES];

		float fov;
		float aspectRatio;

		float ortho_bounds_x_min, ortho_bounds_x_max;
		float ortho_bounds_y_min, ortho_bounds_y_max;
		float ortho_bounds_z_min, ortho_bounds_z_max;
	};
}

#endif /* __MB_CAMERA_COMPONENT__ */
