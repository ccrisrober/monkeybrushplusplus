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

#include "MeshRenderer.hpp"
#include "../../materials/Uniform.hpp"
#include "../../resources/ResourceDrawable.hpp"
#include "../Node.hpp"

namespace mb
{
  MeshRenderer::MeshRenderer(mb::DrawablePtr mesh, MaterialPtr material,
    unsigned int mode_)
    : Component()
    , _mesh(mesh)
    , _material(material)
    , _mode(mode_)
  {
  }
  MeshRenderer::MeshRenderer(const std::string& name, MaterialPtr material,
    unsigned int mode_)
    : MeshRenderer(mb::ResourceDrawable::get(name), material, mode_)
  {
  }
  MaterialPtr MeshRenderer::getMaterial() const
  {
    return this->_material;
  }
  mb::DrawablePtr MeshRenderer::getMesh() const
  {
    return this->_mesh;
  }
  void MeshRenderer::setMaterial(MaterialPtr m)
  {
    this->_material = m;
  }
  void MeshRenderer::setMesh(mb::DrawablePtr m)
  {
    this->_mesh = m;
  }
  void MeshRenderer::render()
  {
    this->_material->uniform("model")->value(_node->transform().matrixWorld());

    this->_material->use();

    this->_mesh->render(_mode);
  }
  unsigned int MeshRenderer::mode()
  {
    return this->_mode;
  }
  void MeshRenderer::setMode(unsigned int m)
  {
    this->_mode = m;
  }
}
