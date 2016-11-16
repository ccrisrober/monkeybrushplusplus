/*
* Copyright (c) 2016 maldicion069
*
* Authors: Cristian Rodríguez Bernal
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

#include "MeshRenderer.hpp"

namespace MB
{
	MeshRenderer::MeshRenderer(Drawable* mesh, Material* material)
		: Component()
		, _mesh(mesh)
		, _material(material)
	{
	}
	Material* MeshRenderer::getMaterial() const
	{
		return this->_material;
	}
	Drawable* MeshRenderer::getMesh() const
	{
		return this->_mesh;
	}
	void MeshRenderer::setMaterial(Material* m)
	{
		this->_material = m;
	}
	void MeshRenderer::setMesh(Drawable* m)
	{
		this->_mesh = m;
	}
	void MeshRenderer::render()
	{
		this->_node->_updateMatrixWorld();
		// this._material._uniforms["model"].value = this.node.transform._matrixWorld; // TODO
		this->_material->use();
		this->_mesh->render();
	}
}