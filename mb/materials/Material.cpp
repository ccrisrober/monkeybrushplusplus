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

#include "Material.hpp"

namespace MB
{
	Material::Material()
	{
	}
    Material::~Material() {}
    TUniforms& Material::uniforms()
    {
        return this->_uniforms;
    }
    Uniform*& Material::uniform(const std::string& name)
    {
        return this->_uniforms[name];
    }
	void Material::addUniform(const std::string& name, Uniform* u)
	{
		this->_uniforms[name] = u;
	}
	bool Material::hasUniform(const std::string& name)
	{
		return _uniforms.find(name) != _uniforms.end();
	}
	Uniform* Material::operator[](std::string& name)
	{
		return uniform(name);
	}
	void Material::use()
	{
		this->_program.use();
		for (const auto& uniform : _uniforms)
		{
			if (!uniform.second->isDirty())
				continue;
            auto type = uniform.second->type();
			if (type == Float)
			{
				this->_program.sendUniformf(uniform.first, uniform.second->value().cast<float>());
			}
            else if (type == Integer)
            {
                this->_program.sendUniformi(uniform.first, uniform.second->value().cast<int>());
            }
            else if (type == Boolean)
            {
                this->_program.sendUniformb(uniform.first, uniform.second->value().cast<bool>());
            }
			else if (type == Vector2)
            {
                this->_program.sendUniform2v(uniform.first, uniform.second->value().cast<Vect2>()._values.data());
            }
            else if (type == Vector3)
            {
                this->_program.sendUniform3v(uniform.first, uniform.second->value().cast<Vect3>()._values);
            }
            else if (type == Vector4)
            {
                this->_program.sendUniform4v(uniform.first, uniform.second->value().cast<Vect4>()._values.data());
            }
            else if (type == Matrix2)
            {
                this->_program.sendUniform2m(uniform.first, uniform.second->value().cast<Mat2>()._values.data());
            }
            else if (type == Matrix3)
            {
                this->_program.sendUniform3m(uniform.first, uniform.second->value().cast<Mat3>()._values.data());
            }
            else if (type == Matrix4)
            {
				this->_program.sendUniform4m(uniform.first, uniform.second->value().cast<Mat4>()._values.data());
            }
			uniform.second->setDirty(false);
		}
	}
	void Material::unuse()
	{
		this->_program.unuse();
	}
}
