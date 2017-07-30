#pragma once
#include "entitymanager.hpp"

class System {
private:
	EntityManager* _target;
	std::vector<int> _actingIndices;
protected:
	virtual void Act(unsigned int);
public:
	System(EntityManager*);
	virtual void Run();
	template <class C> void TargetComponent();
	template <class C> void UntargetComponent();
};

#include "template_system.tpp"
