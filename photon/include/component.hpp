#pragma once

#include <string>
#include <vector>

class Component {
protected:
	std::string _name;
	bool _isActive = false;
	virtual void f();
public:
	Component(std::string name);
	std::string Name();
	void Activate();
	void Deactivate();
	void IsActive();
};


class IDComponent : protected Component {
protected:
	void f();
public:
	IDComponent();
	std::string id;
};


class ComponentRegistry {
private:
	std::vector<std::string> _registry;
	unsigned int _registryCount = 0;
public:
	template <class C> void Register();
	template <class C> unsigned int GetIndex();
};

template <class C>
void ComponentRegistry::Register() {
	if(!std::is_base_of<Component, C>::value) {
		throw std::invalid_argument("Class is not a component");
	}

	unsigned int preRC = _registryCount;
	C object;

	if(std::find(_registry.begin(), _registry.end(), object.Name()) != _registry.end()) {
		throw std::logic_error("A Component has already been registered under the " + object._name + " identifier");
	}
	_registry.push_back(object._name);
	if(_registry.size() <= preRC) {
		throw std::runtime_error("Component registration failed");
	}
}

template <class C> 
unsigned int ComponentRegistry::GetIndex() {
	if(!std::is_base_of<Component, C>::value) {
		throw std::invalid_argument("Class is not a component");
	}

	C object;
	auto iterator = std::find(_registry.begin(), _registry.end(), object.Name);
	if(iterator == _registry.end()) {
		throw std::invalid_argument("Could not find component");
	}
	else {
		return std::distance(_registry.begin(), iterator);
	}
}
