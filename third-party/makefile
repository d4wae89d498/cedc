# Root folder
PROJECT_DIR := $(dir $(realpath $(dir $(lastword $(MAKEFILE_LIST)))))

include $(PROJECT_DIR)/common.mk

# Marker file
LIBS_MADE_MARKER := $(PROJECT_DIR)/$(TMP_DIR)/.libs_made

.PHONY: all std_pcm
all: $(LIBS_MADE_MARKER)

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
	@cd $(PROJECT_DIR)/third-party/antlr4/runtime/Cpp \
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
