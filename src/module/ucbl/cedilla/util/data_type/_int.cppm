export module ucbl.cedilla:util.data_type._int;

import :common;

export namespace ucbl::cedilla {
	struct Int {
		// Constructors
		Int() : value(0) {}
		Int(s64 val) : value(val) {}

		// Implicit conversion to string using format
		operator string() const {
			return format("{}", value);
		}

		// Implicit conversion to s64
		operator s64() const {
			return value;
		}

		s64 value;
	};
}

