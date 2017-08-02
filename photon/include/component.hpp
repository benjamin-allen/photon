#pragma once

#include <string>
#include <vector>

namespace photon {

	struct Component {
		Component(std::string);
		std::string IDString();
		void Activate();
		void Deactivate();
		bool IsActive();
	protected:
		std::string _identifierString;
		bool _activityStatus = false;
	};


	struct IDComponent : Component {
		IDComponent();
		std::string id;
	};


	class ComponentRegistry {
	private:
		std::vector<std::string> _registry;
		unsigned int _registryCount = 0;
	public:
		template <class C> void Register();
		template <class C> unsigned int GetIndex();
	};

}

#include "template_component.tpp"
