export module ucbl.cedilla:class_registry;

import :common;

export namespace cedilla
{
	template <typename T>
	struct ClassRegistry
	{
		using FactoryFunction = function<unique_ptr<T>()>;

		unordered_map<string, FactoryFunction> registry;

		void register_class(const string& key, FactoryFunction func)
		{
			registry[key] = func;
		}

		unique_ptr<T> create_instance(const string& key) const
		{
			auto it = registry.find(key);
			if (it != registry.end())
			{
				return it->second();
			}
			return nullptr;
		}

		ClassRegistry()
		{
		}
	};
};

