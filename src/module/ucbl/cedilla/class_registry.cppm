export module ucbl.cedilla:class_registry;

import :common;

export namespace cedilla
{
	template <typename T>
	class ClassRegistry {
	public:
		using FactoryFunction = function<unique_ptr<T>()>;

		void registerClass(const string& key, FactoryFunction func) {
			registry[key] = func;
		}

		unique_ptr<T> createInstance(const string& key) const {
			auto it = registry.find(key);
			if (it != registry.end()) {
				return it->second();
			}
			return nullptr;
		}
		ClassRegistry() {}

	private:
		unordered_map<string, FactoryFunction> registry;
	};
};

