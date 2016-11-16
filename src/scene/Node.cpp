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

#include "Node.hpp"

namespace MB
{
	Node::Node(const std::string& name, const std::string& tag)
	: _name(name)
	, _id(_generateUUID())
	, _parent(nullptr)
	, _tag(tag)
    , _isEnabled(true)
	, _transform(Transform())
	{
	}
	bool Node::isEnabled() const
	{
		return this->_isEnabled;
	}
	bool Node::hasParent() const
	{
		return this->_parent != nullptr;
	}
	Node* Node::parent() const
	{
		return this->_parent;
	}
	void Node::setParent(Node* p)
	{
        // TODO: Check parent in p node (addChild or removeChild in p.parent)
		this->_parent = p;
	}
	void Node::addChild(Node* n)
	{
		if (n == this)
		{
			throw "TODO: ERROR";
		}
		n->setParent(this);
		this->_children.push_back(n);
	}
    void Node::removeChild(Node* /*n*/) {
		// TODO
	}
	void Node::addComponent(Component* c)
	{
		c->setNode(this);
		this->_components.push_back(c);
	}
	void Node::setEnabled(const bool v)
	{
		this->_isEnabled = v;
		for(auto& c: this->_children)
		{
			c->setEnabled(v);
		}
	}
	void Node::removeAll()
	{
        // TODO: Clear Nodes ...
		this->_children.clear( );
	}
	std::vector<Node*> Node::children() const
	{
		return this->_children;
	}
	std::vector<Component*> Node::components() const
	{
		return this->_components;
	}
	Transform& Node::transform()
	{
		return this->_transform;
	}
	void Node::_updateMatrixWorld(bool force)
	{
		if (this->_transform._autoUpdate)
		{
			this->_transform.updateMatrix();
		}
		if (this->_transform._matrixWorldNeedUpdate || force)
		{
			if (!hasParent())
			{
				//this.transform._matrixWorld.copy(this.transform._matrix);
			}
			else
			{
				//this.parent.transform._matrixWorld.mult(this.transform._matrix, this.transform._matrixWorld);
			}

			this->_transform._matrixWorldNeedUpdate = false;
			force = true;
		}

		for (auto& child : _children)
		{
			child->_updateMatrixWorld(force);
		}
	}
	std::string Node::_generateUUID() const
	{
        char GUID[40];
        int t = 0;
        std::string szTemp = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx";
        std::string szHex = "0123456789ABCDEF-";
        int nLen = szTemp.size();

        for (t=0; t<nLen+1; t++)
        {
            int r = rand () % 16;
            char c = ' ';

            switch (szTemp[t])
            {
                case 'x' : { c = szHex [r]; } break;
                case 'y' : { c = szHex [(r & 0x03) | 0x08]; } break;
                case '-' : { c = '-'; } break;
                case '4' : { c = '4'; } break;
            }

            GUID[t] = ( t < nLen ) ? c : 0x00;
        }

        return std::string(GUID);
	}
}
