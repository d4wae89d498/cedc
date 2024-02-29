#define REGISTER_CLASS(TYPE, CLASS) \
    namespace\
	{\
        struct Registrator_ ## TYPE ## CLASS\
		{\
            Registrator_ ## TYPE ## CLASS()\
			{\
                TYPE ## Registry ::get().register_class(#CLASS, [](string str) -> std::unique_ptr<TYPE>\
				{\
					return CLASS  :: unserialize(str);\
				});\
            }\
        };\
        static Registrator_ ## TYPE ## CLASS registrator_ ## TYPE ## CLASS;\
    }

#define fn auto
#define TEST21 42
