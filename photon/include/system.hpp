#pragma once
#include "entitymanager.hpp"

namespace photon {

	class System {
	protected:
		EntityManagerBase* _target;
		std::vector<int> _actingIndices;
	public:
		System(EntityManagerBase*);
		virtual void Run();
		template <class C> void TargetComponent();
		template <class C> void UntargetComponent();
		EntityManagerBase* Target();
	};

}

#include "template_system.tpp"
