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

	/// Throws an exception if the class parameter is not a derivative of
	/// Component.
	template <typename EM>
	template <class C>
	void System<EM>::targetComponent() {
		if(!std::is_base_of<Component, C>::value) {
			throw std::invalid_argument("Class is not a component");
		}
		C object;
		int index = _target->getComponentVectorIndex(object.idString());

		_actingIndices.push_back(index);
		std::sort(_actingIndices.begin(), _actingIndices.end()); // Is this sort needed?
	}

	/// Throws an exception if the class parameter is not a derivative of
	/// Component.
	template <typename EM>
	template <class C>
	void System<EM>::untargetComponent() {
		if(!std::is_base_of<Component, C>::value) {
			throw std::invalid_argument("Class is not a component");
		}
		C object;
		int index = _target->getComponentVectorIndex(object.idString());

		for(int i = 0; i < _actingIndices.size(); ++i) {
			if(_actingIndices[i] == index) {
				_actingIndices.erase(_actingIndices.begin() + i);
				return;
			}
		}

		throw std::invalid_argument("Component does not exist as a target");
	}

}
