export module ucbl.cedilla:clonable;

import :common;

export namespace cedilla
{
	template <typename T>
	struct Clonable
	{
		virtual fn	clone() const -> unique_ptr<T> = 0;
	};

	template <typename T>
	struct MaybeClonable
	{
 		virtual fn clone() const -> unique_ptr<T>
		{
			throw new runtime_error("calling clone without implementation");
    	}

		fn is_clonable() const -> bool
		{
        	return !is_same<decltype(&T::clone), decltype(&T::clone)>::value;
    	}
	};
}
