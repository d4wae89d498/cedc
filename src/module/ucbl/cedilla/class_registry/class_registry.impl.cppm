export module ucbl.cedilla:class_registry.impl;
export import :class_registry;

import :common;

namespace cedilla
{
	template <typename T>
	fn  ClassRegistry<T>::register_class(const string& key, FactoryFunction func) -> void
	{
		registry[key] = func;
	}

	template <typename T>
	fn ClassRegistry<T>::create_instance(const string& key) const -> unique_ptr<T>
	{
		auto it = registry.find(key);
		if (it != registry.end())
		{
			return it->second();
		}
		return nullptr;
	}

	template <typename T>
	ClassRegistry<T>::ClassRegistry()
	{
	}
};

