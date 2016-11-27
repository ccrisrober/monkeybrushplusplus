/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus <https://github.com/maldicion069/monkeybrushplusplus>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0f as published
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

#ifndef __MB_PARTICLE_SYSTEM__
#define __MB_PARTICLE_SYSTEM__

#include <mb/api.h>

#include "../models/Drawable.hpp"
#include "../materials/Material.hpp"
#include "../cameras/Camera.hpp"

namespace mb
{
	class ParticleSystem
    {
    public:
        ParticleSystem(mb::Drawable* mesh, mb::Material* material)
			: _mesh(mesh)
			, _material(material)
        {

        }
        void sort(mb::Camera& /*camera*/)
        {
            if (_sortParticles)
            {
                /*std::sort(positions.begin(), position.end(), [&](Vect3& a, Vect3& b)
                {
					Vect3& aa = Vect3::sub(camera.transform().position(), a);
					Vect3& bb = Vect3::sub(camera.transform().position(), b);
                    return aa.length() > bb.length();
                });*/
            }
        }
        void sort(bool _sort)
        {
            this->_sortParticles = _sort;
        }

    protected:
        bool _sortParticles;
		mb::Drawable* _mesh;
		mb::Material* _material;
    };
}

#endif /* __MB_PARTICLE_SYSTEM__ */
