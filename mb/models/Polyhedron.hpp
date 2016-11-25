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

#ifndef __MB_POLYHEDRON__
#define __MB_POLYHEDRON__

#include <mb/api.h>

#include "Drawable.hpp"
#include "../maths/Mathf.hpp"
#include <map>

typedef unsigned int uint;

namespace MB
{
    class Polyhedron: public Drawable
    {
    public:

        std::vector<float> verts;
        std::vector<float> norms;
        std::vector<float> tex;
        std::vector<unsigned int> el;
        
        std::map<std::string, unsigned int> _pointsCache;

        float _radius;
        float _subdivisions;


        MB_API
        Polyhedron(const float radius, const float subdivisions)
        {
            _radius = radius;
            _subdivisions = subdivisions;
            
            // Normalize
            for (unsigned int i = 0, size = verts.size(); i < size; i += 3)
            {
                float mod = std::sqrt(verts[i] * verts[i] + verts[i + 1] * verts[i + 1] +
                    verts[i + 2] * verts[i + 2]);
                float nX = verts[i] / mod;
                float nY = verts[i + 1] / mod;
                float nZ = verts[i + 2] / mod;
                norms.push_back(nX);
                norms.push_back(nY);
                norms.push_back(nZ);

                tex.push_back(std::atan2(nX, nZ));
                tex.push_back(std::acos(nY));
                verts[i] *= radius / mod;
                verts[i + 1] *= radius / mod;
                verts[i + 2] *= radius / mod;
            }


            std::function<uint<uint, uint>> midPoint([&](uint a, uint b) 
            {
	    		std::string key = el[a] < el[b] ? 
	    			std::to_string(el[a]) + ":" + std::to_string(el[b]) : 
	    			std::to_string(el[b]) + ":" + std::to_string(el[a]);

				std::map<std::string, unsigned int>::iterator r = _pointsCache.find(key);
				if (r != _pointsCache.end())
				{
					return r->second;
				}

	            unsigned int index = verts.size() / 3;
	            verts.push_back((verts[el[a] * 3] + verts[el[b] * 3]) * 0.5f);
	            verts.push_back((verts[el[a] * 3 + 1] + verts[el[b] * 3 + 1]) * 0.5f);
	            verts.push_back((verts[el[a] * 3 + 2] + verts[el[b] * 3 + 2]) * 0.5f);

	            float mod = std::sqrt(verts[index * 3] *
	                verts[index * 3] + verts[index * 3 + 1] *
	                verts[index * 3 + 1] + verts[index * 3 + 2] * verts[index * 3 + 2]);
	            float nX = verts[index * 3] / mod;
	            float nY = verts[index * 3 + 1] / mod;
	            float nZ = verts[index * 3 + 2] / mod;

	            norms.push_back(nX);
	            norms.push_back(nY);
	            norms.push_back(nZ);

	            tex.push_back((std::atan2(nX, nZ) / Mathf::PI) * 0.5f);
	            tex.push_back(std::acos(nY) / Mathf::PI);
	            verts[index * 3] *= radius / mod;
	            verts[index * 3 + 1] *= radius / mod;
	            verts[index * 3 + 2] *= radius / mod;

	            _pointsCache[key] = index;
	            return index;
            });

            // Regenerate indices
            for (unsigned int ir = 0; ir < subdivisions; ++ir)
            {
                std::vector<unsigned int> new_el;
                for (unsigned int i = 0, size = el.size(); i < size; i += 3)
                {
                    unsigned int midA = midPoint(i, i + 1);
                    unsigned int midB = midPoint(i + 1, i + 2);
                    unsigned int midC = midPoint(i + 2, i);
                    new_el.push_back(el[i]);
                    new_el.push_back(midA);
                    new_el.push_back(midC);
                    new_el.push_back(el[i + 1]);
                    new_el.push_back(midB);
                    new_el.push_back(midA);
                    new_el.push_back(el[i + 2]);
                    new_el.push_back(midC);
                    new_el.push_back(midB);
                    new_el.push_back(midA);
                    new_el.push_back(midB);
                    new_el.push_back(midC);
                }
                el = new_el;
            }

            _pointsCache.clear();
        }
    };
}

#endif /* __MB_POLYHEDRON__ */
