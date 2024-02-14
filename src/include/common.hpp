#define REGISTER_CLASS(TYPE, CLASS) \
    namespace { \
        struct Registrator_ ## TYPE ## CLASS { \
            Registrator_ ## TYPE ## CLASS() { printf("called!\n");\
                TYPE ## Registry ::get().registerClass(#CLASS, []() -> std::unique_ptr<CLASS> { return make_unique<CLASS>();  }); \
            } \
        }; \
        static Registrator_ ## TYPE ## CLASS registrator_ ## TYPE ## CLASS; \
    }
