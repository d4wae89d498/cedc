PROJECT_DIR := $(dir $(realpath $(dir $(lastword $(MAKEFILE_LIST)))))

include $(PROJECT_DIR)/common.mk

LIBS_MADE_MARKER := $(PROJECT_DIR)/$(TMP_DIR)/.libs_made

.PHONY: all std_pcm $(wildcard update_*)
all: $(LIBS_MADE_MARKER)

SUBMODULES := 	$(shell cat $(PROJECT_DIR)/third-party/versions.txt)

define update_submodule
	CURRENT_VERSION=$$(cd $(PROJECT_DIR)/third-party/$(1) && git tag -l '$(2).[0-9]*.[0-9]*' --sort=-v:refname | head -n 1); \
	NEW_VERSION=$$(cd $(PROJECT_DIR)/third-party/$(1) && git fetch --tags && git tag -l '$(2).[0-9]*.[0-9]*' --sort=-v:refname | head -n 1); \
	if ! test "$$NEW_VERSION"; then \
		echo "No new version found for $(1) $(2)"; \
		exit 1; \
	elif ! test "$$CURRENT_VERSION"; then \
		echo "No current version found for $(1) $(2). Checking out the new version $$NEW_VERSION"; \
		cd $(PROJECT_DIR)/third-party/$(1) && git checkout tags/$$NEW_VERSION; \
	elif test "$$CURRENT_VERSION" != "$$NEW_VERSION"; then \
		echo "Updating $(1) from $$CURRENT_VERSION to $$NEW_VERSION..."; \
		cd $(PROJECT_DIR)/third-party/$(1) && git checkout tags/$$NEW_VERSION; \
		rm -f $(LIBS_MADE_MARKER); \
	else \
		echo "$(1) is already up-to-date ($$CURRENT_VERSION)";\
	fi;
endef

# Generate individual update rules
define generate_update_rules
$(foreach module_version,$(SUBMODULES),\
	$(eval module=$$(shell echo $(module_version) | cut -d ':' -f 1))\
	$(eval version=$$(shell echo $(module_version) | cut -d ':' -f 2))\
	$(eval update_$(module): ; $$(call update_submodule,$(module),$(version)))\
)
endef
$(eval $(call generate_update_rules))

update_deps:
	@for module_version in $(SUBMODULES); do \
		module=$$(echo $$module_version | cut -d ':' -f 1); \
		version=$$(echo $$module_version | cut -d ':' -f 2); \
		make update_$$module; \
	done

# Build all third party libs
$(LIBS_MADE_MARKER):
	@mkdir -p $(PROJECT_DIR)/$(TMP_DIR)
	@mkdir -p $(PROJECT_DIR)/$(PCM_DIR)
	@cd $(PROJECT_DIR)/third-party/llvm-project \
		&& rm -rf build \
		&& mkdir -p build \
		&& cmake -G Ninja -S runtimes -B build \
			-DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi;libunwind" \
			-DCMAKE_C_COMPILER=$(shell which clang) \
			-DCMAKE_CXX_COMPILER=$(shell which clang++) \
		&& ninja -C build
	@cd $(PROJECT_DIR)/third-party/antlr/runtime/Cpp \
		&& rm -rf build \
		&& mkdir -p build \
		&& cd build \
		&& cmake .. \
			-DCMAKE_CXX_COMPILER=$(shell which clang++) \
			-DCMAKE_CXX_FLAGS="-stdlib=libc++ -I$(LLVM_BUILD_DIR)/include/c++/v1 -I$(LLVM_BUILD_DIR)/include" \
			-DCMAKE_EXE_LINKER_FLAGS="-L$(LLVM_BUILD_DIR)/lib -lc++ -lc++abi -lunwind" \
			-DCMAKE_SHARED_LINKER_FLAGS="-L$(LLVM_BUILD_DIR)/lib -lc++ -lc++abi -lunwind" \
			-DCMAKE_MODULE_LINKER_FLAGS="-L$(LLVM_BUILD_DIR)/lib -lc++ -lc++abi -lunwind" \
			-DCMAKE_BUILD_TYPE=Release \
		&& make
	@make -C $(PROJECT_DIR)/third-party/libastmatcher-parser
	@make -C $(PROJECT_DIR)/third-party/cppmodsort
	@make $(PROJECT_DIR)/$(PCM_DIR)/std.pcm
	@make $(PROJECT_DIR)/$(PCM_DIR)/std.compat.pcm
	@touch $(LIBS_MADE_MARKER)

# Build std.pcm
$(PROJECT_DIR)/$(PCM_DIR)/std.pcm: $(PROJECT_DIR)/third-party/llvm-project/build/modules/c++/v1/std.cppm $(PROJECT_DIR)/common.mk
	$(CXX) $(CXXFLAGS) --precompile -Wno-reserved-module-identifier $< -o $@

# Build std.compat.pcm
$(PROJECT_DIR)/$(PCM_DIR)/std.compat.pcm: $(PROJECT_DIR)/third-party/llvm-project/build/modules/c++/v1/std.compat.cppm $(PROJECT_DIR)/common.mk
	$(CXX) $(CXXFLAGS) --precompile -Wno-reserved-module-identifier $< -o $@
