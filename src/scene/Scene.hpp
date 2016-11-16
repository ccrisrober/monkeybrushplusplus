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

#ifndef __MB_SCENE__
#define __MB_SCENE__

#include "Node.hpp"

namespace MB
{
	class Scene
	{
	public:
		Scene();
		void render(float dt);
		Node* root() const;
		Node* findByName(const std::string& name)
		{
			Node* toRet = this->_searchName(name, root());
			return toRet;
		}
		Node* findByTag(const std::string& tag)
		{
			Node* toRet = this->_searchTag(tag, root());
			return toRet;
		}
		void registerBeforeRender(const std::function<void()>& cb, bool recyclable = false) {
			this->_beforeRender.push_back(std::make_pair(cb, recyclable));
		};
		void registerAfterRender(const std::function<void()>& cb, bool recyclable = false) {
			this->_afterRender.push_back(std::make_pair(cb, recyclable));
		};
	private:
		Node* _searchName(const std::string& name, Node* elem)
		{
			if (elem->hasParent() && elem->name() == name) {
				return elem;
			}
			// Search in childrens
			for (auto& c : elem->children())
			{
				auto child = this->_searchName(name, c);
				if (child)
				{
					return child;
				}
			}
			return nullptr;
		}
		Node* _searchTag(const std::string& tag, Node* elem)
		{
			if (elem->hasParent() && elem->tag() == tag) {
				return elem;
			}
			// Search in childrens
			for (auto& c : elem->children())
			{
				auto child = this->_searchTag(tag, c);
				if (child)
				{
					return child;
				}
			}
			return nullptr;
		}
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