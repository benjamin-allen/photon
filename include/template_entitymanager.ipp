// Photon: A fast, simple, open-source ECS library for C++
//
// MIT License
//
// Copyright(c) 2017 Benjamin Allen
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

namespace photon {

	template <typename... Components>
	template <typename... Cs>
	typename std::enable_if<sizeof...(Cs) == 0>::type EntityManagerBase<Components...>::registerComponent() { }

	/// Adds a component to the component registry and then expands the
	/// component collection with a pointer to a new vector. That vector is
	/// expanded to match the size of the rest of the collection and filled
	/// with \c C objects. It is then emplaced into the collection.
	///
	/// Throws an exception if the class parameter is not a derivative of
	/// Component.
	template <typename... Components>
	template <typename C, typename... Cs>
	void EntityManagerBase<Components...>::registerComponent() {
		if (!std::is_base_of<Component, C>::value) {
			throw std::invalid_argument("Class is not a component");
		}
		_componentRegistry.registerComponent<C>();

		// See if this block can be simplified with one of vector's constructors
		std::shared_ptr<std::vector<C>> vector(new std::vector<C>);
		vector->resize(_indexCount);
		for (unsigned int i = 0; i < _indexCount; ++i) {
			C c;
			vector->at(i) = c;
		}

		std::any obj;
		obj.emplace<std::shared_ptr<std::vector<C>>>(vector);
		componentCollection.push_back(obj);
		registerComponent<Cs...>();
	}

	template <typename... Components>
	template <typename... Cs>
	typename std::enable_if<sizeof...(Cs) == 0>::type EntityManagerBase<Components...>::destroyComponent() { }

    /// Deletes the component data fully and resets the std::any object
	template <typename... Components>
	template <typename C, typename... Cs>
	void EntityManagerBase<Components...>::destroyComponent() {
		if (!std::is_base_of<Component, C>::value) {
			throw std::invalid_argument("Class is not a component");
		}
		unsigned int cIndex = _componentRegistry.getIndex<C>();
		componentCollection[cIndex].reset(); // toss the object
		destroyComponent<Cs...>();
	}

	template <typename... Components>
	template <typename... Cs>
	typename std::enable_if<sizeof...(Cs) == 0>::type EntityManagerBase<Components...>::growComponent() { }

    /// Doubles the size of the data vector
	template <typename... Components>
	template <typename C, typename... Cs>
	void EntityManagerBase<Components...>::growComponent() {
		if (!std::is_base_of<Component, C>::value) {
			throw std::invalid_argument("Class is not a component");
		}
		unsigned int cIndex = _componentRegistry.getIndex<C>();
		std::shared_ptr<std::vector<C>> cVec = std::any_cast<std::shared_ptr<std::vector<C>>>(componentCollection[cIndex]);
		cVec->resize(cVec->size() * PHOTON_EXPANSION_FACTOR); // Should have gone with this the first time
		growComponent<Cs...>();
	}


	/// Throws an exception if the class parameter is not a derivative of
	/// Component.
	///
	/// \warning Users are discouraged from using this function to activate
	/// or deactivate an entity's IDComponent, since it will not touch the
	/// private variables associated with those functions.
	template <typename... Components>
	template <class C>
	void EntityManagerBase<Components...>::setComponentActiveState(unsigned int entity, bool newState) {
		if(!std::is_base_of<Component, C>::value) {
			throw std::invalid_argument("Class is not a component");
		}
		unsigned int cIndex = _componentRegistry.getIndex<C>();

		// Maybe make this touch _entityCount if necessary?
		if(newState == true) {
			std::any_cast<std::shared_ptr<std::vector<C>>>(componentCollection[cIndex])->at(entity).activate();
		}
		else {
			std::any_cast<std::shared_ptr<std::vector<C>>>(componentCollection[cIndex])->at(entity).deactivate();
		}
	}

	/// Throws an exception if the class parameter is not a derivative of
	/// Component. Also makes calls to another function that can throw
	/// other exceptions if the class parameter is not registered.
	template <typename... Components>
	template <class C>
	unsigned int EntityManagerBase<Components...>::getComponentVectorIndex() {
		if(!std::is_base_of<Component, C>::value) {
			throw std::invalid_argument("Class is not a component");
		}
		return _componentRegistry.getIndex<C>();
	}

	template <typename... Components>
	template <class C>
	std::shared_ptr<std::vector<C>> EntityManagerBase<Components...>::getVectorReference() {
		return std::any_cast<std::shared_ptr<std::vector<C>>>(componentCollection[getComponentVectorIndex<C>()]);
	}
}
