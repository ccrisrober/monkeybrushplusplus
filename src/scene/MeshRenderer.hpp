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

#ifndef __MB_MESH_RENDERER__
#define __MB_MESH_RENDERER__

#include "../models/Drawable.hpp"
#include "../materials/Material.hpp"
#include "Component.hpp"
#include "Node.hpp"

namespace MB
{
	class MeshRenderer: public Component
	{
	public:
		MeshRenderer(Drawable* mesh, Material* material);
		MeshRenderer(const std::string& name, Material* material);
		Material* getMaterial() const;
		Drawable* getMesh() const;
		void setMaterial(Material* m);
		void setMesh(Drawable* m);
		void render();
	protected:
		Drawable* _mesh;
		Material* _material;
	};
}

#endif /* __MB_MESH_RENDERER__ */