module ucbl.cedilla;

import :common;
import :ast_node;
import :state;

namespace cedilla
{
	template <typename T>
	fn  ClassRegistry<T>::register_class(const string& key, FactoryFunction func) -> void
	{
		registry[key] = func;
	}

	template <typename T>
	fn ClassRegistry<T>::create_instance(const string& key, const string& serialized_str) const -> unique_ptr<T>
	{
		auto it = registry.find(key);
		if (it != registry.end())
			return it->second(serialized_str);
		return nullptr;
	}

	template <typename T>
	ClassRegistry<T>::ClassRegistry()
	{
	}

	template class ClassRegistry<AstNode>;
	template class ClassRegistry<State>;
}
