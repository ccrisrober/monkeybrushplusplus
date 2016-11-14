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

// Code based on https://hbfs.wordpress.com/2010/12/21/c-logging/

#ifndef __MB_LOG__
#define __MB_LOG__

namespace MB {
	typedef enum
	{
		LOG_LEVEL_QUIET,    // no output
		LOG_LEVEL_ERROR,    // only errors are output
		LOG_LEVEL_WARNING,  // errors and warnings are output
		LOG_LEVEL_INFO,     // errors, warnings, and informative messages
		LOG_LEVEL_ALL,      // all messages are output
		LOG_LEVEL_NONE,     // end of enum marker
	} TLogLevel;
	class Log {
	public:
		static void setLogLevel(const TLogLevel level)
		{

		}
		static TLogLevel logLevel()
		{

		}
		static void log(const std::string& message, const TLogLevel level = LOG_LEVEL_DEFAULT)
		{

		}
    	static void setStream(std::ostream& ost)
    	{
    		_ost = ost;
    	}
    	static std::ostream& stream() const
    	{
    		return _ost;
    	}

	protected:
		static TLogLevel _logLevel;
		static std::ostream& _ost;
	};
}

#endif /* __MB_LOG__ */