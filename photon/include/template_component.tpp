#pragma once

template <class C>
void ComponentRegistry::Register() {
	if(!std::is_base_of<Component, C>::value) {
		throw std::invalid_argument("Class is not a component");
	}

	unsigned int preRC = _registryCount;
	C object;

	if(std::find(_registry.begin(), _registry.end(), object.Name()) != _registry.end()) {
		throw std::logic_error("A Component has already been registered under the " + object.Name() + " identifier");
	}
	_registry.push_back(object.Name());
	_registryCount = _registry.size();
	if(_registryCount <= preRC) {
		throw std::runtime_error("Component registration failed");
	}
}

template <class C> 
unsigned int ComponentRegistry::GetIndex() {
	if(!std::is_base_of<Component, C>::value) {
		throw std::invalid_argument("Class is not a component");
	}

	C object;
	auto iterator = std::find(_registry.begin(), _registry.end(), object.Name());
	if(iterator == _registry.end()) {
		throw std::invalid_argument("Could not find component");
	}
	else {
		return std::distance(_registry.begin(), iterator);
	}
}