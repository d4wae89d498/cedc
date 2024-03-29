## Coding Style

## Naming

Cases :

- UPPER_SNAKE_CASE for macros, enum items, and constexpr names.
- lower_snake_case for var names (prefer one letter where applicable), function names, namespaces and module partition names.
- PascalCase for user-defined class names and templates arguments (prefer one letter where applicable),
- modules names should be defined as organisation_name.module_name
- use all needed namespace instead of prefixing it on each calls

Prefixes :
- only g_ for global and s_ for static. None for members nor types.

Braces :
Always use ANSI C++ style.

Modules :
Dont use private fragments. use a separate impl file for easier build system that uses timestamp. Implementation module ext shall be a  `.cpp`.  `.cppm` for interfaces.
One class per module (or one function and its primitives is acceptable). Group impl and intrfaces within a dir named according class name but in snake case. If interface only, file goes at root of project without a directory.

classes :
constructor shall be explicit

```C++
export module vendor_name.module_name:partition_name;

#define SOME_MACRO_CONST 21

typedef enum
{
	SOME_ENUM_CONST1 = 0,
	SOME_ENUM_CONST2 = 1
}	my_enum;

constexpr float MY_PI = 3.14;
constexpr float MY_EXP(float x, int n)
{
    return n == 0 ? 1 :
        n % 2 == 0 ? MY_EXP(x * x, n / 2) :
        MY_EXP(x * x, (n - 1) / 2) * x;
}


int g_myint = 0;

namespace namespace_name
{
	template <typename T>
	class ClassName
	{
		int 	member_var;

		fn	some_func()
		{
			static int	s_local_var;
			int			local_var;

			const mylocalconst = this->member_var + 3; // note the this->

			while (cond1)
			{
				if (cond2)
				{
	...
				}
				else
				{
	...
				}
			}
		}
	}
}
```

## VS Code configuration

we provided .vscode/extension file to suggest you to install clangd ext.
