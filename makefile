.DEFAULT_GOAL := default

include common.mk

# Set the libraries to link
THIRD_PARTY_LIBS := third-party/libastmatcher-parser/libastmatcher-parser.a\
 	third-party/antlr/runtime/Cpp/build/runtime/libantlr4-runtime.a\
 	third-party/llvm-project/build/lib/libunwind.a\
 	third-party/llvm-project/build/lib/libc++experimental.a\
 	third-party/llvm-project/build/lib/libc++.a\
 	third-party/llvm-project/build/lib/libc++abi.a

# Compilation database output
CXXDB := 	$(TMP_DIR)/compile_commands.json

# Libraries targets
VENDORS := $(shell find src/module -type d -mindepth 1 -maxdepth 1)
MODULES := $(foreach vendor,$(VENDORS),$(shell find $(vendor) -type d -mindepth 1 -maxdepth 1))
STATIC_LIBS := $(MODULES:$(SRC_MOD_DIR)/%=$(LIB_DIR)/%.a)
DYNAMIC_LIBS := $(MODULES:$(SRC_MOD_DIR)/%=$(LIB_DIR)/%.so)
LIBS := $(STATIC_LIBS) $(DYNAMIC_LIBS)

# Project modules
IFACES := $(shell find src/module -type f -name "*.cppm")
VOID := $(shell make -C ./third-party/cppmodsort/ \
			&& mkdir -p $(DEP_DIR) \
			&& ./third-party/cppmodsort/cppmodsort \
			-m --src-dir src/module/ --pcm-dir tmp/pcm/ $(IFACES) > tmp/dep/module.d)
include tmp/dep/module.d

# Project sources
IMPLS :=	$(shell find src/module -type f -name "*.cpp")

# Project objects
OBJS := 	$(IFACES:$(SRC_MOD_DIR)/%.cppm=$(OBJ_MOD_DIR)/%.cppm.o)\
			$(IMPLS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.cpp.o)\
			$(OBJ_MOD_DIR)/std.compat.cppm.o\
			$(OBJ_MOD_DIR)/std.cppm.o

# Project pre-compiled modules
PCMS := 	$(IFACES:$(SRC_MOD_DIR)/%.cppm=$(PCM_DIR)/%.pcm)

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
DEPS 	:= 	$(MOD_SRCS:$(SRC_DIR)/%=$(DEP_DIR)/%.d) $(IMPLS:$(SRC_DIR)/%=$(DEP_DIR)/%.d)

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

# Generated dependencies
-include $(DEPS)

#-------------------------------------------------#

.SUFFIXES:
.PRECIOUS: 	$(PCHS) $(PCMS) $(LIBS)
.PHONY: 	default all test clean fclean re

all: 	$(THIRD_PARTY_BUILT_MARKER) $(EXECS) $(CXXDB)
re: 	clean all

$(THIRD_PARTY_LIBS): $(THIRD_PARTY_BUILT_MARKER)

#
#	Headers
#

$(PCH_DIR)/%.pch: $(SRC_DIR)/%.hpp makefile third-party/makefile
	@mkdir -p $(@D)
	$(CXX) -x c++-header -DCLANGD $(CXXFLAGS) -o $@ $<

#
#	Interfaces objects
#

$(PCM_DIR)/%.pcm: $(SRC_MOD_DIR)/%.cppm $(PCHS) $(THIRD_PARTY_BUILT_MARKER)
	@mkdir -p $(@D)
	@mkdir -p $(shell dirname $(patsubst $(PCM_DIR)/%.pcm,$(DEP_DIR)/%.cppm.d,$(@)))
	$(CXX) $(CXXFLAGS) -MMD -MF $(patsubst $(PCM_DIR)/%.pcm,$(DEP_DIR)/%.cppm.d,$(@)) --precompile $< -o $@ $(INCPCHS)
	@path="$@"; \
	prefix="$(PCM_DIR)/"; \
	stripped_path=$${path#$${prefix}}; \
	vendor_name=$$(echo "$$stripped_path" | cut -d'/' -f1); \
	package_name=$$(echo "$$stripped_path" | cut -d'/' -f2); \
	module_name=$$(echo "$$stripped_path" | cut -d'/' -f3- | tr '/' '.'); \
	if test "$$module_name"; then\
		dest_pcm=$(PCM_DIR)/$$vendor_name.$$package_name-$$module_name;\
	else\
		dest_pcm=$(PCM_DIR)/$$vendor_name.$$package_name;\
	fi;\
	cp -f $@ "$$dest_pcm"

$(OBJ_MOD_DIR)/%.cppm.o: $(PCM_DIR)/%.pcm
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS)  -c $< -o $@

#
#	Implementation objects
#

$(OBJ_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp $(PCHS) $(PCMS) $(THIRD_PARTY_BUILT_MARKER)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS)  -c $< -o $@ $(INCPCHS)

#
#	Libs
#

$(LIB_DIR)/%.a: $(filter $(OBJ_MOD_DIR)/%,$(OBJS)) $(OBJ_MOD_DIR)/%.cppm.o
	@mkdir -p $(@D)
	ar -rcs $@ $^

$(LIB_DIR)/%.so: $(STATIC_LIBS) $(THIRD_PARTY_LIBS)
	@mkdir -p $(@D)
	$(CXX) -shared -o $@ $^

#
#	Binaries
#

