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

#ifndef __MB_EVENT_DISPATCHER__
#define __MB_EVENT_DISPATCHER__

#include <mb/api.h>

#include <unordered_map>
#include <vector>
#include "../utils/any.hpp"

namespace mb
{
    class Event
    {
    public:
        std::string type;
        any target;
    };

    class EventDispatcher
    {
    public:
        MB_API
        void addEventListener(const std::string& type, EventDispatcher* ev)
        {
            if(std::find(_callbacks[type].begin(), _callbacks[type].end(), ev) == _callbacks[type].end())
                _callbacks[type].push_back(ev);
        }
        MB_API
        void removeEventListener(const std::string& type, EventDispatcher* ev)
        {
            if(hasEvent(type, ev))
                remove(_callbacks[type].begin(), _callbacks[type].end(), ev);
        }
        MB_API
        void dispatchEvent(const Event& ev)
        {
            if(_callbacks.count(ev.type) == 0)
                return;

            for(auto cb: _callbacks[ev.type])
                cb->handler(*this, ev);
        }
        MB_API
        bool hasEvent(const std::string& type, EventDispatcher* ev)
        {
            if(_callbacks.count(type) == 0)
                return false;

            return std::find(_callbacks[type].begin(), _callbacks[type].end(), ev) != _callbacks[type].end();
        }

        /*void addEventListener(std::string eventType, cb: MBX.EventListener) {
            if (!this._callbacks) {
                this._callbacks = {};
            }
            if (!this._callbacks.hasOwnProperty(eventType)) {
                this._callbacks[eventType] = [cb];
                return;
            }
            // Check exists
            if (this._callbacks[eventType].indexOf(cb) !== -1) {
                this._callbacks[eventType].push(cb);
            }
        }
        void removeEventListener(std::string eventType, cb: MBX.EventListener) {
            if (!this._callbacks) return;
            if (!this._callbacks.hasOwnProperty(eventType)) {
                return;
            }
            let index = this._callbacks[eventType].indexOf(cb);
            if (index !== -1) {
                this._callbacks[eventType].splice(index, 1);
            }
        }
        void dispatchEvent(ev: MBX.Event) {
            if (!this._callbacks) return;
            if (!this._callbacks.hasOwnProperty(ev.type)) {
                return;
            }
            for (let i in this._callbacks[ev.type]) {
                this._callbacks[ev.type][i](ev);
            }
        }
        void hasEvent(std::string eventType, cb: MBX.EventListener): boolean {
            if (!this._callbacks) return false;
            if (this._callbacks.hasOwnProperty(eventType)
                && this._callbacks[eventType].indexOf(cb) !== -1) {
                return true;
            }
            return false;
        }*/
    protected:
        std::function<void(EventDispatcher&, const Event&)> handler = [](EventDispatcher&, const Event&){};
        std::unordered_map<std::string, std::vector<EventDispatcher*> > _callbacks;
    };
}

#endif /* __MB_EVENT_DISPATCHER__ */
