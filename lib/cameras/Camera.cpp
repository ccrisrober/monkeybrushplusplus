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

#include "Camera.hpp"

namespace mb
{
  Camera::Camera(float near_, float far_)
    : _near(near_)
    , _far(far_)
  {
  }
  Mat4 Camera::projectionMatrix() const
  {
    return this->_projectionMatrix;
  }
  Mat4 Camera::viewMatrix() const
  {
    return this->_viewMatrix;
  }
  Transform& Camera::transform()
  {
    return this->_transform;
  }
  void Camera::setNearFar(float near, float far)
  {
    this->_near = near;
    this->_far = far;
    updateProjectionMatrix();
  }
  float Camera::near() const {
    return this->_near;
  }
  void Camera::near(float near)
  {
    this->_near = near;
    updateProjectionMatrix();
  }
  float Camera::far() const {
    return this->_far;
  }
  void Camera::far(float far)
  {
    this->_far = far;
    updateProjectionMatrix();
  }
}
