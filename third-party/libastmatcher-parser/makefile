# Get the directory of the current Makefile
CURRENT_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

# Get the parent directory
PROJECT_DIR := $(realpath $(CURRENT_DIR)/../..)

include $(PROJECT_DIR)/common.mk

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

ANTLR_OUT_HEADERS=	AstMatcherLexer.h\
	AstMatcherParser.h\
	AstMatcherListener.h\
	AstMatcherBaseListener.h\
	AstMatcherVisitor.h\
	AstMatcherBaseVisitor.h

ANTLR_OBJS=$(ANTLR_OUT_SOURCES:.cpp=.o)

NAME=libastmatcher-parser.a

all: $(NAME)

$(NAME): $(ANTLR_OUT_FILES) $(ANTLR_OBJS)
	ar -rcs $@ $(ANTLR_OBJS)

$(ANTLR_OUT_SOURCES): AstMatcher.g4
	antlr -Dlanguage=Cpp -visitor AstMatcher.g4

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I../antlr4/runtime/Cpp/runtime/src

clean:
	rm -f a.out $(ANTLR_OUT_OTHERS) $(ANTLR_OUT_SOURCES) $(ANTLR_OUT_HEADERS) $(ANTLR_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
