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

#define PHOTON_INITIAL_ALLOCATION 1000
#define PHOTON_EXPANSION_COUNT PHOTON_INITIAL_ALLOCATION / 2

namespace photon {

	class EntityManagerBase {
	private:
		unsigned int _entityCount;
		unsigned int _indexCount;
		ComponentRegistry _componentRegistry;
	protected:
		virtual void Expand();
		template <class C> void Grow();
		template <class C> void Destroy();
	public:
		EntityManagerBase();
		virtual ~EntityManagerBase();
		template <class C> void RegisterComponent();
		template <class C> void SetComponentActiveState(unsigned int, bool);
		template <class C> unsigned int GetComponentVectorIndex();
		unsigned int AddEntity();
		void AddEntities(unsigned int);
		unsigned int GetEntityCount();
		void RemoveEntity(unsigned int);

		std::vector<std::any> componentCollection;
	};

}

#include "template_entitymanager.tpp"
