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

void Component::IsActive() {
	return _isActive;
}

IDComponent::IDComponent() : Component("idcomponent") { }
