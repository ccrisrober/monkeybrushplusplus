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

#ifndef __MB_SCENE__
#define __MB_SCENE__

#include <mb/api.h>

#include "../SimpleCamera.hpp"
#include "Node.hpp"

namespace MB
{
	class Scene
	{
	public:
		MB_API
		Scene();
		MB_API
		void render(float dt);
		MB_API
		Node* root() const;
		MB_API
		Node* findByName(const std::string& name);
		MB_API
		Node* findByTag(const std::string& tag);
		MB_API
		void registerBeforeRender(const std::function<void()>& cb, bool recyclable = false);
		MB_API
		void registerAfterRender(const std::function<void()>& cb, bool recyclable = false);
		MB_API
		SimpleCamera* camera = new SimpleCamera(Vect3(0.2f, 0.18f, 8.44f));
	private:
		void applyQueue(std::vector<std::pair<std::function<void()>, bool> >& queue);
		Node* _searchName(const std::string& name, Node* elem);
		Node* _searchTag(const std::string& tag, Node* elem);
	protected:
		std::vector<std::pair<std::function<void()>, bool>> _beforeRender;
		std::vector<std::pair<std::function<void()>, bool>> _afterRender;
		void _subrender(Node* n, float dt);
		Node* _sceneGraph;

		unsigned int _totalMeshes;
		//unsigned int _totalVertices;
		//unsigned int _drawCalls;
		//unsigned int _totalIndices;

	};
}

#endif /* __MB_SCENE__ */