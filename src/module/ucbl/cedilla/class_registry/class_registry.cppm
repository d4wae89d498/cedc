export module ucbl.cedilla:class_registry;

import :common;

export namespace cedilla
{
	template<typename T>
	struct ClassRegistry
	{
		unordered_map<string, unique_ptr<T>(*)(const string &)> registry;

		void register_class(const string& key, unique_ptr<T>(*func)(const string &))
		{
			registry[key] = func;
		}

		fn deserialize(const string& key, const string &v) -> unique_ptr<T>
		{
			auto it = registry.find(key);
			if (it != registry.end())
			{
				return it->second(v);
			}
			else
			{
				throw runtime_error("Class not registered: " + key);
			}
		}
	};
};
