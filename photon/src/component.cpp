#include "component.hpp"

using std::string;

namespace photon {

	Component::Component(string name) {
		_identifierString = name;
	}

	string Component::IDString() {
		return _identifierString;
	}

	void Component::Activate() {
		_activityStatus = true;
	}

	void Component::Deactivate() {
		_activityStatus = false;
	}

	bool Component::IsActive() {
		return _activityStatus;
	}

	IDComponent::IDComponent() : Component("idcomponent") { }

}
