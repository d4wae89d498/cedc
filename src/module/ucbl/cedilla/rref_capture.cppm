export module ucbl.cedilla:rref_capture;

import :common;

export namespace cedilla
{
	template<typename T>
	struct RrefCapture
	{
		T* ptr;
		RrefCapture(T&& x) : ptr(&x) {}
		operator T&& () const { return std::move(*ptr); } // restitute rvalue ref

	};
}
