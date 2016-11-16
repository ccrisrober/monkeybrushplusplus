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

#ifndef __MB_EVENT_DISPATCHER__
#define __MB_EVENT_DISPATCHER__

#include <unordered_map>
#include "../utils/any.hpp"

namespace MB
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
        void addEventListener(std::string)
        {

        }
        void removeEventListener(std::string)
        {

        }
        void dispatchEvent(const Event& ev)
        {
            if(_callbacks.count(ev.type) == 0)
            {
                return;
            }
            /*for(const auto& l: _callbacks[ev.type])
            {
                //l->eventHandler(*this, ev);
            }*/
        }
        bool hasEvent(std::string)
        {
            return false;
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
        std::unordered_map<std::string, std::string> _callbacks;
    };
}

#endif /* __MB_EVENT_DISPATCHER__ */
