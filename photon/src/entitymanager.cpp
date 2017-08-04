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

		RegisterComponent<IDComponent>();
	}

	EntityManagerBase::~EntityManagerBase() { 
		Destroy<IDComponent>();
	}

	unsigned int EntityManagerBase::AddEntity() {
		unsigned int IDIndex = _componentRegistry.GetIndex<IDComponent>();
		unsigned int entity;
		vector<IDComponent>* idVec= any_cast<vector<IDComponent>*>(componentCollection[IDIndex]);
		if(_entityCount < idVec->size()) {
			if(!idVec->at(_entityCount).IsActive()) {
				idVec->at(_entityCount).Activate();
				return _entityCount++;
			}
		}
		for(entity = 0; entity < _indexCount; ++entity) {
			if(!idVec->at(entity).IsActive()) {
				++_entityCount;
				idVec->at(entity).Activate();
				return entity;
			}
		}

		Expand();
		_indexCount += PHOTON_EXPANSION_COUNT;
		++_entityCount;
		idVec->at(entity).Activate();
		return entity;
	}

	void EntityManagerBase::AddEntities(unsigned int count) {
		unsigned int IDIndex = _componentRegistry.GetIndex<IDComponent>();
		unsigned int entity;
		vector<IDComponent>* idVec = any_cast<vector<IDComponent>*>(componentCollection[IDIndex]);
		if(count < idVec->size()) {
			for(entity = 0; entity < count; ++entity) {
				idVec->at(entity).Activate();
				idVec->at(entity).id = std::to_string(entity);
			}
		}
	}

	void EntityManagerBase::RemoveEntity(unsigned int entity) {
		unsigned int cIndex = _componentRegistry.GetIndex<IDComponent>();
		vector<IDComponent>* v = any_cast<vector<IDComponent>*>(componentCollection[cIndex]);
		v->at(entity).Deactivate();
		--_entityCount;
	}

	unsigned int EntityManagerBase::GetEntityCount() {
		return _entityCount;
	}

	void EntityManagerBase::Expand() {
		Grow<IDComponent>();
	}
}