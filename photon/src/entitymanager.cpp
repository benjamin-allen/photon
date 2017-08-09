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
	
	/// Derived entity managers should have this constructor in their
	/// initialization list.
	///
	/// \remark This handles the registration of IDComponent, which is the only
	/// component that EntityManagerBase assumes to exist in its system.
	EntityManagerBase::EntityManagerBase() {
		_entityCount = 0;
		_indexCount = PHOTON_INITIAL_ALLOCATION;

		registerComponent<IDComponent>();
	}

	/// Derived entity managers should call destroy on components registered
	/// within their constructor.
	///
	/// \warning This is a virtual destructor and will be invoked by derived
	/// classes.
	///
	/// \remark This handles the destruction of IDComponent.
	EntityManagerBase::~EntityManagerBase() { 
		destroy<IDComponent>();
	}

	/// If a few things line up right, this function can add an entity in O(1)
	/// time. If not, performance becomes O(n), and the worst-case performance
	/// is O(n) plus the time required to expand every managed component.
	unsigned int EntityManagerBase::addEntity() {
		unsigned int IDIndex = _componentRegistry.getIndex<IDComponent>();
		vector<IDComponent>* idVec = any_cast<vector<IDComponent>*>(componentCollection[IDIndex]);

		// Expand if we know there's no room left
		if(_entityCount == _indexCount) {
			expand();
			_indexCount += PHOTON_EXPANSION_COUNT;
			idVec->at(_entityCount++).activate(); // post increment is correct
			return _entityCount;
		}

		// Try to add an entity at the next logical index
		if(!idVec->at(_entityCount).isActive()) {
			idVec->at(_entityCount).activate();
			return _entityCount++; // post increment is correct here since the index of the new entity is desired
		}

		// Failing both of those things, get a deactivated entity and add it
		unsigned int entity = _deactivatedEntities.back();
		_deactivatedEntities.pop_back();
		idVec->at(entity).activate();
		++_entityCount;
		return entity;
	}

	/// \warning This function is buggy and shouldn't be used yet. It was not a
	/// part of the design goals for 0.1.0 and was hastily added to test an
	/// idea. Use this with extreme caution: it has undefined behaviour at
	/// high values of count and will indiscriminately overwrite other 
	/// components.
	void EntityManagerBase::addEntities(unsigned int count) {
		unsigned int IDIndex = _componentRegistry.getIndex<IDComponent>();
		vector<IDComponent>* idVec = any_cast<vector<IDComponent>*>(componentCollection[IDIndex]);

		// This is not guaranteed to execute, and should not if the number of entities to add
		// is less than the space already available
		while((int)_indexCount - (int)count < (int)_entityCount) {
			expand();
			_indexCount += PHOTON_EXPANSION_COUNT;
		}
		
		// Fill in missing entities first
		while(_deactivatedEntities.size() > 0 && count > 0) {
			unsigned int entity = _deactivatedEntities.back();
			_deactivatedEntities.pop_back();
			idVec->at(entity).activate();
			++_entityCount;
			--count;
		}

		// Now start at _entityCount and continue to fill
		while(count > 0) {
			idVec->at(_entityCount).activate();
			++_entityCount;
			--count;
		}
	}

	/// \warning This function does not touch the non-IDComponent data of an
	/// entity. It doesn't even deactivate the components.
	void EntityManagerBase::removeEntity(unsigned int entity) {
		unsigned int cIndex = _componentRegistry.getIndex<IDComponent>();
		vector<IDComponent>* v = any_cast<vector<IDComponent>*>(componentCollection[cIndex]);
		v->at(entity).deactivate();
		_deactivatedEntities.push_back(entity); // Add the removed entity for use later
		--_entityCount;
	}

	unsigned int EntityManagerBase::getEntityCount() {
		return _entityCount;
	}

	/// \remark This handles the expansion of IDComponent
	/// \remark Derived classes should call this function, but are also free to
	///         call grow<IDComponent>() directly
	/// \see grow<class C>()
	void EntityManagerBase::expand() {
		grow<IDComponent>();
	}
}