# Project structure
BIN_DIR := 	bin
LIB_DIR := 	lib
SRC_DIR := 	src
TMP_DIR := 	tmp

# Compilation flags
CXX :=		clang++
CXXFLAGS :=	-std=c++26 -fprebuilt-module-path=$(TMP_DIR)
CXXDB := 	compile_commands.json

# Project sources
SRCS :=		Serializable.cppm\
			LinkedList.cppm\
			Tree.cppm\
			Box.cppm\
			ClassRegistry.cppm\
			Ast.cppm

SRCS := 	$(SRCS:%=$(SRC_DIR)/%)
OBJS := 	$(SRCS:$(SRC_DIR)/%.cppm=$(TMP_DIR)/%.o)
PCMS := 	$(SRCS:$(SRC_DIR)/%.cppm=$(TMP_DIR)/%.pcm)

# Project library
NAME :=		$(LIB_DIR)/libcedilla.a

# Project executables
MAINS :=	cli/main.cpp
MAINS :=	$(MAINS:%=$(SRC_DIR)/%)
EXECS :=	$(MAINS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.out)

# Project headers
HEADERS :=	include/common.hpp
HEADERS := 	$(HEADERS:%=$(SRC_DIR)/%)
PCHS	:=	$(HEADERS:$(SRC_DIR)/%.hpp=$(TMP_DIR)/%.pch)
#INCPCHS2 :=	$(PCHS:%=-include-pch %)
INCPCHS :=	$(PCHS:%=-include-pch %)

# Common dependancies
DEPS := 	makefile

#-------------------------------------------------#

.SUFFIXES:
.PRECIOUS: 	$(PCHS) $(TMP_DIR)/%.pcm
.PHONY: 	all clean fclean re

all: $(NAME) $(EXECS)
	which $(CXX)

$(TMP_DIR)/%.pch: $(SRC_DIR)/%.hpp $(DEPS)
	@mkdir -p $(@D)
	$(CXX) -x c++-header -DCLANGD $(CXXFLAGS) -o $@ $<


$(TMP_DIR)/%.pcm: $(SRC_DIR)/%.cppm $(PCHS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) --precompile $< -o $@

$(TMP_DIR)/%.o: $(TMP_DIR)/%.pcm
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS)  -c $< -o $@

$(NAME): $(OBJS)
	@mkdir -p $(@D)
	ar -rcs $@ $(OBJS)
	@make $(CXXDB)

$(BIN_DIR)/%.out: $(SRC_DIR)/%.cpp $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< $(NAME) -o $@
	@make $(CXXDB)

$(CXXDB): $(EXECS)
	@make --always-make --dry-run \
	| grep -wE 'clang\+\+' \
	| jq -nR '[inputs | {directory: env.PWD, command: (. + " -DCLANGD") , file: (match("\\S+\\.(cpp|cppm)").string)}]' \
	> $(CXXDB)

clean:
	rm -f $(OBJS) $(PCMS) $(PCHS) $(CXXDB)

fclean: clean
	rm -f $(NAME)
	rm -f $(EXECS)

re: fclean all
