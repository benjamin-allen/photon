#pragma once
#include "entitymanager.hpp"

class System {
protected:
	EntityManager* _target;
	std::vector<int> _actingIndices;
	virtual void Act(unsigned int);
public:
	System(EntityManager*);
	virtual void Run();
	template <class C> void TargetComponent();
	template <class C> void UntargetComponent();
	EntityManager* Target();
};

#include "template_system.tpp"
