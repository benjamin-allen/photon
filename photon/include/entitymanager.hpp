#pragma once

#include "component.hpp"
#include <memory>

#define PHOTON_INITIAL_ALLOCATION 1000
#define PHOTON_EXPANSION_COUNT PHOTON_INITIAL_ALLOCATION / 2

class EntityManager {
private:
	unsigned int _entityCount;
	unsigned int _indexCount;
	bool _forceUniqueIdentifiers;
	ComponentRegistry _componentRegistry;

	void Expand();
public:
	EntityManager();
	EntityManager(bool);
	template <class C> void RegisterComponent();
	unsigned int AddEntity();
	void RemoveEntity(unsigned int);
	void RemoveEntity(std::string);
	unsigned int GetEntityCount();
	void SetComponentActiveState(unsigned int, std::string, bool);
	int GetComponentVectorIndex(std::string);
	
	std::vector<std::vector<std::unique_ptr<Component>>> components;
};

#include "template_entitymanager.tpp"
