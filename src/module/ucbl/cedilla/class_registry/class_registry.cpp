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
		print("create_instance with: {}\n", key);
		auto it = registry.find(key);
		if (it != registry.end())
		{
			print("found\n");
			return it->second(serialized_str);
		}
		print("not found!\n");
		throw runtime_error("Error: ClassRegistry::create_instance: key " + key + " not found.");
		return nullptr;
	}

	template <typename T>
	ClassRegistry<T>::ClassRegistry()
	{
	}

	template class ClassRegistry<AstNode>;
	template class ClassRegistry<State>;
}
