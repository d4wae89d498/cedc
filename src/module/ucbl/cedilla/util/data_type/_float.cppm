export module ucbl.cedilla:_float;

import :common;

export namespace cedilla {
	class Float {
		// Constructors
		Float() : value(0.0) {}
		Float(double val) : value(val) {}

		// Implicit conversion to string using format
		operator string() const {
			return format("{}", value);
		}

		// Implicit conversion to double
		operator double() const {
			return value;
		}

		double value;
	};
}

