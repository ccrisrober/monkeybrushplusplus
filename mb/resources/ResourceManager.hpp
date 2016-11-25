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

#ifndef __MB_RESOURCE_MANAGER__
#define __MB_RESOURCE_MANAGER__

#include <functional>
#include <unordered_map>
#include "../utils/any.hpp"

/**
MB::ResourceManager manager;
bool loaded = manager.isAssetLoaded("matcap"); // MB_TEXTURE_ASSETS + std::string("/matcap.jpg"));
std::cout << "MAPCAP LOADED: " << loaded << std::endl;
manager.asyncLoadRequested("matcap");
manager.asyncLoadCompleted("matcap", options); // TODO: Y USAR ANY??
loaded = manager.isAssetLoaded("matcap"); // MB_TEXTURE_ASSETS + std::string("/matcap.jpg"));
std::cout << "MAPCAP LOADED: " << loaded << std::endl;

MB::TexOptions ass = manager.retrieveAsset("matcap").cast<MB::TexOptions>();
 */

namespace MB
{
	class ResourceManager
	{
		class MapEntry
		{
		protected:
            any _asset;
            unsigned int _refCount;
        public:
            /**
             * MapEntry constructor
             */
            MapEntry()
            {
                this->_asset = nullptr;
                this->_refCount = 1;
            }
            /**
             * Return asset name
             * @return {any} [description]
             */
			any getAsset() const
            {
                return this->_asset;
            }
            /**
             * Set asset name
             * @param {any} name New asset name
             */
            void setAsset(any resource)
            {
                this->_asset = resource;
            }
            /**
             * Return asset counter
             * @return {number} Number of uses of this asset
             */
            unsigned int count() const
            {
                return this->_refCount;
            }
            /**
             * Increment asset counter.
             */
            void incCount()
            {
                this->_refCount++;
            }
            /**
             * Decrement asset counter.
             */
            void decCount()
            {
                this->_refCount--;
            }
        };
	protected:
		/**
         * Number of resources per load.
         * @type {number}
         */
        unsigned int _numOutstandingLoads = 0;
        /**
         * All resources finished loading callback.
         * @type {Function}
         */
        std::function<void()> _loadCompleteCallback = nullptr;
        /**
         * [MapEntry description]
         * @type {[key: string]: MapEntry;}
         */
        std::unordered_map<std::string, MapEntry*> _resourceMap;

	public:
        /**
         * Create an asynchronous request to load a resource.
         * @param {string} resName Resource name.
         */
        void asyncLoadRequested(const std::string& resName)
        {
            _resourceMap[resName] = new MapEntry();
            ++_numOutstandingLoads;
        };
        /**
         * Ends resource load with failed.
         * @param {string} resName Resource name.
         */
        void asyncLoadFailed(const std::string& resName)
        {
            std::cout << "ERROR loading " << resName << std::endl;
            --_numOutstandingLoads;
            _checkForAllLoadCompleted();
        }
        /**
         * Calling this function when the resource is loaded correctly.
         * @param {string} resName     Resource name.
         * @param {any} loadedAsset Resource object.
         */
        void asyncLoadCompleted(const std::string& resName, any loadedAsset)
        {
            if (!isAssetLoaded(resName))
            {
                throw "ASSET NOT LOADED";
            }
            _resourceMap[resName]->setAsset(loadedAsset);
            --_numOutstandingLoads;
            _checkForAllLoadCompleted();
        }
        /**
         * Check if all resources are loaded.
         */
        void _checkForAllLoadCompleted()
        {
            if ((_numOutstandingLoads == 0) && (_loadCompleteCallback != nullptr))
            {
                std::function<void()> funToCall = _loadCompleteCallback;
                _loadCompleteCallback = nullptr;
                funToCall();
            }
        };
        /**
         * Set callback function that called when all assets
         *     have finished loading.
         * @param {Function}
         */
        void setLoadCompleteCallback(std::function<void()> fn)
        {
            _loadCompleteCallback = fn;
            _checkForAllLoadCompleted();
        }
        /**
         * Return asset from alias/name
         * @param  {string} resName [description]
         * @return {any}
         */
		any retrieveAsset(const std::string& resName)
        {
			any r = nullptr;
            if (_resourceMap.find(resName) != _resourceMap.end())
            {
                r = _resourceMap[resName]->getAsset();
            }
            else
            {
                throw "ASSET NOT IN MAP";
            }
            return r;
        }
        /**
         * Check whether the resource has already been loaded.
         * @param  {string} resName: Resource name
         * @return {boolean}: True if resource exist
         */
        bool isAssetLoaded(const std::string& resName)
        {
        	return _resourceMap.find(resName) != _resourceMap.end();
        }
        /**
         * @param {string}
         */
        void incAssetRefCount (const std::string& resName)
        {
            _resourceMap[resName]->incCount();
        }
        /**
         * Unload a existing resource.
         * @param {string}
         */
        unsigned int unloadAsset (const std::string& resName)
        {
            unsigned int c = 0;
            if (_resourceMap.find(resName) != _resourceMap.end())
            {
                _resourceMap[resName]->decCount();
                c = _resourceMap[resName]->count();
                if (c == 0)
                {
                    delete _resourceMap[resName];
                    _resourceMap.erase(resName);
                }
            }
            return c;
        }
	};
}

#endif /* __MB_RESOURCE_MANAGER__ */