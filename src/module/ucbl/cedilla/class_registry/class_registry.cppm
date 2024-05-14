export module ucbl.cedilla:class_registry;

import :common;

export namespace cedilla
{

	template<typename T>
	struct ClassRegistry
	{
		unordered_map<string, void*> registry;

		void register_class(const string& key, void* func) {
			registry[key] = func;
		}

		template<typename... Args>
		unique_ptr<T> make(const string& key, Args&&... args) {
			auto it = registry.find(key);
			if (it != registry.end()) {
				return ((unique_ptr<T>(*)(Args...)) it->second)  (std::forward<Args>(args)...);
			} else {
				throw runtime_error("Class not registered: " + key);
			}
		}
	};
};
