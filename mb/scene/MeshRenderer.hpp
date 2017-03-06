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

#ifndef __MB_MESH_RENDERER__
#define __MB_MESH_RENDERER__

#include <mb/api.h>

#include "../models/Drawable.hpp"
#include "../models/IDrawable.hpp"
#include "../materials/Material.hpp"
#include "Component.hpp"

namespace mb
{
  class MeshRenderer: public Component
  {
  //MB_IMPLEMENT_RTTI(mb::MeshRenderer)
  public:
    MB_API
    static std::shared_ptr<mb::MeshRenderer> create(
      mb::DrawablePtr mesh, MaterialPtr material,
      unsigned int mode = GL_TRIANGLES )
    {
      return std::make_shared<mb::MeshRenderer>( mesh, material, mode );
    }
    MB_API
    MeshRenderer(mb::DrawablePtr mesh, MaterialPtr material,
      unsigned int mode_ = GL_TRIANGLES);
    MB_API
    MeshRenderer(const std::string& name, MaterialPtr material,
      unsigned int mode_ = GL_TRIANGLES);
    MB_API
    MaterialPtr getMaterial( void ) const;
    MB_API
    mb::DrawablePtr getMesh( void ) const;
    MB_API
    void setMaterial(MaterialPtr m);
    MB_API
    void setMesh(mb::DrawablePtr m);
    //MB_API
    void render( void );
    MB_API
    unsigned int mode( void );
    MB_API
    void setMode(unsigned int m);

    // TODO: UNUSED
    MB_API
    void setMaterials( const std::vector<MaterialPtr>& mats )
    {
      this->_materials = mats;
    }
  protected:
    mb::DrawablePtr _mesh;
    std::vector<MaterialPtr> _materials;
    MaterialPtr _material;
    unsigned int _mode;
  };
}

#endif /* __MB_MESH_RENDERER__ */
