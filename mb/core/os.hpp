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

#ifndef __MB_OS__
#define __MB_OS__

#if defined(WIN32)
	#include <direct.h>
	//#include <windows.h>
#endif

#include <mb/api.h>

namespace MB
{
	class os
	{
	public:
		MB_API
		static void mkdir(const std::string& path)
		{
			#if defined(WIN32)
				_mkdir(path.c_str());
			#else
                mkdir(path.c_str(), S_IRWXU);
			#endif
		}
		MB_API
		static std::string path(const std::string& path)
		{
			std::string aux = path;
			#if defined(WIN32)
				strReplaceAll(aux, "/", "\\");
			#else
				strReplaceAll(aux, "\\", "/");
			#endif
			return aux;
		}
		MB_API
		static bool isdir(const std::string& p)
		{
			/*std::string _path = path(p);
			#if defined(WIN32)
                WIN32_FILE_ATTRIBUTE_DATA info;
                GetFileAttributesExA(_path.c_str(), GetFileExInfoStandard, &info);
                return (info.dwFileAttributes != INVALID_FILE_ATTRIBUTES &&
                        (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY));
			#else
                struct stat info;
                stat(_path.c_str(), &info);
                return S_ISDIR(info.st_mode);
			#endif*/
                
            return false;
		}
		MB_API
		static char path_delimiter()
		{
			char delimeter;
			#if defined(WIN32)
				delimeter = '\\';
			#else
				delimeter = '/';
			#endif
			return delimeter;
		}
	private:
		static void strReplaceAll(std::string& source, std::string const& find, std::string const& replace)
		{
		    for(std::string::size_type i = 0; (i = source.find(find, i)) != std::string::npos;)
		    {
		        source.replace(i, find.length(), replace);
		        i += replace.length();
		    }
		}
	};
}

#endif /* __MB_OS__ */