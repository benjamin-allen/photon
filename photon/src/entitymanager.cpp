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
		unsigned int entity; // Used in a loop below. It's out here in case expansion is necessary.
		vector<IDComponent>* idVec= any_cast<vector<IDComponent>*>(componentCollection[IDIndex]);

		// First attempts to add an entity at _entityCount
		if(_entityCount < idVec->size()) {
			if(!idVec->at(_entityCount).isActive()) {
				idVec->at(_entityCount).activate();
				return _entityCount++; // post increment is correct here since the index of the new entity is desired
			}
		}

		// If that fails, fallback to scanning for a deactivated entity
		for(entity = 0; entity < _indexCount; ++entity) {
			if(!idVec->at(entity).isActive()) {
				++_entityCount; // pre increment is fine here since this isn't getting returned
				idVec->at(entity).activate();
				return entity;
			}
		}

		// If we don't have any free space, time to expand the collection and add an entity at the first new spot
		// Maybe we can jump straight to this check if _entityCount and _indexCount converge.
		expand();
		_indexCount += PHOTON_EXPANSION_COUNT;
		++_entityCount;
		idVec->at(entity).activate();
		return entity;
	}

	/// \warning This function is buggy and shouldn't be used yet. It was not a
	/// part of the design goals for 0.1.0 and was hastily added to test an
	/// idea. Use this with extreme caution: it has undefined behaviour at
	/// high values of count and will indiscriminately overwrite other 
	/// components.
	void EntityManagerBase::addEntities(unsigned int count) {
		unsigned int IDIndex = _componentRegistry.getIndex<IDComponent>();
		unsigned int entity;
		vector<IDComponent>* idVec = any_cast<vector<IDComponent>*>(componentCollection[IDIndex]);
		// So very bad
		if(count < idVec->size()) {
			for(entity = 0; entity < count; ++entity) {
				idVec->at(entity).activate();
				idVec->at(entity).id = std::to_string(entity);
			}
		}
	}

	/// \warning This function does not touch the non-IDComponent data of an
	/// entity. It doesn't even deactivate the components.
	void EntityManagerBase::removeEntity(unsigned int entity) {
		unsigned int cIndex = _componentRegistry.getIndex<IDComponent>();
		vector<IDComponent>* v = any_cast<vector<IDComponent>*>(componentCollection[cIndex]);
		v->at(entity).deactivate();
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