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

#include <string>
#include <vector>

namespace photon {

	/// \brief Base class from which components are derived.
	///
	/// Components are data structures which contain data, do not perform
	/// logic, and only contain a few methods to return information about a 
	/// particular object.
	struct Component {

		/// \brief Constructs a component with the given identifier string.
		/// \see IDComponent
		Component(std::string);

		/// \brief Returns the identifier string of the component.
		/// \return The identifier string
		std::string idString();

		/// \brief Activates the component.
		/// \see deactivate()
		void activate();

		/// \brief Deactivates the component.
		/// \see activate()
		void deactivate();

		/// \brief Returns true if the component is active.
		/// \return The active status
		bool isActive();

	protected:

		/// \brief The string used to identify this component.
		std::string _identifierString;

		/// \brief Represents if the component's data should be considered or
		///        not.
		bool _activityStatus = false;
	};


	/// \brief A component which stores the id of an entity. It also controls
	///        the active state of the entity.
	/// \see Component
	struct IDComponent : Component {

		/// \brief Constructs a IDComponent object.
		IDComponent();

		/// \brief The id of an entity. Does not have to be unique.
		std::string id;
	};


	/// \brief Maps components to indices via their identifier strings.
	///
	/// The component registry is used in entity managers to look up indices
	/// needed to access component data. In its current state there's not much
	/// reason to use one as a standalone registry.
	///
	/// \see Component
	/// \see EntityManagerBase
	class ComponentRegistry {
	private:

		/// \brief Indexes the strings
		/// \private
		std::vector<std::string> _registry;

		/// \brief The number of registered components
		/// \private
		unsigned int _registryCount = 0;

	public:

		/// \brief Adds a component to the registry
		/// \tparam C The component to be added
		template <class C> void registerComponent();

		/// \brief Retrieves the index of a component in the registry
		/// \tparam C The component to be searched for
		/// \returns The index of the component
		template <class C> unsigned int getIndex();
	};

}

#include "template_component.ipp"
