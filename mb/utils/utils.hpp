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

#ifndef __MB_UTILS__
#define __MB_UTILS__

#include <mb/api.h>

#include <string>
#include <functional>
#include <thread>
#include <future>

namespace mb
{
	namespace utils
	{
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