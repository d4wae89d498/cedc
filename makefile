# Project structure
BIN_DIR := 	bin
LIB_DIR := 	lib
SRC_DIR := 	src
TMP_DIR := 	tmp

# Src subdirs
MOD_DIR := $(SRC_DIR)/module

# Tmp subdirs
OBJ_DIR := $(TMP_DIR)/obj
PCM_DIR := $(TMP_DIR)/pcm
PCH_DIR := $(TMP_DIR)/pch
DEP_DIR := $(TMP_DIR)/dep

# Compilation flags
CXX :=		clang++ -std=c++26
CXXFLAGS =	-g\
			-O0\
			-fsanitize=address\
			-nostdinc++\
			-nostdlib++\
			-Itools/llvm-project/build/include/c++/v1\
			-Wno-unqualified-std-cast-call\
			-fprebuilt-module-path=$(PCM_DIR)\
			-Ilib/libantlr4-runtime/runtime/src\
			-Ilib/libastmatcher-parser\
			-Wno-unused-command-line-argument\
			-Wreserved-module-identifier

ifeq ($(shell uname -s), Darwin)
    CXXFLAGS += -target x86_64-apple-macos10.9
endif

# External libraries
LIBS :=		tools/llvm/build/lib/libc++.a\
			tools/llvm/build/lib/libc++experimental.a\
			tools/llvm/build/lib/libc++abi.a\
			tools/llvm/build/lib/libunwind.a\
			tools/antlr4/runtime/Cpp/dist/libantlr4-runtime.a\
			tools/libastmatcher-parser/libastmatcher-parser.a

#				$(shell find $(PCM_DIR) -type d | sed 's/^/-fprebuilt-module-path=/' | tr '\n' ' ')

# Compilation database output
CXXDB := 	$(TMP_DIR)/compile_commands.json

# Project sources
VOID := 	$(shell cd ./tools/cppmodsort/ && make)
MODULES :=	$(shell ./tools/cppmodsort/cppmodsort $(shell find src/module -type f -name "*.cppm"))
IMPLS :=	$(shell find src/module -type f -name "*.cpp")

# Project objects
OBJS := 	$(MODULES:$(SRC_DIR)/%.cppm=$(OBJ_DIR)/%.cppm.o)\
			$(IMPLS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.cpp.o)

# Project pre-compiled modules
PCMS := 	$(MODULES:$(SRC_DIR)/%.cppm=$(PCM_DIR)/%.pcm)

# Project library
NAME :=		$(LIB_DIR)/libcedilla.a

# Project executables
MAINS :=	cli/main.cpp\
			\
			test/ast.cpp\
			test/linked_list.cpp\
			test/tree.cpp\
			test/lexer.cpp

MAINS :=	$(MAINS:%=$(SRC_DIR)/%)
EXECS :=	$(MAINS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.out)

# Project headers
HEADERS :=	include/common.hpp
HEADERS := 	$(HEADERS:%=$(SRC_DIR)/%)
PCHS	:=	$(HEADERS:$(SRC_DIR)/%.hpp=$(PCH_DIR)/%.pch)
INCPCHS :=	$(PCHS:%=-include-pch %)

# Deps
DEPS 	:= 	$(MODULES:$(SRC_DIR)/%=$(DEP_DIR)/%.d) $(IMPLS:$(SRC_DIR)/%=$(DEP_DIR)/%.d)

# Submodules libraries marker
LIBS_MADE_MARKER=$(TMP_DIR)/.libs_made

# Extract the path of the current Makefile
CURRENT_MAKEFILE := $(lastword $(MAKEFILE_LIST))

# Extract the directory of the current Makefile
MAKEFILE_DIR := $(realpath $(dir $(CURRENT_MAKEFILE)))

#-------------------------------------------------#

.SUFFIXES:
.PRECIOUS: 	$(PCHS) $(PCMS)
.PHONY: 	all clean fclean re

all: $(LIBS_MADE_MARKER) $(NAME) $(EXECS)

