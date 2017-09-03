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

#include "component.hpp"
#include <any>
#include <memory>
#include <type_traits>

#define PHOTON_INITIAL_ALLOCATION 1000
#define PHOTON_EXPANSION_FACTOR 2

namespace photon {

	/// \brief The base class from which custom entity managers are defined.
	///
	/// \tparam ... The list of components for the entity manager to use
	///
	/// \c EntityManagerBase is responsible for many things, the most
	/// important of which is the \c componentCollection , a vector of pointers
	/// to vectors of components. This part of the API is the most volatile and
	/// where most of the effort in optimization is put.
	template <typename... Components>
	class EntityManagerBase {
	private:
	
		/// \brief Adds a component to the collection, given a variadic template
		/// list
		template <typename C, typename... Cs> void registerComponent();
		
		template <typename... Cs> typename std::enable_if<sizeof...(Cs) == 0>::type registerComponent();
		
		/// \brief Deletes a component from the collection givin a variadic template
		/// list
		template <typename C, typename... Cs> void destroyComponent();
		
		template <typename... Cs> typename std::enable_if<sizeof...(Cs) == 0>::type destroyComponent();
		
		/// \brief Expands the component data in the collection
		template <typename C, typename... Cs> void growComponent();
		
		template <typename... Cs> typename std::enable_if<sizeof...(Cs) == 0>::type growComponent();

		/// \brief The number of entities currently active in the world.
		/// \private
		unsigned int _entityCount;

		/// \brief The number of safely-accessible indices.
		/// \private
		unsigned int _indexCount;

		/// \brief Stores indices of deleted components.
		/// \private
		std::vector<unsigned int> _deactivatedEntities;

		/// \brief The entity manager's internal component registry.
		/// \see ComponentRegistry
		ComponentRegistry _componentRegistry;

	public:

		/// \brief Base constructor for EntityManagerBase
		EntityManagerBase();

		/// \brief Virtual destructor for EntityManagerBase.
		virtual ~EntityManagerBase();

		/// \brief Adds a component to be managed by an entity manager.
		/// \tparam C The component to be managed
		//template <class C> void registerComponent();

		/// \brief Modifies a managed component's current state on an entity.
		/// \tparam C The component to be modified
		/// \param entity The index of the entity owning the component
		/// \param state The new state of the component
		template <class C> void setComponentActiveState(unsigned int entity, bool state);

		/// \brief Searches the component registry for the specified component.
		/// \tparam C The component to be searched for
		/// \return The index of the pointer to the vector in the
		/// \c componentCollection
		template <class C> unsigned int getComponentVectorIndex();

        /// \brief Returns a reference to the component vector
        /// \tparam C The class of the vector component to be returned
        /// \return A shared pointer object to the vector reference
		template <class C> std::shared_ptr<std::vector<C>> getVectorReference();

		/// \brief Adds an entity to the entity manager.
		/// \return The index of the new entity
		unsigned int addEntity();

		/// \brief Adds multiple entities to the entity manager.
		/// \param count The number of entities to add
		void addEntities(unsigned int count);

		/// \brief Returns the number of entities tracked by the entity manager.
		/// \return \c _entityCount
		unsigned int getEntityCount();

		/// \brief Deactivates an entity.
		/// \param entity The entity to deactivate
		void removeEntity(unsigned int entity);

		/// \brief A collection of pointers to various vectors of components.
		///
		/// The component collection is made up of \c std::any objects which
		/// point to heap-allocated vectors. These pointers can be accessed by
		/// using \c std::any_cast() and can then be treated as usual.
		///
		/// \warning This data structure may fundamentally change as Photon
		/// develops. Watch for any changes while the project isn't at 1.0.0.
		std::vector<std::any> componentCollection;
	};

}

#include "template_entitymanager.ipp"
#include "nontemplate_entitymanager.ipp"
