#include "system.hpp"

using std::unique_ptr;

System::System(EntityManager* target) {
	unique_ptr<EntityManager> ptr(target);
	_target = ptr;
	if(!_target) {
		throw std::invalid_argument("Unsuitable target EntityManager");
	}
}

