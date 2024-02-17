# Project structure
BIN_DIR := 	bin
LIB_DIR := 	lib
SRC_DIR := 	src
TMP_DIR := 	tmp

# Tmp subdirs
OBJ_DIR := $(TMP_DIR)/obj
PCM_DIR := $(TMP_DIR)/pcm
PCH_DIR := $(TMP_DIR)/pch
DEP_DIR := $(TMP_DIR)/dep

# Compilation flags
CXX :=		clang++ -std=c++26
CXXFLAGS :=	-nostdinc++ -fprebuilt-module-path=$(PCM_DIR) -fprebuilt-module-path=lib/libcxx-pcm/lib

CXXDB := 	compile_commands.json

# Project sources
SRCS :=		Serializable.cppm\
			LinkedList.cppm\
			Tree.cppm\
			Box.cppm\
			ClassRegistry.cppm\
			Ast.cppm

SRCS := 	$(SRCS:%=$(SRC_DIR)/%)
OBJS := 	$(SRCS:$(SRC_DIR)/%.cppm=$(OBJ_DIR)/%.o)
PCMS := 	$(SRCS:$(SRC_DIR)/%.cppm=$(PCM_DIR)/%.pcm)

# Project library
NAME :=		$(LIB_DIR)/libcedilla.a

# Project executables
MAINS :=	cli/main.cpp
MAINS :=	$(MAINS:%=$(SRC_DIR)/%)
EXECS :=	$(MAINS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.out)

# Project headers
HEADERS :=	include/common.hpp
HEADERS := 	$(HEADERS:%=$(SRC_DIR)/%)
PCHS	:=	$(HEADERS:$(SRC_DIR)/%.hpp=$(PCH_DIR)/%.pch)
INCPCHS :=	$(PCHS:%=-include-pch %)

# Deps
DEPS 	:= 	$(SRCS:$(SRC_DIR)/%.cppm=$(DEP_DIR)/%.d)

# Submodules libraries marker
LIBCXX_MADE_MARKER=.libcxx_made

#-------------------------------------------------#

.SUFFIXES:
.PRECIOUS: 	$(PCHS) $(PCMS)
.PHONY: 	all clean fclean re

$(LIBCXX_MADE_MARKER):
	make -C lib/libcxx-pcm
	@ln -sf $(shell pwd)/lib/libcxx-pcm/lib/libcxx.a lib/libcxx.a
	@touch $(LIBCXX_MADE_MARKER)

all: $(LIBCXX_MADE_MARKER) $(NAME) $(EXECS)

$(PCH_DIR)/%.pch: $(SRC_DIR)/%.hpp makefile
	@mkdir -p $(@D)
	$(CXX) -x c++-header -DCLANGD $(CXXFLAGS) -o $@ $<

-include tmp/dep/*.d

$(PCM_DIR)/%.pcm: $(SRC_DIR)/%.cppm $(PCHS)
	@mkdir -p $(@D)
	@mkdir -p $(DEP_DIR)
	$(CXX) $(CXXFLAGS) -MMD -MF $(patsubst $(PCM_DIR)/%.pcm,$(DEP_DIR)/%.d,$(@)) --precompile $< -o $@ $(INCPCHS)

$(OBJ_DIR)/%.o: $(PCM_DIR)/%.pcm
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS)  -c $< -o $@

$(NAME): $(OBJS)
	@mkdir -p $(@D)
	ar -rcs $@ $(OBJS)
	@make $(CXXDB)

$(BIN_DIR)/%.out: $(SRC_DIR)/%.cpp $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -o $@ $(INCPCHS) $(NAME) lib/libcxx.a -w
	@make $(CXXDB)

$(CXXDB): $(EXECS)
	@make --always-make --dry-run \
	| grep -wE 'clang\+\+' \
	| jq -nR '[inputs | {directory: env.PWD, command: (. + " -DCLANGD") , file: (match("\\S+\\.(cpp|cppm)").string)}]' \
	> $(CXXDB)

clean:
	rm -f $(DEPS) $(OBJS) $(CXXDB)

fclean: clean
	rm -f $(NAME)
	rm -f $(EXECS)
	rm -f $(PCMS)
	rm -f $(PCHS)
	rm -f $(LIBCXX_MADE_MARKER)
	make fclean -C lib/libcxx-pcm
re: fclean all
