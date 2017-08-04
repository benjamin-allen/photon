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

	template <class C>
	void EntityManagerBase::RegisterComponent() {
		if(!std::is_base_of<Component, C>::value) {
			throw std::invalid_argument("Class is not a component");
		}
		_componentRegistry.Register<C>();

		std::vector<C>* vector = new std::vector<C>;
		vector->resize(_indexCount);
		for(unsigned int i = 0; i < _indexCount; ++i) {
			C c;
			vector->at(i) = c;
		}

		std::any obj;
		obj.emplace<std::vector<C>*>(vector);
		componentCollection.push_back(obj);
	}

	template <class C>
	void EntityManagerBase::SetComponentActiveState(unsigned int entity, bool newState) {
		if(!std::is_base_of<Component, C>::value) {
			throw std::invalid_argument("Class is not a component");
		}
		unsigned int cIndex = _componentRegistry.GetIndex<C>();
		if(newState == true) {
			std::any_cast<vector<C>*>(componentCollection[cIndex])->at(entity).Activate();
		}
		else {
			std::any_cast<vector<C>*>(componentCollection[cIndex])->at(entity).Deactivate();
		}
	}

	template <class C>
	unsigned int EntityManagerBase::GetComponentVectorIndex() {
		if(!std::is_base_of<Component, C>::value) {
			throw std::invalid_argument("Class is not a component");
		}
		return _componentRegistry.GetIndex<C>();
	}

	template <class C>
	void EntityManagerBase::Grow() {
		if(!std::is_base_of<Component, C>::value) {
			throw std::invalid_argument("Class is not a component");
		}
		unsigned int cIndex = _componentRegistry.GetIndex<C>();
		std::vector<C>* cVec = std::any_cast<std::vector<C>*>(componentCollection[cIndex]);
		cVec->resize(cVec->size() + PHOTON_EXPANSION_COUNT);
	}

	template <class C>
	void EntityManagerBase::Destroy() {
		if(!std::is_base_of<Component, C>::value) {
			throw std::invalid_argument("Class is not a component");
		}
		unsigned int cIndex = _componentRegistry.GetIndex<C>();
		std::vector<C>* cVec = std::any_cast<std::vector<C>*>(componentCollection[cIndex]);
		delete cVec;
		componentCollection[cIndex].reset();
	}

}