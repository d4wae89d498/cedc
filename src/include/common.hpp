#define REGISTER_DESERIALIZABLE_WITH_FUNC(TYPE, CLASS, F) \
    namespace { \
        struct Registrator_##CLASS { \
            Registrator_##CLASS() { \
                TYPE ## Registry::get().register_class(#CLASS, F); \
            } \
        }; \
        static Registrator_##CLASS reg_##CLASS; \
    }

#define REGISTER_DESERIALIZABLE(TYPE, CLASS) REGISTER_DESERIALIZABLE_WITH_FUNC(TYPE, CLASS, CLASS::deserialize)

#define fn auto

#define u64 unsigned long
#define u32 unsigned
#define u16 unsigned short
#define u8 	unsigned char

#define s64 long
#define s32 int
#define s16 short
#define s8 	char

static_assert(sizeof(u64) == 8, "u64 size check failed"); // 8 bytes = 64 bits
static_assert(sizeof(u32) == 4, "u32 size check failed"); // 4 bytes = 32 bits
static_assert(sizeof(u16) == 2, "u16 size check failed"); // 2 bytes = 16 bits
static_assert(sizeof(u8) == 1, "u8 size check failed");  // 1 byte = 8 bits

static_assert(sizeof(s64) == 8, "s64 size check failed"); // 8 bytes = 64 bits
static_assert(sizeof(s32) == 4, "s32 size check failed"); // 4 bytes = 32 bits
static_assert(sizeof(s16) == 2, "s16 size check failed"); // 2 bytes = 16 bits
static_assert(sizeof(s8) == 1, "s8 size check failed");  // 1 byte = 8 bits
