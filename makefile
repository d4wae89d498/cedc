.DEFAULT_GOAL := default

include common.mk

# Set the libraries to link
LIBS := third-party/libastmatcher-parser/libastmatcher-parser.a\
 	third-party/antlr/runtime/Cpp/build/runtime/libantlr4-runtime.a\
 	third-party/llvm-project/build/lib/libunwind.a\
 	third-party/llvm-project/build/lib/libc++experimental.a\
 	third-party/llvm-project/build/lib/libc++.a\
 	third-party/llvm-project/build/lib/libc++abi.a

# Compilation database output
CXXDB := 	$(TMP_DIR)/compile_commands.json

# Project modules
MODULES := $(shell find src/module -type f -name "*.cppm")
VOID := $(shell make -C ./third-party/cppmodsort/ \
			&& mkdir -p $(DEP_DIR) \
			&& ./third-party/cppmodsort/cppmodsort \
			-m --src-dir src/ --pcm-dir tmp/pcm/ $(MODULES) > tmp/dep/module.d)
include tmp/dep/module.d

# Project sources
IMPLS :=	$(shell find src/module -type f -name "*.cpp")

# Project objects
OBJS := 	$(MODULES:$(SRC_DIR)/%.cppm=$(OBJ_DIR)/%.cppm.o)\
			$(IMPLS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.cpp.o)

# Project pre-compiled modules
PCMS := 	$(MODULES:$(SRC_DIR)/%.cppm=$(PCM_DIR)/%.pcm)

# Project library
NAME :=		$(LIB_DIR)/libcedilla.a

# Project executables
MAINS :=	$(shell find src/cli -type f -name "*.cpp")
TESTS := 	$(shell find src/test -type f -name "*.cpp")
MAINS_OUT := $(MAINS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.out)
TESTS_OUT := $(TESTS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.out)
EXECS :=	$(MAINS_OUT) $(TESTS_OUT)

# Project headers
HEADERS :=	$(shell find src/include -type f -name "*.hpp")
PCHS	:=	$(HEADERS:$(SRC_DIR)/%.hpp=$(PCH_DIR)/%.pch)
INCPCHS :=	$(PCHS:%=-include-pch %)

# Makefile dependecy files
DEPS 	:= 	$(MODULES:$(SRC_DIR)/%=$(DEP_DIR)/%.d) $(IMPLS:$(SRC_DIR)/%=$(DEP_DIR)/%.d)

# Include third-party makefile
include third-party/makefile

# Multithreaded build by default
ifeq ($(shell uname), Darwin)
    CPU_CORES := $(shell sysctl -n hw.ncpu)
else
    CPU_CORES := $(shell nproc)
endif
default:
	make -j$(CPU_CORES) all
#-------------------------------------------------#

.SUFFIXES:
.PRECIOUS: 	$(PCHS) $(PCMS)
.PHONY: 	default all test clean fclean re

all: $(THIRD_PARTY_BUILT_MARKER) $(EXECS) $(CXXDB)

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
			echo "Warning: Unknown module file location '$<'"; \
		;;\
	esac

$(OBJ_DIR)/%.cppm.o: $(PCM_DIR)/%.pcm
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS)  -c $< -o $@

$(OBJ_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp $(PCHS) $(PCMS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS)  -c $< -o $@

$(NAME): $(OBJS)
	@mkdir -p $(@D)
	ar -rcs $@ $(OBJS)

$(BIN_DIR)/%.out: $(SRC_DIR)/%.cpp $(NAME) $(PCMS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -o $@ $(INCPCHS) $(NAME) $(LIBS) -w

$(CXXDB): $(EXECS)
	@make --always-make --dry-run \
	| grep -wE 'clang\+\+' \
	| jq -nR '[inputs | {directory: env.PWD, command: (. + " -DCLANGD") , file: (match("\\S+\\.(cpp|cppm|hpp)(?=\\s|$$)").string)}]' \
	> $(CXXDB)

define run-and-check
	output=$$($1 2>&1); \
	return_code=$$?; \
	if test $$return_code != "0"; then \
		echo "$1 exited with return code $$return_code \n\n --> $$output\n\n\n\n"; \
		exit 1; \
	else \
		echo "$1 OK"; \
	fi;
endef
test:	$(TESTS_OUT)
	@$(foreach file,$(TESTS_OUT),$(call run-and-check,$(file)))

clean:
	rm -f $(DEPS) $(OBJS) $(CXXDB)

fclean: clean
	rm -f $(NAME)
	rm -f $(EXECS)
	rm -f $(PCMS)
	rm -f $(PCHS)

re: clean all
