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
CXXFLAGS =	-g -nostdinc++ -nostdlib++ -fprebuilt-module-path=lib/libcxx-pcm/lib -Wno-unqualified-std-cast-call -fprebuilt-module-path=$(PCM_DIR)
#				$(shell find $(PCM_DIR) -type d | sed 's/^/-fprebuilt-module-path=/' | tr '\n' ' ')

CXXDB := 	$(TMP_DIR)/compile_commands.json

# Project modules

MODULES := 	ucbl/cedilla/common.cppm\
			ucbl/cedilla/scan/scan.cppm\
			ucbl/cedilla/clonable.cppm\
			ucbl/cedilla/serializable.cppm\
			ucbl/cedilla/state.cppm\
			ucbl/cedilla/state_array/state_array.cppm\
			ucbl/cedilla/state_map/state_map.cppm\
			ucbl/cedilla/class_registry/class_registry.cppm\
			ucbl/cedilla/state_registry/state_registry.cppm\
			ucbl/cedilla/linked_list_node/linked_list_node.cppm\
			ucbl/cedilla/linked_list/linked_list.cppm\
			ucbl/cedilla/tree_node.cppm\
			ucbl/cedilla/ast_node/ast_node.cppm\
			ucbl/cedilla/ast_node_registry/ast_node_registry.cppm\
			\
			ucbl/cedilla.cppm


MODULES := 	$(MODULES:%=$(MOD_DIR)/%)

IMPLS :=	$(shell find src/module -type f -name "*.cpp")\

#IMPLS := 	$(IMPLS:%=$(MOD_DIR)/%)

OBJS := 	$(MODULES:$(SRC_DIR)/%.cppm=$(OBJ_DIR)/%.cppm.o)\
			$(IMPLS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.cpp.o)

PCMS := 	$(MODULES:$(SRC_DIR)/%.cppm=$(PCM_DIR)/%.pcm)

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
LIBCXX_MADE_MARKER=$(TMP_DIR)/.libcxx_made

#-------------------------------------------------#

.SUFFIXES:
.PRECIOUS: 	$(PCHS) $(PCMS)
.PHONY: 	all clean fclean re

all: $(LIBCXX_MADE_MARKER) $(NAME) $(EXECS)

$(LIBCXX_MADE_MARKER):
	make -C lib/libcxx-pcm
	@mkdir -p $(@D)
	@ln -sf $(shell pwd)/lib/libcxx-pcm/lib/libcxx.a lib/libcxx.a
	@touch $(LIBCXX_MADE_MARKER)

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
	$(CXX) $(CXXFLAGS) $< -o $@ $(INCPCHS) $(NAME) lib/libcxx.a -w
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
	rm -f $(LIBCXX_MADE_MARKER)
	make fclean -C lib/libcxx-pcm

re: fclean all
