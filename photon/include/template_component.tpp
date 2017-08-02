#pragma once

namespace photon {

	template <class C>
	void ComponentRegistry::Register() {
		if(!std::is_base_of<Component, C>::value) {
			throw std::invalid_argument("Class is not a component");
		}

		unsigned int preRC = _registryCount;
		C component;

		if(std::find(_registry.begin(), _registry.end(), component.IDString()) != _registry.end()) {
			throw std::logic_error("A Component has already been registered under the " + component.IDString() + " identifier");
		}
		_registry.push_back(component.IDString());
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

		C component;
		auto iterator = std::find(_registry.begin(), _registry.end(), component.IDString());
		if(iterator == _registry.end()) {
			throw std::invalid_argument("Could not find component");
		}
		else {
			return std::distance(_registry.begin(), iterator);
		}
	}

}