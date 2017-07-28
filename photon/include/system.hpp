#pragma once
#include "entitymanager.hpp"

class System {
private:
	std::unique_ptr<EntityManager> _target;
	std::vector<int> _actingIndices;
protected:
	virtual void Act();
public:
	System(EntityManager*);
	virtual void Run();
	template <class C> void TargetComponent();
	template <class C> void UntargetComponent();
}

template <class C>
void System::TargetComponent() {
	if(!std::is_base_of<Component, C>::value) {
		throw std::invalid_argument("Class is not a component");
	}
	int index = _target->GetComponentVectorIndex(C.Name());

	_actingIndices.push_back(index);
	std::sort(_actingIndices.begin(), _actingIndices.end());
}

template <class C>
void System::UntargetComponent() {
	if(!std::is_base_of<Component, C>::value) {
		throw std::invalid_argument("Class is not a component");
	}
	int index = _target->GetComponentVectorIndex(C.Name());

	for(int i = 0; i < _actingIndices.size(); ++i) {
		if(_actingIndices[i] == index) {
			_actingIndices[i].erase();
			return;
		}
	}

	throw std::invalid_argument("Component does not exist as a target");
}
