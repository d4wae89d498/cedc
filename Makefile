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
SRCS :=		Std.cppm\
			Serializable.cppm\
			LinkedList.cppm\
			Tree.cppm
SRCS := 	$(SRCS:%=$(SRC_DIR)/%)
OBJS := 	$(SRCS:$(SRC_DIR)/%.cppm=$(TMP_DIR)/%.o)
PCMS := 	$(SRCS:$(SRC_DIR)/%.cppm=$(TMP_DIR)/%.pcm)

# Project library
NAME :=		$(LIB_DIR)/libcedilla.a

# Project executables
MAINS :=	cli/main.cpp
MAINS :=	$(MAINS:%=$(SRC_DIR)/%)
EXECS :=	$(MAINS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.out)

# Project Precompiled headers
HEADERS :=	include/pch.hpp
HEADERS := 	$(HEADERS:%=$(SRC_DIR)/%)
PCHS	:=	$(HEADERS:$(SRC_DIR)/%.hpp=$(TMP_DIR)/%.pch)
INCPCHS :=	$(PCHS:%=-include-pch %)

# Common dependancies
DEPS := 	makefile

#-------------------------------------------------#

.SUFFIXES:
.PRECIOUS: 	$(PCH) $(TMP_DIR)/%.pcm
.PHONY: 	all clean fclean re

all: $(NAME) $(EXECS) $(CXXDB)
	which $(CXX)

$(TMP_DIR)/%.pch: $(SRC_DIR)/%.hpp $(DEPS)
	@mkdir -p $(@D)
	$(CXX) -x c++-header $(CXXFLAGS) -o $@ $<

$(TMP_DIR)/%.pcm: $(SRC_DIR)/%.cppm $(PCHS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCPCHS) --precompile $< -o $@

$(TMP_DIR)/%.o: $(TMP_DIR)/%.pcm
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS)  -c $< -o $@

$(NAME): $(OBJS)
	@mkdir -p $(@D)
	ar -rcs $@ $(OBJS)

$(BIN_DIR)/%.out: $(SRC_DIR)/%.cpp $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCPCHS) $< $(NAME) -o $@

clean:
	rm -f $(OBJS) $(PCMS) $(PCHS)

fclean: clean
	rm -f $(NAME)
	rm -f $(EXECS)

re: fclean all

$(CXXDB): $(SRCS) $(MAIN)
	make --always-make --dry-run \
	| grep -wE 'clang\+\+' \
	| jq -nR '[inputs | {directory: env.PWD, command: . , file: (match("\\S+\\.(cpp|cppm)").string)}]' \
	> $(CXXDB)

