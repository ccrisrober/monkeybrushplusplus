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
// http://stackoverflow.com/questions/1666802/is-there-a-class-macro-in-c
#ifndef __MB_RTTI__
#define __MB_RTTI__

namespace mb
{
	class RTTI {
	protected:
		RTTI( void ) { }

	public:
		virtual ~RTTI( void ) { }
		virtual const char *getClassName( void ) const = 0;
	};

}

/**
    \brief Helper macro to implement RTTI in classes
    \todo This macro does not work well with templates
*/
#define MB_IMPLEMENT_RTTI( X ) \
    public: \
        static constexpr const char *__CLASS_NAME = #X; \
        virtual const char *getClassName( void ) const override { return __CLASS_NAME; }

#endif /* __MB_RTTI__ */
