PROJECT_DIR := $(dir $(realpath $(dir $(lastword $(MAKEFILE_LIST)))))
LLVM_BUILD_DIR := $(PROJECT_DIR)/third-party/llvm-project/build

include $(PROJECT_DIR)/common.mk

.PHONY: build_deps $(wildcard update_*) clean_deps build_std_pcm

THIRD_PARTY_BUILT_MARKER := $(PROJECT_DIR)/$(TMP_DIR)/.marker/third_party
all:  $(THIRD_PARTY_BUILT_MARKER)

# Build LLVM
LLVM_BUILT_MARKER := $(PROJECT_DIR)/$(TMP_DIR)/.marker/llvm
$(LLVM_BUILT_MARKER):
	@mkdir -p $(PROJECT_DIR)/$(TMP_DIR)/.marker
	@cd $(PROJECT_DIR)/third-party/llvm-project \
		&& rm -rf build \
		&& mkdir -p build \
		&& cmake -G Ninja -S runtimes -B build \
			-DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi;libunwind" \
			-DCMAKE_C_COMPILER=$(shell which clang) \
			-DCMAKE_CXX_COMPILER=$(shell which clang++) \
		&& ninja -C build
	@make build_std_pcm
	@touch $(LLVM_BUILT_MARKER)
build_llvm: $(LLVM_BUILT_MARKER)

# Build ANTLR
ANTLR_BUILT_MARKER := $(PROJECT_DIR)/$(TMP_DIR)/.marker/antlr
$(ANTLR_BUILT_MARKER): $(LLVM_BUILT_MARKER)
	@mkdir -p $(PROJECT_DIR)/$(TMP_DIR)/.marker
	@cd $(PROJECT_DIR)/third-party/antlr/runtime/Cpp \
		&& rm -rf build \
		&& mkdir -p build \
		&& cd build \
		&& export DYLD_LIBRARY_PATH=$(LLVM_BUILD_DIR)/lib \
		&& export LD_LIBRARY_PATH=$(LLVM_BUILD_DIR)/lib \
		&& cmake .. \
			-DCMAKE_C_COMPILER=$(shell which clang) \
			-DCMAKE_CXX_COMPILER=$(shell which clang++) \
			-DCMAKE_CXX_FLAGS="$(CXXFLAGS)" \
			-DCMAKE_EXE_LINKER_FLAGS="-L$(LLVM_BUILD_DIR)/lib -lc++ -lc++abi -lunwind" \
			-DCMAKE_SHARED_LINKER_FLAGS="-L$(LLVM_BUILD_DIR)/lib -lc++ -lc++abi -lunwind" \
			-DCMAKE_MODULE_LINKER_FLAGS="-L$(LLVM_BUILD_DIR)/lib -lc++ -lc++abi -lunwind" \
			-DCMAKE_BUILD_TYPE=Release \
		&& make
	@touch $(ANTLR_BUILT_MARKER)
build_antlr: $(ANTLR_BUILT_MARKER)

# Build all third party libs
$(THIRD_PARTY_BUILT_MARKER):
	make $(LLVM_BUILT_MARKER)
	make $(ANTLR_BUILT_MARKER)
	@make -C $(PROJECT_DIR)/third-party/libastmatcher-parser
	@make -C $(PROJECT_DIR)/third-party/cppmodsort
	@touch $(THIRD_PARTY_BUILT_MARKER)
build_deps: $(THIRD_PARTY_BUILT_MARKER)
clean_deps:
	rm -f $(THIRD_PARTY_BUILT_MARKER)
	make clean -C third-party/cppmodsort
	make clean -C third-party/libastmatcher-parser
	rm -rf third-party/runtime/Cpp/build
	rm -rf third-party/llvm-project/build

# Build std.pcm
$(PROJECT_DIR)/$(PCM_DIR)/std.pcm: $(PROJECT_DIR)/third-party/llvm-project/build/modules/c++/v1/std.cppm $(PROJECT_DIR)/common.mk
	@mkdir -p $(PROJECT_DIR)/$(PCM_DIR)
	$(CXX) $(CXXFLAGS) --precompile -Wno-reserved-module-identifier $< -o $@

# Build std.compat.pcm
$(PROJECT_DIR)/$(PCM_DIR)/std.compat.pcm: $(PROJECT_DIR)/third-party/llvm-project/build/modules/c++/v1/std.compat.cppm $(PROJECT_DIR)/common.mk
	@mkdir -p $(PROJECT_DIR)/$(PCM_DIR)
	$(CXX) $(CXXFLAGS) --precompile -Wno-reserved-module-identifier $< -o $@

# Build both
build_std_pcm:
	make $(PROJECT_DIR)/$(PCM_DIR)/std.pcm
	make $(PROJECT_DIR)/$(PCM_DIR)/std.compat.pcm

# Submodules updater
define update_submodule
	@CURRENT_VERSION=$$(cd $(PROJECT_DIR)/third-party/$(1) && git tag -l '$(2).[0-9]*.[0-9]*' --sort=-v:refname | head -n 1); \
	NEW_VERSION=$$(cd $(PROJECT_DIR)/third-party/$(1) && git fetch --tags && git tag -l '$(2).[0-9]*.[0-9]*' --sort=-v:refname | head -n 1); \
	if ! test "$$NEW_VERSION"; then \
		echo "No new version found for $(1) $(2)"; \
		exit 1; \
	elif ! test "$$CURRENT_VERSION"; then \
		echo "No current version found for $(1) $(2). Checking out the new version $$NEW_VERSION"; \
		cd $(PROJECT_DIR)/third-party/$(1) && git checkout tags/$$NEW_VERSION; \
		echo $$NEW_VERSION > $(PROJECT_DIR)/third-party/.versions/$(1); \
		rm -f $(THIRD_PARTY_BUILT_MARKER); \
	elif test "$$CURRENT_VERSION" != "$$NEW_VERSION"; then \
		echo "Updating $(1) from $$CURRENT_VERSION to $$NEW_VERSION..."; \
		cd $(PROJECT_DIR)/third-party/$(1) && git checkout tags/$$NEW_VERSION; \
		echo $$NEW_VERSION > $(PROJECT_DIR)/third-party/.versions/$(1); \
		rm -f $(THIRD_PARTY_BUILT_MARKER); \
	else \
		echo "$(1) is already up-to-date ($$CURRENT_VERSION)";\
		echo $$CURRENT_VERSION > $(PROJECT_DIR)/third-party/.versions/$(1); \
	fi;
endef

update_antlr:
	$(call update_submodule,antlr,4)

update_llvm:
	$(call update_submodule,llvm-project,llvmorg-18)

update_deps:
	make update_antlr
	make update_llvm
