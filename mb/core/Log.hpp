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
#include <sstream>
#include <fstream>
#include <memory>
#include <chrono>
#include "../utils/StringUtils.hpp"

namespace mb
{
	class Log
	{
	private:
		Log(void) {}
		virtual ~Log() {}
	public:
		enum LogLevel {
			LOG_LEVEL_NONE = -1,		// no output
			LOG_LEVEL_ERROR = 2,		// only errors are output
			LOG_LEVEL_WARNING = 3,		// errors and warnings are output
			LOG_LEVEL_INFO = 4,			// errors, warnings, and informative messages
			LOG_LEVEL_DEBUG = 5,		// errors, warnings, informative messages and debug
			LOG_LEVEL_ALL = 99			// all messages are output
		};
		static void setLevel(int level) { _level = level; }
		static int getLevel(void) { return _level; }
	private:
		static int _level;
	public:
		template<typename ... Args>
		static void error(std::string const &msg, Args && ...args)
		{
			print(LogLevel::LOG_LEVEL_ERROR, "E", msg, std::forward< Args >(args)...);
		}
		template<typename ... Args>
		static void warning(std::string const &msg, Args && ...args)
		{
			print(LogLevel::LOG_LEVEL_WARNING, "E", msg, std::forward< Args >(args)...);
		}
		template<typename ... Args>
		static void info(std::string const &msg, Args && ...args)
		{
			print(LogLevel::LOG_LEVEL_INFO, "E", msg, std::forward< Args >(args)...);
		}
		template< typename ... Args >
		static void print(int level, std::string const &levelStr, std::string const &TAG, Args &&... args)
		{
			if (getLevel() >= level && _outputHandler != nullptr)
			{
				auto tp = std::chrono::system_clock::now();
				auto s = std::chrono::duration_cast< std::chrono::microseconds >(tp.time_since_epoch());
				auto t = (time_t)(s.count());

				auto str = StringUtils::toString(t, " ",
					levelStr, "/", TAG, " - ",
					std::forward< Args >(args)...);

				_outputHandler->printLine(str);
			}
		}

		public:
			class OutputHandler
			{
				public:
					virtual ~OutputHandler(void) { }
					virtual void printLine(std::string const &line) = 0;
			};
			class ConsoleOutputHandler : public OutputHandler
			{
			public:
				ConsoleOutputHandler(void) { }
				virtual ~ConsoleOutputHandler(void) { }

				virtual void printLine(std::string const &line) override
				{
					std::cout << line << "\n";
				}
			};
			class FileOutputHandler : public OutputHandler
			{
			public:
				FileOutputHandler(std::string const &path) : _out(path, std::ios::out) { }
				virtual ~FileOutputHandler(void) { }

				virtual void printLine(std::string const &line) override
				{
					_out << line << "\n";
				}
			private:
				std::ofstream _out;
			};
			class NullOutputHandler : public OutputHandler
			{
			public:
				NullOutputHandler(void) { }
				virtual ~NullOutputHandler(void) { }

				virtual void printLine(std::string const &) override
				{
				}
			};
			template< class T, typename ... Args >
			static void setOutputHandler(Args &&... args)
			{
				_outputHandler = std::move(std::unique_ptr< T >(new T(std::forward< Args >(args)...)));
			}
	private:
		static std::unique_ptr< OutputHandler > _outputHandler;
	};
}

#endif  /* __MB_LOG__ */
