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
CXXFLAGS =	-g -nostdinc++ -fprebuilt-module-path=lib/libcxx-pcm/lib -Wno-unqualified-std-cast-call -fprebuilt-module-path=$(PCM_DIR)
#				$(shell find $(PCM_DIR) -type d | sed 's/^/-fprebuilt-module-path=/' | tr '\n' ' ')

CXXDB := 	compile_commands.json

# Project modules interfaces

MODULES := 	ucbl/cedilla/common.hppm\
			ucbl/cedilla/clonable.hppm\
			ucbl/cedilla/serializable.hppm\
			ucbl/cedilla/linked_list/linked_list.hppm\
			ucbl/cedilla/tree/tree.hppm\
			ucbl/cedilla/box/box.hppm\
			ucbl/cedilla/class_registry/class_registry.hppm\
			ucbl/cedilla/ast/ast.hppm\
			ucbl/cedilla.hppm

MODULES := 	$(MODULES:%=$(MOD_DIR)/%)
OBJS := 	$(MODULES:$(SRC_DIR)/%.hppm=$(OBJ_DIR)/%.hppm.o)
PCMS := 	$(MODULES:$(SRC_DIR)/%.hppm=$(PCM_DIR)/%.pcm)

# Project modules implementations

IMPLS :=	$(shell find "src/module" -type f -name "*.cppm")

OBJS :=		$(OBJS) $(IMPLS:$(SRC_DIR)/%.cppm=$(OBJ_DIR)/%.cppm.o)

# Project library
NAME :=		$(LIB_DIR)/libcedilla.a

# Project executables
MAINS :=	cli/main.cpp\
			\
			test/ast.cpp\
			test/linked_list.cpp\
			test/tree.cpp

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

-include $(DEPS)

$(PCM_DIR)/%.pcm: $(SRC_DIR)/%.hppm $(PCHS)
	@mkdir -p $(@D)
	@mkdir -p $(shell dirname $(patsubst $(PCM_DIR)/%.pcm,$(DEP_DIR)/%.hppm.d,$(@)))
	$(CXX) -x c++-module $(CXXFLAGS) -MMD -MF $(patsubst $(PCM_DIR)/%.pcm,$(DEP_DIR)/%.hppm.d,$(@)) --precompile $< -o $@ $(INCPCHS)
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

$(OBJ_DIR)/%.hppm.o: $(PCM_DIR)/%.pcm
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS)  -c $< -o $@

debug:
	echo IMPLS : $(IMPLS)
	echo "---"
	echo PCMS : $(PCMS)
	echo "---"
	echo OBJS : $(OBJS)

$(OBJ_DIR)/%.cppm.o: $(SRC_DIR)/%.cppm
	@mkdir -p $(@D)
	@mkdir -p $(shell dirname $(patsubst $(OBJ_DIR)/%.cppm.o,$(DEP_DIR)/%.cppm.d,$(@)))
	$(CXX) -x c++-module $(CXXFLAGS) -MMD -MF $(patsubst $(OBJ_DIR)/%.cppm.o,$(DEP_DIR)/%.cppm.d,$(@))  -c $< -o $@ $(INCPCHS)

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
	| jq -nR '[inputs | {directory: env.PWD, command: (. + " -DCLANGD") , file: (match("\\S+\\.(cpp|cppm|hppm)").string)}]' \
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
