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
#include "../materials/Uniform.hpp"
#include "../resources/ResourceDrawable.hpp"

namespace MB
{
	MeshRenderer::MeshRenderer(Drawable* mesh, Material* material)
		: Component()
		, _mesh(mesh)
		, _material(material)
	{
	}
	MeshRenderer::MeshRenderer(const std::string& name, Material* material)
		: MeshRenderer(MB::ResourceDrawable::get(name), material)
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
		auto model = this->getNode()->transform().matrixWorld();
        this->_material->uniform("model")->value(model);
        //std::cout << this->_node->name() << std::endl;
        //Uniform* Uview = _material->uniforms()["model"];
        //std::cout << Uview->value().cast<Mat4>() << std::endl;
        //this->_material->uniform("color")->value(Vect3(1.0f, 0.0f, 1.0f));
		this->_material->use();
        this->_mesh->render();
	}
}
