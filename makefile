include common.mk

# External libraries
LIBS :=		third-party/llvm-project/build/lib/libc++.a\
			third-party/llvm-project/build/lib/libc++experimental.a\
			third-party/llvm-project/build/lib/libc++abi.a\
			third-party/llvm-project/build/lib/libunwind.a\
			third-party/antlr4/runtime/Cpp/build/runtime/libantlr4-runtime.a\
			third-party/libastmatcher-parser/libastmatcher-parser.a

# Compilation database output
CXXDB := 	$(TMP_DIR)/compile_commands.json


# Project sources
VOID := 	$(shell cd ./third-party/cppmodsort/ && make)
MODULES :=	$(shell ./third-party/cppmodsort/cppmodsort $(shell find src/module -type f -name "*.cppm"))
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

# Extract the path of the current Makefile
CURRENT_MAKEFILE := $(lastword $(MAKEFILE_LIST))



include third-party/makefile

#-------------------------------------------------#

.SUFFIXES:
.PRECIOUS: 	$(PCHS) $(PCMS)
.PHONY: 	all test clean fclean re

all: $(LIBS_MADE_MARKER) $(NAME) $(EXECS)

$(PCH_DIR)/%.pch: $(SRC_DIR)/%.hpp makefile third-party/makefile
	@mkdir -p $(@D)
	$(CXX) -x c++-header -DCLANGD $(CXXFLAGS) -o $@ $<

-include $(DEPS)

$(PCM_DIR)/%.pcm: $(SRC_DIR)/%.cppm $(PCHS)
	@mkdir -p $(@D)
	@mkdir -p $(shell dirname $(patsubst $(PCM_DIR)/%.pcm,$(DEP_DIR)/%.cppm.d,$(@)))
	$(CXX) $(CXXFLAGS) -MMD -MF $(patsubst $(PCM_DIR)/%.pcm,$(DEP_DIR)/%.cppm.d,$(@)) --precompile $< -o $@ $(INCPCHS)
	@case "$<" in \
		$(MOD_DIR)/*)\
			path="$<"; \
			prefix="$(MOD_DIR)/"; \
			stripped_path=$${path#$${prefix}}; \
			vendor_name=$$(echo "$$stripped_path" | cut -d'/' -f1); \
			num_folders=$$(echo "$$stripped_path" | tr -cd '/' | wc -c); \
			if test $$num_folders = 1 ; then \
				cp -f $@ $(PCM_DIR)/$$vendor_name.$(notdir $@); \
			else \
				project_name=$$(echo "$$stripped_path" | cut -d'/' -f2); \
				cp -f $@ $(PCM_DIR)/$$vendor_name.$$project_name-$(notdir $@);  \
			fi; \
		;;\
		*)\
		;;\
	esac

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

test:
	./bin/test/lexer.out

clean:
	rm -f $(DEPS) $(OBJS) $(CXXDB)

fclean: clean
	rm -f $(NAME)
	rm -f $(EXECS)
	rm -f $(PCMS)
	rm -f $(PCHS)
	rm -f $(LIBS_MADE_MARKER)
	rm -rf $(LIBS)
	make clean -C third-party/libastmatcher-parser
	rm -rf third-party/runtime/Cpp/build

re: clean all
