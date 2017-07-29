#pragma once

#include "component.hpp"
#include <memory>

#define PHOTON_INITIAL_ALLOCATION 100
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

template <class C>
void EntityManager::RegisterComponent() {
	if(!std::is_base_of<Component, C>::value) {
		throw std::invalid_argument("Class is not a component");
	}
	componentRegistry.Register<C>();

	std::vector<std::unique_ptr<Component>> vector;
	vector.reserve(_indexCount);
	for(unsigned int i = 0; i < _indexCount; ++i) {
		std::unique_ptr<C> ptr(new C());
		vector.push_back(std::move(ptr));
	}

	components.push_back(vector);
}
