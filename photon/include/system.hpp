#pragma once
#include "entitymanager.hpp"

namespace photon {

	class System {
	protected:
		EntityManager* _target;
		std::vector<int> _actingIndices;
	public:
		System(EntityManager*);
		virtual void Run();
		template <class C> void TargetComponent();
		template <class C> void UntargetComponent();
		EntityManager* Target();
	};

}

#include "template_system.tpp"
