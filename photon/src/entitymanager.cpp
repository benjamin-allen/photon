#include "entitymanager.hpp"
#include <typeinfo>

using std::string;
using std::unique_ptr;
using std::vector;
using std::any;
using std::any_cast;


namespace photon {
	EntityManager::EntityManager() {
		_entityCount = 0;
		_indexCount = PHOTON_INITIAL_ALLOCATION;

		RegisterComponent<IDComponent>();
	}

	unsigned int EntityManager::AddEntity() {
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
		++_entityCount;
		idVec->at(entity).Activate();
		return entity;
	}

	void EntityManager::RemoveEntity(unsigned int entity) {
		unsigned int cIndex = _componentRegistry.GetIndex<IDComponent>();
		vector<IDComponent>* v = any_cast<vector<IDComponent>*>(componentCollection[cIndex]);
		v->at(entity).Deactivate();
		--_entityCount;
	}

	unsigned int EntityManager::GetEntityCount() {
		return _entityCount;
	}

	void EntityManager::Expand() {
		for(unsigned int i = 0; i < componentCollection.size(); ++i) {
			auto v = any_cast<vector<void*>*>(componentCollection[i]);
			v->resize(PHOTON_EXPANSION_COUNT);
			for(unsigned int j = _indexCount; j < v->size(); ++j) {
				v->at(j) = v->at(0);
			}
		}

		_indexCount += PHOTON_EXPANSION_COUNT;
	}

}