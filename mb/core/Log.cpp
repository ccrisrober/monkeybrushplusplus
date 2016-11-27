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

#include "Log.hpp"

namespace mb
{
	LOG::LOG() {}
	LOG::LOG(TLogLevel type)
	{
		msglevel = type;
		if (LOG::headers || LOG::date)
		{
			operator << ("[");

			if (LOG::headers && LOG::date)
			{
				operator << (getLabel(type) + " - " + getLogTime());
			}
			else
			{
				if (LOG::headers)
				{
					operator << (getLabel(type));
				}
				else if (LOG::date)
				{
					operator << (getLogTime());
				}
			}
			operator << ("] ");
		}
	}
	LOG::~LOG()
	{
		if (opened)
		{
			std::cout << std::endl;
		}
		opened = false;
	}
	LOG& LOG::operator<<(const std::string &msg)
	//template<class T>
	//LOG& LOG::operator<<(const T &msg)
	{
		if (msglevel == TLogLevel::NONE)
		{
			opened = false;
		}
		else if (msglevel >= LOG::level)
		{
			std::cout << msg.c_str();
			opened = true;
		}
		return *this;
	}
	std::string LOG::getLogTime()
	{
		time_t t;
		struct tm *tm;
		char datetime[50];

		t = time(nullptr);
		tm = localtime(&t);
		strftime(datetime, 50, "%Y/%m/%d %H:%M:%S", tm);

		return datetime;
	}

	std::string LOG::getLabel(TLogLevel type)
	{
		std::string label;
		switch (type)
		{
		case ALL:
			label = "ALL";
			break;
		case INFO:
			label = "INFO";
			break;
		case WARNING:
			label = "WARNING";
			break;
		case ERROR:
			label = "ERROR";
			break;
		case NONE:
			label = "NONE";
			break;
		}
		return label;
	}
	LOG::TLogLevel LOG::level = TLogLevel::ALL;
	bool LOG::headers = true;
	bool LOG::date = false;
}