#include "component.hpp"

using std::string;
using std::unique_ptr;

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

unique_ptr<Component> Component::NOST() {
	return nullptr;
}

unique_ptr<Component> IDComponent::NOST() {
	unique_ptr<IDComponent> p(new IDComponent);
	return p;
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
