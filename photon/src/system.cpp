#include "system.hpp"

namespace photon {

	System::System(EntityManagerBase* target) {
		_target = target;
		if(!_target) {
			throw std::invalid_argument("Unsuitable target EntityManager");
		}
	}

	EntityManagerBase* System::Target() {
		return _target;
	}

	void System::Run() { }
}