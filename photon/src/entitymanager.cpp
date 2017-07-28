#include "entitymanager.hpp"

using std::string;

EntityManager::EntityManager() : EntityManager(false) { }

EntityManager::EntityManager(bool forceUniques) {
	_entityCount = 0;
	_forceUniqueIdentifiers = forceUniques;
	_indexCount = PHOTON_INITIAL_ALLOCATION;
	
	RegisterComponent<IDComponent>();
}

unsigned int EntityManager::AddEntity() {
	for(unsigned int entity = 0; entity < _indexCount; ++entity) {
		if(!components[componentRegistry.GetIndex("idcomponent")][entity].IsActive()) {
			++_entityCount;
			components[componentRegistry.GetIndex("idcomponent")][entity].Activate();
			return entity;
		}
	}

	Expand();
}

void EntityManager::RemoveEntity(unsigned int entity) {
	components[componentRegistry.GetIndex("idcomponent")][entity].Deactivate();
	--_entityCount;
}

void EntityManager::RemoveEntity(string id) {
	for(unsigned int entity = 0; entity < _indexCount; ++entity) {
		if(components[componentRegistry.GetIndex("idcomponent")][entity].id == id) {
			components[componentRegistry.GetIndex("idcomponent")][entity].Deactivate();
		}
	}
}

unsigned int EntityManager::GetEntityCount() {
	return _entityCount;
}

void EntityManager::SetComponentActiveState(unsigned int entity, string componentID, bool newState) {
	unsigned int cIndex = _componentRegistry.GetIndex(componentID);
	if(newState == true) {
		components[cIndex][entity].Activate();
	}
	else {
		components[cIndex][entity].Deactivate();
	}
}

int EntityManager::GetComponentVectorIndex(string component) {
	return _componentRegistry.GetIndex(component);
}
