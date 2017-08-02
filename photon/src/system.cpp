#include "system.hpp"

namespace photon {

	System::System(EntityManager* target) {
		_target = target;
		if(!_target) {
			throw std::invalid_argument("Unsuitable target EntityManager");
		}
	}

	EntityManager* System::Target() {
		return _target;
	}

	void System::Run() { }
}