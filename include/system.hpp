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
#include "entitymanager.hpp"

namespace photon {

	/// \brief Provides a base on which to construct systems.
	///
	/// \tparam The Class of EntityManager supported by this system.
	///
	/// Systems perform logic on entities and their components. Photon's
	/// implementation of systems is currently barebones and WIP. Ssytems target
	/// an entity manager via a pointer and use that pointer to access its data.
	template <typename EM>
	class System {
	protected:

		/// \brief The entity manager associated with this system.
		EM* _target;

		/// \brief Indices of vectors to be checked for availability
		/// \remarks Its use is not required or enforced by any code.
		/// \warning This feature is in flux and is likely to change drastically
		/// as Photon develops.
		std::vector<int> _actingIndices;

	public:

		/// \brief Constructs a system object.
		/// \param target Pointer to the desired target entity manager
		System(EM* target);

		/// \brief Virtual space to write system logic in.
		/// \warning This is an abstract function.
		virtual void run() = 0;

		/// \brief Adds a component's index to the acting indices.
		/// \tparam C The component to be added
		template <class C> void targetComponent();

		/// \brief Removes a component's index from the acting indices.
		/// \tparam C The component to be removed
		template <class C> void untargetComponent();

		/// \return The system's target entity manager.
		EM* target();
	};

}

#include "template_system.ipp"
#include "nontemplate_system.ipp"
