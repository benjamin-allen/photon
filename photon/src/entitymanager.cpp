// Photon: A fast, simple, open-source ECS library for C++
// 
// MIT License
// 
// Copyright(c) 2017 Benjamin Allen
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "entitymanager.hpp"
#include <typeinfo>

using std::string;
using std::vector;
using std::any;
using std::any_cast;


namespace photon {
	
	EntityManagerBase::EntityManagerBase() {
		_entityCount = 0;
		_indexCount = PHOTON_INITIAL_ALLOCATION;

		registerComponent<IDComponent>();
	}

	EntityManagerBase::~EntityManagerBase() { 
		destroy<IDComponent>();
	}

	unsigned int EntityManagerBase::addEntity() {
		unsigned int IDIndex = _componentRegistry.getIndex<IDComponent>();
		unsigned int entity;
		vector<IDComponent>* idVec= any_cast<vector<IDComponent>*>(componentCollection[IDIndex]);
		if(_entityCount < idVec->size()) {
			if(!idVec->at(_entityCount).isActive()) {
				idVec->at(_entityCount).activate();
				return _entityCount++;
			}
		}
		for(entity = 0; entity < _indexCount; ++entity) {
			if(!idVec->at(entity).isActive()) {
				++_entityCount;
				idVec->at(entity).activate();
				return entity;
			}
		}

		expand();
		_indexCount += PHOTON_EXPANSION_COUNT;
		++_entityCount;
		idVec->at(entity).activate();
		return entity;
	}

	void EntityManagerBase::addEntities(unsigned int count) {
		unsigned int IDIndex = _componentRegistry.getIndex<IDComponent>();
		unsigned int entity;
		vector<IDComponent>* idVec = any_cast<vector<IDComponent>*>(componentCollection[IDIndex]);
		if(count < idVec->size()) {
			for(entity = 0; entity < count; ++entity) {
				idVec->at(entity).activate();
				idVec->at(entity).id = std::to_string(entity);
			}
		}
	}

	void EntityManagerBase::removeEntity(unsigned int entity) {
		unsigned int cIndex = _componentRegistry.getIndex<IDComponent>();
		vector<IDComponent>* v = any_cast<vector<IDComponent>*>(componentCollection[cIndex]);
		v->at(entity).deactivate();
		--_entityCount;
	}

	unsigned int EntityManagerBase::getEntityCount() {
		return _entityCount;
	}

	void EntityManagerBase::expand() {
		grow<IDComponent>();
	}
}