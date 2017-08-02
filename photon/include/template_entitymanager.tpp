#pragma once

namespace photon {

	template <class C>
	void EntityManager::RegisterComponent() {
		if(!std::is_base_of<Component, C>::value) {
			throw std::invalid_argument("Class is not a component");
		}
		_componentRegistry.Register<C>();

		std::vector<C>* vector = new std::vector<C>;
		vector->resize(_indexCount);
		for(unsigned int i = 0; i < _indexCount; ++i) {
			C c;
			vector->at(i) = c;
		}

		std::any obj;
		obj.emplace(vector);
		componentCollection.push_back(obj);
	}

	template <class C>
	void EntityManager::SetComponentActiveState(unsigned int entity, bool newState) {
		if(!std::is_base_of<Component, C>::value) {
			throw std::invalid_argument("Class is not a component");
		}
		unsigned int cIndex = _componentRegistry.GetIndex<C>();
		if(newState == true) {
			std::any_cast<vector<C>*>(componentCollection[cIndex])->at(entity).Activate();
		}
		else {
			std::any_cast<vector<C>*>(componentCollection[cIndex])->at(entity).Deactivate();
		}
	}

	template <class C>
	unsigned int EntityManager::GetComponentVectorIndex() {
		if(!std::is_base_of<Component, C>::value) {
			throw std::invalid_argument("Class is not a component");
		}
		return _componentRegistry.GetIndex<C>();
	}
}