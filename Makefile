# Project structure
BIN_DIR := 	bin
LIB_DIR := 	lib
SRC_DIR := 	src
TMP_DIR := 	tmp

# Compilation flags
CXX :=		clang++
CXXFLAGS :=	-std=c++26 -fprebuilt-module-path=$(TMP_DIR)/pcm
CXXDB := 	compile_commands.json

# Project sources
SRCS :=		Serializable.cppm\
			LinkedList.cppm\
			Tree.cppm\
			Box.cppm\
			ClassRegistry.cppm\
			Ast.cppm

SRCS := 	$(SRCS:%=$(SRC_DIR)/%)
OBJS := 	$(SRCS:$(SRC_DIR)/%.cppm=$(TMP_DIR)/obj/%.o)
PCMS := 	$(SRCS:$(SRC_DIR)/%.cppm=$(TMP_DIR)/pcm/%.pcm)

# Project library
NAME :=		$(LIB_DIR)/libcedilla.a

# Project executables
MAINS :=	cli/main.cpp
MAINS :=	$(MAINS:%=$(SRC_DIR)/%)
EXECS :=	$(MAINS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.out)

# Project headers
HEADERS :=	include/common.hpp
HEADERS := 	$(HEADERS:%=$(SRC_DIR)/%)
PCHS	:=	$(HEADERS:$(SRC_DIR)/%.hpp=$(TMP_DIR)/pch/%.pch)
INCPCHS :=	$(PCHS:%=-include-pch %)

# Deps
DEPS 	:= 	$(SRCS:$(SRC_DIR)/%.cppm=$(TMP_DIR)/deps/%.d)

# Common dependancies

#-------------------------------------------------#

.SUFFIXES:
.PRECIOUS: 	$(PCHS) $(TMP_DIR)/%.pcm
.PHONY: 	all clean fclean re

all: $(NAME) $(EXECS)
	which $(CXX)
	echo $(DEPS)

$(TMP_DIR)/pch/%.pch: $(SRC_DIR)/%.hpp makefile
	@mkdir -p $(@D)
	$(CXX) -x c++-header -DCLANGD $(CXXFLAGS) -o $@ $<

-include tmp/dep/*.d

$(TMP_DIR)/pcm/%.pcm: $(SRC_DIR)/%.cppm $(PCHS)
	@mkdir -p $(@D)
	@mkdir -p $(TMP_DIR)/dep
	$(CXX) $(CXXFLAGS) -MMD -MF $(patsubst $(TMP_DIR)/pcm/%.pcm,$(TMP_DIR)/dep/%.d,$(@)) --precompile $< -o $@ $(INCPCHS)

$(TMP_DIR)/obj/%.o: $(TMP_DIR)/pcm/%.pcm
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS)  -c $< -o $@

$(NAME): $(OBJS)
	@mkdir -p $(@D)
	ar -rcs $@ $(OBJS)
	@make $(CXXDB)

$(BIN_DIR)/%.out: $(SRC_DIR)/%.cpp $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< $(NAME) -o $@ $(INCPCHS)
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
