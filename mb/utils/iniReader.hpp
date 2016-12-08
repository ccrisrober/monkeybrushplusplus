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

#ifndef __MB_INIREADER__
#define	__MB_INIREADER__

#include <mb/api.h>

#include <string>
#include <fstream>
#include <algorithm>

// Code based on https://github.com/bmaynard/iniReader

namespace mb
{
	class ini
	{
	public:
		/*
		parseIniFile("sample.ini");
		cout << "MYSQL Host: " << getOptionToString("mysql_host") << "\n"; //Return string
		cout << "MYSQL User: " << getOptionToString("mysql_user") << "\n"; //Return string
		cout << "MYSQL Pass: " << getOptionToString("mysql_pass") << "\n"; //Return string
		cout << "MYSQL DB: " << getOptionToChar("mysql_db") << "\n"; //Return char
		cout << "MYSQL Socket: " << getOptionToChar("mysql_socket") << "\n"; //Return char
		cout << "MYSQL Port: " << getOptionToInt("mysql_port") << "\n"; //Return int
		cout << "Bad Config Item: " << getOptionToString("bad_config_item") << "\n"; //Should return nothing

		cleanupIniReader();
		*/

		/**
		* Parse a configuration file
		*
		* @param	fileName The name of the file to parse
		* @return	none
		*/
		MB_API
		static void parseIniFile(const std::string& fileName);

		/**
		* If you are finished with the config item, use this function to cleanup the results
		*
		* @return none
		*/
		MB_API
		static void cleanupIniReader();

		/**
		* Return the value of the requested key in with the string type
		*
		* @param	key The option key
		* @return	string The value of the requested key
		*/
		MB_API
		static std::string getOptionToString(const std::string& key);

		/**
		* Return the value of the requested key in with the int type
		*
		* @param	key The option key
		* @return	int The value of the requested key
		* @note	If item is not an integer (or does not exist) then 0 will be returned.
		*/
		MB_API
		static int getOptionToInt(const std::string& key);

		/**
		* Return the value of the requested key in with the char type
		*
		* @param    key The option key
		* @return   char The value of the requested key
		*/
		MB_API
		static const char *getOptionToChar(const std::string& key);

	protected:
		static std::string parseOptionName(const std::string& value);
		static std::string parseOptionValue(const std::string& value);
		static std::string trim(const std::string& s);
		static std::string rtrim(std::string s);
		static std::string ltrim(std::string s);
	};
}

#endif	/* __MB_INIREADER__ */
