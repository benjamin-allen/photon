#pragma once

namespace photon {

	/// Throws an exception if target is null.
	template <typename EM>
	System<EM>::System(EM* target) {
		_target = target;
		if(!_target) {
			throw std::invalid_argument("Unsuitable target EntityManager");
		}
	}

	template <typename EM>
	EM* System<EM>::target() {
		return _target;
	}
}