$(LIBS_MADE_MARKER):
	@mkdir -p $(@D)
	@mkdir -p tmp/pcm
	@cd tools/llvm-project \
		&& rm -rf build \
		&& mkdir -p build \
		&& cmake -G Ninja -S runtimes -B build \
			-DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi;libunwind" \
			-DCMAKE_C_COMPILER=$(shell which clang) \
			-DCMAKE_CXX_COMPILER=$(shell which clang++) \
		&& ninja -C build
	$(CXX) $(CXXFLAGS) --precompile tools/llvm-project/build/modules/c++/v1/std.cppm -o tmp/pcm/std.pcm
	$(CXX) $(CXXFLAGS) --precompile tools/llvm-project/build/modules/c++/v1/std.compat.cppm -o tmp/pcm/std.compat.pcm
	@cd tools/antlr4/runtime/Cpp \
		&& rm -rf build \
		&& mkdir -p build \
		&& cd build \
		&& cmake .. \
		&& make
	@make -C tools/libastmatcher-parser
	@touch $(LIBS_MADE_MARKER)

$(PCH_DIR)/%.pch: $(SRC_DIR)/%.hpp makefile
	@mkdir -p $(@D)
	$(CXX) -x c++-header -DCLANGD $(CXXFLAGS) -o $@ $<

-include $(DEPS)

$(PCM_DIR)/%.pcm: $(SRC_DIR)/%.cppm $(PCHS)
	@mkdir -p $(@D)
	@mkdir -p $(shell dirname $(patsubst $(PCM_DIR)/%.pcm,$(DEP_DIR)/%.cppm.d,$(@)))
	$(CXX) $(CXXFLAGS) -MMD -MF $(patsubst $(PCM_DIR)/%.pcm,$(DEP_DIR)/%.cppm.d,$(@)) --precompile $< -o $@ $(INCPCHS)
	@if [[ "$<" == $(MOD_DIR)/* ]]; then \
		path="$<"; \
		prefix="$(MOD_DIR)/"; \
		stripped_path=$${path#$${prefix}}; \
		vendor_name=$$(echo "$$stripped_path" | cut -d'/' -f1); \
		num_folders=$$(echo "$$stripped_path" | tr -cd '/' | wc -c); \
		if [[ $$num_folders -eq 1 ]]; then \
			cp -f $@ $(PCM_DIR)/$$vendor_name.$(notdir $@); \
		else \
			project_name=$$(echo "$$stripped_path" | cut -d'/' -f2); \
			cp -f $@ $(PCM_DIR)/$$vendor_name.$$project_name-$(notdir $@);  \
		fi; \
	fi

$(OBJ_DIR)/%.cppm.o: $(PCM_DIR)/%.pcm
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS)  -c $< -o $@

$(OBJ_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS)  -c $< -o $@

$(NAME): $(OBJS)
	@mkdir -p $(@D)
	ar -rcs $@ $(OBJS)
	@make $(CXXDB)

$(BIN_DIR)/%.out: $(SRC_DIR)/%.cpp $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -o $@ $(INCPCHS) $(NAME) $(LIBS) -w
	@make $(CXXDB)

$(CXXDB): $(EXECS)
	@make --always-make --dry-run \
	| grep -wE 'clang\+\+' \
	| jq -nR '[inputs | {directory: env.PWD, command: (. + " -DCLANGD") , file: (match("\\S+\\.(cpp|cppm|hpp)(?=\\s|$$)").string)}]' \
	> $(CXXDB)

clean:
	rm -f $(DEPS) $(OBJS) $(CXXDB)

fclean: clean
	rm -f $(NAME)
	rm -f $(EXECS)
	rm -f $(PCMS)
	rm -f $(PCHS)
	rm -f $(LIBS_MADE_MARKER)
	rm -rf $(LIBS)
	make fclean -C lib/libcxx-pcm
	make clean -C lib/libastmatcher-parser
	rm -rf lib/antlr4-runtime/build

re: fclean all
