
module ucbl.cedilla:tree;

namespace cedilla
{
	fn f() -> int
	{
		if (true)
		{
		}
		int f;
		return 21;
	}
}

// namespace cedilla

/*
A  <- cursor

  ...
   |
   +-- Child1 <- cursor

  ...
   |
   +-- Child1 <- cursor
   +-- Child2 <- cursor

 A B <- cursor

 A B C <- cursor

 A B C
   |
   +-- Child1
   +-- Child2


=> pas besoin de parent ?

*/
