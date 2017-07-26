#include "entitymanager.hpp"

EntityManager::EntityManager() {
	EntityManager(false);
}

EntityManager::EntityManager(bool forceUniques) {
	_entityCount = 0;
	_forceUniqueIdentifiers = forceUniques;
	_indexCount = PHOTON_INITIAL_ALLOCATION;
	
	RegisterComponent<IDComponent>();
}
