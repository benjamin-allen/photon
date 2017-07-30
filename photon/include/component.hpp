#pragma once

#include <string>
#include <vector>
#include <algorithm>

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
	bool IsActive();
};


class IDComponent : public Component {
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
	unsigned int GetIndex(std::string);
};

#include "template_component.tpp"
