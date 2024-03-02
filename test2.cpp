import std;
//import std.compat;

using namespace std;


template<typename... Args>
bool scan23(const string& input, const string& format, Args&... args) {
	string regex_format = regex_replace(format, regex("\\{\\}"), "([^ ]*)");
	println("{}", regex_format);
	regex r(regex_format);
    smatch match;
    if (regex_search(input, match, r) && match.size() == sizeof...(Args) + 1) { // +1 for the whole match
        istringstream iss;
        size_t index = 0;
        ((iss.clear(), iss.str(match[++index]), iss >> args), ...);
        return true;
    }
    return false;
}

int main() {
   string key = "lol";
    int value;
    string value2 = "";
	scan23("dadw =21=pomme", "{} ={}={}", key, value, value2);
	println("value: {}", key);
	println("value: {}", value);
	println("value: {}", value2);

    return 0;
}
