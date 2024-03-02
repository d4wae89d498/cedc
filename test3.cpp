import std;

using namespace std;

int main() {
    string str = "123"; // Example string that represents an integer
	int value;

	from_chars(str.data(), str.data() + str.size(), value);

	print("{}\n", value);
    return 0;
}
