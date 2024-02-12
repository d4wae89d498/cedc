#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <memory>

using namespace std;

template <typename T>
class ClassRegistry {
public:
    using FactoryFunction = function<unique_ptr<T>()>;

    static ClassRegistry& get() {
        static ClassRegistry instance;
        return instance;
    }

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

private:
    map<string, FactoryFunction> registry;
    ClassRegistry() {}
};

#define REGISTER_CLASS(TYPE, CLASS) \
    namespace { \
        struct Registrator_ ## TYPE ## CLASS { \
            Registrator_ ## TYPE ## CLASS() { \
                TYPE ## Registry ::get().registerClass(#CLASS, []() -> std::unique_ptr<CLASS> { return make_unique<CLASS>();  }); \
            } \
        }; \
        static Registrator_ ## TYPE ## CLASS registrator_ ## TYPE ## CLASS; \
    }
