ANTLR_OUT_FILES=AstMatcher.tokens\
	AstMatcher.interp\
	AstMatcherLexer.tokens\
	AstMatcherLexer.interp\
	AstMatcherLexer.cpp\
	AstMatcherLexer.h\
	AstMatcherParser.cpp\
	AstMatcherParser.h\
	AstMatcherListener.cpp\
	AstMatcherListener.h\
	AstMatcherBaseListener.cpp\
	AstMatcherBaseListener.h\
	AstMatcherVisitor.cpp\
	AstMatcherVisitor.h\
	AstMatcherBaseVisitor.cpp\
	AstMatcherBaseVisitor.h

a.out:  $(ANTLR_OUT_FILES) _test.cpp _visitor.hpp
	clang++ *.cpp -I./../../bin/build-tools/antlr4/runtime/Cpp/runtime/src ./../../bin/build-tools/antlr4/runtime/Cpp/dist/libantlr4-runtime.a

$(ANTLR_OUT_FILES): AstMatcher.g4
	antlr -Dlanguage=Cpp -visitor AstMatcher.g4

clean:
	rm -f a.out $(ANTLR_OUT_FILES)
