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

#ifndef __MB_MESH_RENDERER__
#define __MB_MESH_RENDERER__

#include "../models/Drawable.hpp"
#include "../materials/Material.hpp"
#include "Component.hpp"

namespace MB {
	class Node;
	class MeshRenderer: public Component {
	public:
		MeshRenderer(Drawable* mesh, Material* material)
		: Component()
		, _mesh(mesh)
		, _material(material)
		{
		}
		Material* getMaterial() const {
			return this->_material;
		}
		Drawable* getMesh() const {
			return this->_mesh;
		}
		void setMaterial(Material* m) {
			this->_material = m;
		}
		void setMesh(Drawable* m) {
			this->_mesh = m;
		}
		void render()
		{
			this->_node->_updateMatrixWorld();
			this->_material->uniforms()["model"] = 1;
			// this._material._uniforms["model"].value = this.node.transform._matrixWorld;
			this->_material->use();
			this->_mesh->render();
		}
	protected:
		Drawable* _mesh;
		Material* _material;
	};
}

#endif /* __MB_MESH_RENDERER__ */