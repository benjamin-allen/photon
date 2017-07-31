#include "entitymanager.hpp"
#include <typeinfo>

using std::string;
using std::unique_ptr;

EntityManager::EntityManager() : EntityManager(false) { }

EntityManager::EntityManager(bool forceUniques) {
	_entityCount = 0;
	_forceUniqueIdentifiers = forceUniques;
	_indexCount = PHOTON_INITIAL_ALLOCATION;
	
	RegisterComponent<IDComponent>();
}

unsigned int EntityManager::AddEntity() {
	unsigned int cIndex = _componentRegistry.GetIndex<IDComponent>();
	unsigned int entity;
	if(_entityCount < components[cIndex].size()) {
		if(!components[cIndex][_entityCount]->IsActive()) {
			components[cIndex][_entityCount]->Activate();
			return _entityCount++;
		}
	}
	for(entity = 0; entity < _indexCount; ++entity) {
		if(components[cIndex][entity]->IsActive() == false) {
			++_entityCount;
			components[cIndex][entity]->Activate();
			return entity;
		}
	}

	Expand();
	++_entityCount;
	components[cIndex][entity]->Activate();
	return entity;
}

void EntityManager::RemoveEntity(unsigned int entity) {
	components[_componentRegistry.GetIndex<IDComponent>()][entity]->Deactivate();
	--_entityCount;
}

void EntityManager::RemoveEntity(string id) {
	unsigned int cIndex = _componentRegistry.GetIndex<IDComponent>();
	for(unsigned int entity = 0; entity < _indexCount; ++entity) {
		unique_ptr<IDComponent> ptr(dynamic_cast<IDComponent*>(components[cIndex][entity].release()));
		if(ptr->id == id) {
			components[cIndex][entity]->Deactivate();
		}
	}
}

unsigned int EntityManager::GetEntityCount() {
	return _entityCount;
}

void EntityManager::SetComponentActiveState(unsigned int entity, string componentID, bool newState) {
	unsigned int cIndex = _componentRegistry.GetIndex(componentID);
	if(newState == true) {
		components[cIndex][entity]->Activate();
	}
	else {
		components[cIndex][entity]->Deactivate();
	}
}

int EntityManager::GetComponentVectorIndex(string component) {
	return _componentRegistry.GetIndex(component);
}

void EntityManager::Expand() {
	for(unsigned int i = 0; i < components.size(); ++i) {
		components[i].resize(_indexCount + PHOTON_EXPANSION_COUNT);
		for(unsigned int j = _indexCount; j < components[i].size(); ++j) {
			components[i][j] = components[i][0]->NOST();
		}
	}

	_indexCount += PHOTON_EXPANSION_COUNT;
}
