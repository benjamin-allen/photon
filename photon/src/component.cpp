#include "component.hpp"

using std::string;

Component::Component(string name) {
	_name = name;
}

string Component::Name() {
	return _name;
}

void Component::Activate() {
	_isActive = true;
}

void Component::Deactivate() {
	_isActive = false;
}

bool Component::IsActive() {
	return _isActive;
}

IDComponent::IDComponent() : Component("idcomponent") { }

unsigned int ComponentRegistry::GetIndex(string componentID) {
	auto iterator = std::find(_registry.begin(), _registry.end(), componentID);
	if(iterator == _registry.end()) {
		throw std::invalid_argument("Could not find component");
	}
	else {
		return std::distance(_registry.begin(), iterator);
	}
}
