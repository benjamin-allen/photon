#pragma once

namespace photon {

	/// Derived entity managers should have this constructor in their
	/// initialization list.
	///
	/// \remark This handles the registration of IDComponent, which is the only
	/// component that EntityManagerBase assumes to exist in its system.
	template <typename... Components>
	EntityManagerBase<Components...>::EntityManagerBase() {
		_entityCount = 0;
		_indexCount = PHOTON_INITIAL_ALLOCATION;
		IDComponent i;
		registerComponent<IDComponent>();
	}

	/// Derived entity managers should call destroy on components registered
	/// within their constructor.
	///
	/// \warning This is a virtual destructor and will be invoked by derived
	/// classes.
	///
	/// \remark This handles the destruction of IDComponent.
	template<typename... Components>
	EntityManagerBase<Components...>::~EntityManagerBase() {
		destroy<IDComponent>();
	}

	/// Best-case performance is O(1). Worst case is also O(1) but requires that
	/// the collection be expanded.
	template<typename... Components>
	unsigned int EntityManagerBase<Components...>::addEntity() {
		unsigned int IDIndex = _componentRegistry.getIndex<IDComponent>();
		shared_ptr<vector<IDComponent>> idVec = any_cast<shared_ptr<vector<IDComponent>>>(componentCollection[IDIndex]);

		// Expand if we know there's no room left
		if(_entityCount == _indexCount) {
			expand();
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

	/// This is recommended over adding entities one-at-a-time with addEntity().
	template <typename... Components>
	void EntityManagerBase<Components...>::addEntities(unsigned int count) {
		unsigned int IDIndex = _componentRegistry.getIndex<IDComponent>();
		shared_ptr<vector<IDComponent>> idVec = any_cast<shared_ptr<vector<IDComponent>>>(componentCollection[IDIndex]);

		// This is not guaranteed to execute, and should not if the number of entities to add
		// is less than the space already available
		while((int)_indexCount - (int)count < (int)_entityCount) {
			expand();
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

	/// If the entity is already deactivated, nothing happens.
	/// \warning This function does not touch the non-IDComponent data of an
	/// entity. It doesn't even deactivate the components.
	template <typename... Components>
	void EntityManagerBase<Components...>::removeEntity(unsigned int entity) {
		unsigned int cIndex = _componentRegistry.getIndex<IDComponent>();
		shared_ptr<vector<IDComponent>> v = any_cast<shared_ptr<vector<IDComponent>>>(componentCollection[cIndex]);
		// Add a check for whether anything changed
		if(v->at(entity).isActive()) {
			v->at(entity).deactivate();
			_deactivatedEntities.push_back(entity); // Add the removed entity for use later
			--_entityCount;
		}
	}

	template <typename... Components>
	unsigned int EntityManagerBase<Components...>::getEntityCount() {
		return _entityCount;
	}


	/// \remark This handles the expansion of IDComponent
	/// \remark Derived classes should call this function, but are also free to
	///         call grow<IDComponent>() directly
	/// \see grow<class C>()
	template <typename... Components>
	void EntityManagerBase<Components...>::expand() {
		grow<IDComponent>();
	}
}