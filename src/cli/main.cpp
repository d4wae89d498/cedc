
import ucbl.cedilla;

using namespace cedilla;

fn main() -> int
{

    string key;
    int value;
	float v;
	int rest;
	float d = -1;

	if (scan("23.2549 end","{} end", d))
		println("OK VAL {}", d);

	if (scan("test =", "{} =", key))
		println("key: [{}]", key);

    if (scan("test = 12 0.26", "{} = {} {}", key, value, d))
		println("key: [{}]", key);
	else
		println("pasok");
	println("k: {}", value);
	println("d: {}", d);
    return 0;
}
