#include "system.hpp"

System::System(EntityManager* target) {
	_target = target;
	if(!_target) {
		throw std::invalid_argument("Unsuitable target EntityManager");
	}
}

void System::Run() {
	unsigned int attempts = 0;
	unsigned int targetAttempts = _target->GetEntityCount();

	for(int entity = 0; attempts < targetAttempts; ++entity) {
		bool hasAllComponents = true;
		for each (int index in _actingIndices) {
			if(!_target->components[index][entity]->IsActive()) {
				hasAllComponents = false;
				break;
			}
		}
		if(!hasAllComponents) {
			continue;
		}
		
		Act(entity);
	}
}

void System::Act(unsigned int entity) { }