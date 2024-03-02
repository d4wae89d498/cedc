import ucbl.cedilla;

using namespace cedilla;

fn main() -> int
{
 	string key;
    int value;


    if (scan("answer = 42", "{} = {}", key, value)) {
        cout << "Parsed successfully:\n";
        cout << "Key: " << key << "\n";
        cout << "Value: " << value << "\n";
    } else {
        cout << "Failed to parse the string.\n";
    }


	//cout << AstNodeRegistry::get().createInstance("Identifier") << endl;

	//printf("... hello\n");
	unique_ptr<int> p;
/*
	cout << "" << endl;

	string a;

	unique_ptr<string> pp;
*/
//	Serializable::serialize();
}
