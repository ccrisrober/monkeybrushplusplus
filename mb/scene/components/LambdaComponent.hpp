/*
 * Copyright (c) 2017 maldicion069
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
#ifndef __MB__LAMBDA_COMPONENT__
#define __MB__LAMBDA_COMPONENT__

#include <mb/api.h>

#include "Component.hpp"

#include <functional>
#include "../Node.hpp"

namespace mb
{
  class LambdaComponent: public Component
  {
	// TODO: CHANGE NODE* to NodePtr
    //using Callback = std::function< void (Node*, const float& ) >;
  public:
	typedef std::function< void(Node*, const mb::Clock&) > Callback;
  public:
    MB_API
    LambdaComponent( Callback cb );
    MB_API
    virtual ~LambdaComponent( void );
    MB_API
    virtual void update( const mb::Clock& clock ) override;
  private:
    Callback _callback;
  };
}

#endif /* __MB__LAMBDA_COMPONENT__ */
