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

#ifndef __MB_LOG__
#define __MB_LOG__

#include <mb/api.h>

#include <iostream>
#include <ctime>

namespace mb
{
	class LOG
	{
	public:
		enum TLogLevel {
			ALL,		// all messages are output
			INFO,		// errors, warnings, and informative messages
			WARNING,	// errors and warnings are output
			ERROR,		// only errors are output
			NONE		// no output
		};
    MB_API
		LOG();
    MB_API
		LOG(TLogLevel type);
    MB_API
		virtual ~LOG();
    MB_API
		LOG& operator<<(const std::string &msg);
		//template<class T>
		//LOG& operator<<(const T &msg);
		static TLogLevel level;
		static bool headers;
		static bool date;
	private:
		bool opened = false;
		TLogLevel msglevel = ALL;
		std::string getLogTime();
		std::string getLabel(TLogLevel type);
	};
}

#endif  /* __MB_LOG__ */
