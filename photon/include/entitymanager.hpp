#pragma once

#include "component.hpp"
#include <memory>
#include <any>

#define PHOTON_INITIAL_ALLOCATION 1000
#define PHOTON_EXPANSION_COUNT PHOTON_INITIAL_ALLOCATION / 2

namespace photon {

	class EntityManager {
	private:
		unsigned int _entityCount;
		unsigned int _indexCount;
		ComponentRegistry _componentRegistry;

		void Expand();
	public:
		EntityManager();
		~EntityManager();
		template <class C> void RegisterComponent();
		template <class C> void SetComponentActiveState(unsigned int, bool);
		template <class C> unsigned int GetComponentVectorIndex();
		unsigned int AddEntity();
		unsigned int GetEntityCount();
		void RemoveEntity(unsigned int);

		std::vector<std::any> componentCollection;
	};

}

#include "template_entitymanager.tpp"
