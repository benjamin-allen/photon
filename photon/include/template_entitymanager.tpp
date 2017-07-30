#pragma once

template <class C>
void EntityManager::RegisterComponent() {
	if(!std::is_base_of<Component, C>::value) {
		throw std::invalid_argument("Class is not a component");
	}
	_componentRegistry.Register<C>();

	std::vector<std::unique_ptr<Component>> vector;
	vector.reserve(_indexCount);
	for(unsigned int i = 0; i < _indexCount; ++i) {
		std::unique_ptr<C> ptr(new C());
		vector.push_back(std::move(ptr));
	}

	components.push_back(std::move(vector));
}