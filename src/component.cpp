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

#include "component.hpp"

using std::string;

namespace photon {

	/// This method should be used by derived classes' initialization list
	/// to define derived components whose identifier strings all match. 
	/// Every component is inactive when constructed and must be activated
	/// manually.
	Component::Component(string name) {
		_identifierString = name;
	}

	string Component::idString() {
		return _identifierString;
	}

	void Component::activate() {
		_activityStatus = true;
	}

	void Component::deactivate() {
		_activityStatus = false;
	}

	bool Component::isActive() {
		return _activityStatus;
	}
	
	/// \code IDComponent::IDComponent() : Component("idcomponent") { } \endcode
	IDComponent::IDComponent() : Component("idcomponent") { }

}
