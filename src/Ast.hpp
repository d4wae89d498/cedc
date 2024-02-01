#pragma once
#include <vector>
#include <any>
#include "./Tree.hpp"

using namespace std;


class AstNode : public Tree<AstNode>
{
	public:
	virtual ~AstNode() = default;
	// TODO: add generic properies assoc array
};



class Ast
{
	public:
	AstNode root;
	// TODO: add ast macro rules
};
