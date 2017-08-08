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

	/// Appends the identifier string of the component to the registry vector.
	/// Throws an exception if:
	/// \li The class parameter is not a derivative of Component
	/// \li The identifier string of the derivative component is not already
	///     registered
	/// \li The \c push_back operation fails
	template <class C>
	void ComponentRegistry::registerComponent() {
		if(!std::is_base_of<Component, C>::value) {
			throw std::invalid_argument("Class is not a component");
		}

		unsigned int preRC = _registryCount;
		C component;

		if(std::find(_registry.begin(), _registry.end(), component.idString()) != _registry.end()) {
			throw std::logic_error("A Component has already been registered under the " + component.idString() + " identifier");
		}
		_registry.push_back(component.idString());
		_registryCount = _registry.size();
		if(_registryCount <= preRC) {
			throw std::runtime_error("Component registration failed");
		}
	}

	/// Uses std::find to search the vector for an identifier string and returns
	/// its index.
	/// Throws an exception if:
	/// \li The class parameter is not a derivative of Component
	/// \li The identifier string could not be found within the registry
	template <class C>
	unsigned int ComponentRegistry::getIndex() {
		if(!std::is_base_of<Component, C>::value) {
			throw std::invalid_argument("Class is not a component");
		}

		C component;
		auto iterator = std::find(_registry.begin(), _registry.end(), component.idString());
		if(iterator == _registry.end()) {
			throw std::invalid_argument("Could not find component");
		}
		else {
			return std::distance(_registry.begin(), iterator);
		}
	}

}