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

	EntityManagerBase::~EntityManagerBase() { }

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

	void EntityManagerBase::Expand() { }

}