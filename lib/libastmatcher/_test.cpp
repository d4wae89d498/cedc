#include "antlr4-runtime.h"
#include "AstMatcherLexer.h"
#include "AstMatcherParser.h"
#include "_visitor.hpp"

using namespace antlr4;

int main(int argc, const char* argv[]) {
    std::ifstream stream;
    stream.open("_test.txt");

   std::stringstream buffer;
    buffer << stream.rdbuf();
    std::string content = buffer.str();

	std::cout << "Input: " << content << std::endl;

    antlr4::ANTLRInputStream input(content);
    AstMatcherLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);

	tokens.fill();
    for (auto token : tokens.getTokens()) {
        std::cout << token->toString() << std::endl;
    }

    AstMatcherParser parser(&tokens);

    AstMatcherParser::PatternContext* tree = parser.pattern();
    ReverseAstMatcherVisitor visitor;
    visitor.visit(tree);


    return 0;
}
