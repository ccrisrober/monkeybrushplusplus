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

#ifndef __MB_UTILS__
#define __MB_UTILS__

#include <mb/api.h>

#include <string>
#include <functional>
#include <thread>
#include <future>
#include <sstream>
#include <cctype>

namespace mb
{
	namespace utils
	{
		/*MB_API
		bool findFiles(const std::string& extension, const std::string&path,
			std::vector<std::string>& results)
		{
			bool found = false;
			//for (boost::filesystem::directory_iterator it(path); 
			//it != boost::filesystem::directory_iterator(); ++it)
			//{
			//	if (_stricmp(it->path().extension().string().c_str(), extension.c_str()) == 0)
			//	{
			//		results.push_back(it->path().string());
			//		found = true;
			//	}
			//}
			return(found);
		}
		MB_API
		bool findFiles(const std::string& extension,
			const std::vector<std::string>& paths,
			std::vector<std::string> & results)
		{
			for (std::vector<std::string>::const_iterator it = paths.begin(); 
				it != paths.end(); ++it)
			{
				findFiles(extension, *it, results);
			}
			return(results.empty());
		}
		*/
		/*MB_API
		bool findFilesRecursive(const std::string& extension,
			const std::string& path, std::vector<std::string> & results)
		{
			bool found = false;
			//boost::filesystem::path searchPath(path);
			//for (boost::filesystem::recursive_directory_iterator dirIt(searchPath); 
			//dirIt != boost::filesystem::recursive_directory_iterator(); ++dirIt)
			//{
			//	if (_stricmp(dirIt->path().extension().string().c_str(), extension.c_str()) == 0)
			//	{
			//		results.push_back(dirIt->path().string());
			//		found = true;
			//	}
			//}
			return(found);
		}

		MB_API
			bool findFilesRecursive(const std::string& extension,
				const std::vector<std::string>& paths,
				std::vector<std::string> & results)
		{
			for (std::vector<std::string>::const_iterator it = paths.begin(); 
				it != paths.end(); ++it)
			{
				findFilesRecursive(extension, *it, results);
			}
			return(results.empty());
		}*/
		/*MB_API
		std::vector<std::string> splitStringIntoTokensOnDelimiter(const std::string& s,
			char delimiter, bool removeWhiteSpace = false)
		{
			std::vector<std::string> tokens;
			std::istringstream iss(s);
			std::string token;
			//
			while (std::getline(iss, token, delimiter)) {
				if (token.size() > 0 && token[0] != delimiter) {
					if (removeWhiteSpace) {
						token = eraseStringFromString(token, " ");
					}
					tokens.push_back(token);
				}
			}

			return tokens;
		}
		MB_API
		std::string eraseStringFromString(std::string bigString,
			const std::string& smallString, bool onlyFirstOccurance = false)
		{
			if (bigString.find(smallString) == std::string::npos) {
				return bigString;
			}
			do {
				bigString.erase(bigString.find(smallString), smallString.size());
			} while (!onlyFirstOccurance && bigString.find(smallString) != std::string::npos);

			return bigString;
		}
		MB_API
		std::string stringToLower(std::string s)
		{
			std::string result;
			for (char c : s) {
				result.push_back(std::tolower(c));
			}
			return result;
		}
		MB_API
		std::string stringToUpper(std::string s)
		{
			std::string result;
			for (char c : s) {
				result.push_back(std::toupper(c));
			}
			return result;
		}*/


		template<typename T>
		struct deleter : std::unary_function<const T*, void>
		{
			void operator() (const T *ptr) const
			{
				delete ptr;
			}
		};
		std::string generateUUID();
		template <class F, class... Args>
		void setInterval(std::atomic_bool& cancelToken, size_t interval, F&& f, Args&&... args)
		{
			cancelToken.store(true);
			auto cb = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
			std::async(std::launch::async, [=, &cancelToken]()mutable {
				while (cancelToken.load()) {
					cb();
					std::this_thread::sleep_for(std::chrono::milliseconds(interval));
				}
			});
		}
		/*std::atomic_bool b;
		setInterval(b, 1000, printf, "hi there\n");
		cancelToken.store(false);*/
	}
}

#endif /* __MB_UTILS __ */
