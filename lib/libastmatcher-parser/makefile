ANTLR_OUT_OTHERS=AstMatcher.tokens\
	AstMatcher.interp\
	AstMatcherLexer.tokens\
	AstMatcherLexer.interp

ANTLR_OUT_SOURCES=AstMatcherLexer.cpp\
	AstMatcherParser.cpp\
	AstMatcherListener.cpp\
	AstMatcherBaseListener.cpp\
	AstMatcherVisitor.cpp\
	AstMatcherBaseVisitor.cpp\

ANTLR_OUT_HEADERS=AstMatcherLexer.cpp\
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

ANTLR_OBJS=$(ANTLR_OUT_SOURCES:.cpp=.o)

NAME=libastmatcher-parser.a

all: $(NAME)

$(NAME): $(ANTLR_OUT_FILES) $(ANTLR_OBJS)
	ar -rcs $@ $(ANTLR_OBJS)

$(ANTLR_OUT_SOURCES): AstMatcher.g4
	antlr -Dlanguage=Cpp -visitor AstMatcher.g4

%.o: %.cpp
	clang++ -c $< -o $@ -I../libantlr4-runtime/runtime/src

clean:
	rm -f a.out $(ANTLR_OUT_OTHERS) $(ANTLR_OUT_SOURCES) $(ANTLR_OUT_HEADERS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
