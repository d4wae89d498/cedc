export module ucbl.cedilla:clonable;

import :common;


/*
TODO :

    // Provide a default implementation for the virtual function.
    virtual void optionalFunction() const {
        std::cout << "Base default implementation of optionalFunction" << std::endl;
    }

    // Function to check if 'optionalFunction' is overridden by the derived class
    bool isOptionalFunctionOverridden() const {
        return !std::is_same<decltype(&Base::optionalFunction), decltype(&Base::optionalFunction)>::value;
    }

*/
export namespace cedilla
{
	template <typename T>
	struct Clonable
	{
		fn	clone() -> unique_ptr<T>;
	};
}
