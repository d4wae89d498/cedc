#pragma once
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct ParsingRule
{
    string name;

	ParsingRule(string name)
	{
		cout << name << endl;
		this->name = name;
	}

    virtual size_t f(const string) = 0;
    virtual ~ParsingRule() {}
};


struct Parser
{

	vector<unique_ptr<ParsingRule>>	rules;
	const char 						*path;

	Parser(const char *path)
	{
		this->path = path;
	};

	void parse()
	{
		ifstream file(this->path);
		if (!file.is_open()) {
			cerr << "Failed to open file: " << this->path << endl;
			exit(1);
		}
		stringstream buffer;
		buffer << file.rdbuf();
		string src = buffer.str();

		size_t i = 0;
		const size_t src_length = src.length();
		while (i < src_length)
		{
			cout << src[i] << endl;
			i += 1;
		}
	};
};
