SRCS :=		Std.cppm\
			Serializable.cppm\
			LinkedList.cppm\
			Tree.cppm

PCH :=		pch

TMP_DIR := 	tmp
LIB_DIR := 	lib
BIN_DIR := 	bin
SRC_DIR := 	src

SRCS := 	$(SRCS:%=$(SRC_DIR)/%)
PCH := 		$(PCH:%=$(TMP_DIR)/%)
OBJS := 	$(SRCS:$(SRC_DIR)/%.cppm=$(TMP_DIR)/%.o)
PCMS := 	$(SRCS:$(SRC_DIR)/%.cppm=$(TMP_DIR)/%.pcm)

DEPS := 	Makefile $(PCH)


NAME :=		$(LIB_DIR)/libcedilla.a
MAIN :=		$(BIN_DIR)/main


CXX :=		clang++
CXXFLAGS :=	-std=c++26 -fprebuilt-module-path=$(TMP_DIR)

CXXDB := compile_commands.json


.SUFFIXES:
.PRECIOUS: 	$(PCH) $(TMP_DIR)/%.pcm
.PHONY: 	all clean fclean re

all: $(DEPS) $(NAME) $(MAIN) $(CXXDB)
	which $(CXX)

$(PCH): src/include/pch.hpp
	@mkdir -p $(@D)
	$(CXX) -x c++-header $(CXXFLAGS) -o $@ $<

$(TMP_DIR)/%.pcm: $(SRC_DIR)/%.cppm $(DEPS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -include-pch $(PCH) --precompile $< -o $@

$(TMP_DIR)/%.o: $(TMP_DIR)/%.pcm $(DEPS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS)  -c $< -o $@

$(NAME): $(OBJS) $(DEPS)
	@mkdir -p $(@D)
	ar -rcs $@ $(OBJS)

$(MAIN): $(NAME) $(DEPS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -include-pch $(PCH) $(SRC_DIR)/main.cpp $(NAME) -o $@

clean:
	rm -f $(OBJS) $(PCMS) $(PCH)

fclean: clean
	rm -f $(MAIN)
	rm -f $(NAME)

re: fclean all

$(CXXDB): $(SRCS) $(MAIN)
	make --always-make --dry-run \
	| grep -wE 'clang\+\+' \
	| jq -nR '[inputs | {directory: env.PWD, command: . , file: (match("\\S+\\.(cpp|cppm)").string)}]' \
	> $(CXXDB)