$(BIN_DIR)/%.out: $(SRC_DIR)/%.cpp $(PCHS) $(STATIC_LIBS) $(THIRD_PARTY_LIBS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -o $@ $(INCPCHS) $(STATIC_LIBS) $(THIRD_PARTY_LIBS) -w

#
#	Compilation database
#

$(CXXDB): $(EXECS)
	@make --always-make --dry-run \
	| grep -wE 'clang\+\+' \
	| jq -nR '[inputs | {directory: env.PWD, command: (. + " -DCLANGD") , file: (match("\\S+\\.(cpp|cppm|hpp)(?=\\s|$$)").string)}]' \
	> $(CXXDB)

#
#	Unit tests
#

define run-and-check
	output=$$($1 2>&1); \
	return_code=$$?; \
	if test $$return_code != "0"; then \
		echo "$(RED)$1 exited with return code $$return_code $(RESET) \n\n --> $$output\n\n\n\n"; \
		exit 1; \
	else \
		echo "$(GREEN)$1 OK$(RESET)"; \
	fi;
endef
test:	$(TESTS_OUT)
	@$(foreach file,$(TESTS_OUT),$(call run-and-check,$(file)))

#
#	Cleaning
#

clean:
	rm -f $(DEPS) $(OBJS) $(CXXDB)

fclean: clean
	rm -f $(LIBS)
	rm -f $(EXECS)
	rm -f $(PCMS)
	rm -f $(PCHS)

#################################################
#############|    D E B U G      |###############
#################################################

debug:
	@echo "$(CYAN)=================================================================================$(RESET)"
	@echo "$(CYAN)========================| BUILD SETTINGS |=======================================$(RESET)"
	@echo "$(CYAN)=================================================================================$(RESET)"
	@echo "$(GREEN)Project Root Directory:$(RESET) $(PROJECT_DIR)"
	@echo "$(GREEN)Operating System:$(RESET) $(shell uname -s)"
	@echo "$(GREEN)CPU Cores:$(RESET) $(CPU_CORES)"
	@echo "$(GREEN)Compiler:$(RESET) $(CXX)"
	@echo "$(GREEN)Compiler Flags:$(RESET) $(CXXFLAGS)"
	@echo "$(GREEN)Debug Flags:$(RESET) $(CXXDBGFLAGS)"
	@echo "-----"
	@echo "$(GREEN)Project Directories:$(RESET)"
	@echo "  $(GREEN)Binary Directory [$(BLUE)$(BIN_DIR)$(RESET)$(GREEN)]$(RESET)"
	@echo "  $(GREEN)Library Directory [$(BLUE)$(LIB_DIR)$(RESET)$(GREEN)]$(RESET)"
	@echo "  $(GREEN)Source Directory [$(BLUE)$(SRC_DIR)$(RESET)$(GREEN)]$(RESET)"
	@echo "  $(GREEN)Module Source Directory [$(BLUE)$(SRC_MOD_DIR)$(RESET)$(GREEN)]$(RESET)"
	@echo "  $(GREEN)Temporary Directory [$(BLUE)$(TMP_DIR)$(RESET)$(GREEN)]$(RESET)"
	@echo "  $(GREEN)Object Directory [$(BLUE)$(OBJ_DIR)$(RESET)$(GREEN)]$(RESET)"
	@echo "  $(GREEN)Object Module Directory [$(BLUE)$(OBJ_MOD_DIR)$(RESET)$(GREEN)]$(RESET)"
	@echo "  $(GREEN)PCM Directory [$(BLUE)$(PCM_DIR)$(RESET)$(GREEN)]$(RESET)"
	@echo "  $(GREEN)PCH Directory [$(BLUE)$(PCH_DIR)$(RESET)$(GREEN)]$(RESET)"
	@echo "  $(GREEN)Dependency Directory [$(BLUE)$(DEP_DIR)$(RESET)$(GREEN)]$(RESET)"
	@echo "-----"
	@echo "$(GREEN)Pre-compiled headers [$(BLUE)$(PCH_DIR)$(RESET)$(GREEN)]:$(RESET) $(PCHS)"
	@echo "-----"
	@echo "$(GREEN)Source Implementations [$(BLUE)$(SRC_DIR)$(RESET)$(GREEN)]:$(RESET) $(IMPLS)"
	@echo "-----"
	@echo "$(GREEN)Modules [$(BLUE)$(SRC_MOD_DIR)$(RESET)$(GREEN)]:$(RESET) $(IFACES)"
	@echo "-----"
	@echo "$(GREEN)Pre-compiled modules [$(BLUE)$(SRC_MOD_DIR) -> $(PCM_DIR)$(RESET)$(GREEN)]:$(RESET) $(PCMS)"
	@echo "-----"
	@echo "$(GREEN)Object files [$(BLUE)$(OBJ_DIR)$(RESET)$(GREEN)]:$(RESET) $(OBJS)"
	@echo "-----"
	@echo "$(GREEN)Libraries [$(BLUE)$(LIB_DIR)$(RESET)$(GREEN)]:$(RESET) $(LIBS)"
	@echo "-----"
	@echo "$(GREEN)Executables [$(BLUE)$(BIN_DIR)$(RESET)$(GREEN)]:$(RESET) $(EXECS)"
	@echo "-----"
	@echo "$(GREEN)Third-party Libraries:$(RESET) $(THIRD_PARTY_LIBS)"
	@echo "-----"
	@echo "$(GREEN)Compilation Database Output:$(RESET) $(CXXDB)"
	@echo "$(CYAN)=================================================================================$(RESET)"
	@echo "$(CYAN)======================| END OF BUILD SETTINGS |===================================$(RESET)"
	@echo "$(CYAN)=================================================================================$(RESET)"
