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

#include "iniReader.hpp"

using namespace std;

#include <cctype>
#include <functional>

namespace mb
{
	struct ConfigItems {
		std::string key;
		std::string value;
	};
	ConfigItems* iniItem[1024];

	int i = 0;

	void ini::parseIniFile(const std::string& fileName)
	{
		std::string optionValue;
		ifstream infile;
		infile.open(fileName.c_str());

		//Does the file exist?
		if (infile.is_open() != true)
		{
			return;
		}

	    std::string key;

		while (!infile.eof()) // To get you all the lines.
		{
			getline(infile, optionValue); // Saves the line in STRING.

			//Is the option a comment
			if (optionValue.substr(0, 1) == "#")
			{
				continue;
			}

			key = parseOptionName(optionValue);

			if (key.length() > 0)
			{
				iniItem[i] = new ConfigItems;
				iniItem[i]->key = key;
				iniItem[i]->value = parseOptionValue(optionValue);
				i++;
			}
		}

		i--;
		infile.close();
	}

	void ini::cleanupIniReader()
	{
		for (int x = 0; x <= i; x++)
		{
			delete iniItem[x];
		}

		i = 0;
	}

	std::string ini::getOptionToString(const std::string& key)
	{
		//Check to see if anything got parsed?
		if (i == 0)
		{
			return "";
		}

		for (int x = 0; x <= i; x++)
		{
			if (key == iniItem[x]->key)
			{
				return iniItem[x]->value;
			}
		}
		
		return "";
	}

	const char *ini::getOptionToChar(const std::string& key)
	{
		//Check to see if anything got parsed?
		if (i == 0)
		{
			return "";
		}

		for (int x = 0; x <= i; x++)
		{
			if (key == iniItem[x]->key)
			{
				return iniItem[x]->value.c_str();
			}
		}

		return "";
	}

	int ini::getOptionToInt(const std::string& key)
	{
		//Check to see if anything got parsed?
		if (i == 0)
		{
			return 0;
		}

		for (int x = 0; x <= i; x++)
		{
			if (key == iniItem[x]->key)
			{
				return atoi(iniItem[x]->value.c_str());
			}
		}

		return 0;
	}

	std::string ini::parseOptionName(const std::string& value)
	{
		size_t found;

		found = value.find('=');

		if (found > 100)
		{
			return "";
		}

		std::string key = value.substr(0, (found-1));
		key = trim(key);

		return key;
	}

	std::string ini::parseOptionValue(const std::string& value)
	{
		size_t found;

		found = value.find('=');

		if (found > 100)
		{
			return "";
		}

		std::string keyValue = value.substr((found+1));
		keyValue = trim(keyValue);

		return keyValue;
	}

	std::string ini::trim(const std::string& s)
	{
		return ltrim(rtrim(s));
	}

	// trim from start
	std::string ini::ltrim(std::string s) {
	    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	    return s;
	}

	// trim from end
	std::string ini::rtrim(std::string s) {
	    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	    return s;
	}
}