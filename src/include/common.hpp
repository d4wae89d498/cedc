#define REGISTER_CLASS(TYPE, CLASS) \
    namespace\
	{\
        struct Registrator_ ## TYPE ## CLASS\
		{\
            Registrator_ ## TYPE ## CLASS()\
			{\
                TYPE ## Registry ::get().register_class(#CLASS, [](const string& str) -> std::unique_ptr<TYPE>\
				{\
					return CLASS  :: unserialize(str);\
				});\
            }\
        };\
        static Registrator_ ## TYPE ## CLASS registrator_ ## TYPE ## CLASS;\
    }

#define fn auto

#define u64 unsigned long
#define u32 unsigned
#define u16 unsigned short
#define u8 	unsigned char

#define s64 long
#define s32 int
#define s16 short
#define s8 	char


static_assert(sizeof(u64) == sizeof(unsigned long), "u64 size check failed");
static_assert(sizeof(u32) == sizeof(unsigned), "u32 size check failed");
static_assert(sizeof(u16) == sizeof(unsigned short), "u16 size check failed");
static_assert(sizeof(u8) == sizeof(unsigned char), "u8 size check failed");

static_assert(sizeof(s64) == sizeof(long), "s64 size check failed");
static_assert(sizeof(s32) == sizeof(int), "s32 size check failed");
static_assert(sizeof(s16) == sizeof(short), "s16 size check failed");
static_assert(sizeof(s8) == sizeof(char), "s8 size check failed");
