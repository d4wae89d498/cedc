export module ucbl.cedilla:class_registry;

import :common;

export namespace cedilla
{
	template <typename T>
	struct ClassRegistry
	{
		using FactoryFunction = function<unique_ptr<T>()>;

		unordered_map<string, FactoryFunction> registry;

		fn register_class(const string& key, FactoryFunction func) -> void;
		fn create_instance(const string& key) const -> unique_ptr<T>;
		ClassRegistry();
	};
};

