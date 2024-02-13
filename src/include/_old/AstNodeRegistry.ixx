#pragma once

#include "./ClassRegistry.hpp"
#include "./Ast.hpp"

using namespace std;

struct AstNodeRegistry : public ClassRegistry<AstNode>
{

};
