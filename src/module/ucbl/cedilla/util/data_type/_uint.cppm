export module ucbl.cedilla:_uint;

import :common;

export namespace cedilla {
	struct UInt {
		// Constructors
		UInt() : value(0) {}
		UInt(u64 val) : value(val) {}

		// Implicit conversion to string using format
		operator string() const {
			return format("{}", value);
		}

		// Implicit conversion to u64
		operator u64() const {
			return value;
		}

		u64 value;
	};
}

