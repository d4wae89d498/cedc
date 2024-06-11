# Root folder
PROJECT_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))

# Project structure
BIN_DIR := bin
LIB_DIR := lib
SRC_DIR := src
TMP_DIR := tmp

# Src subdirs
MOD_DIR := $(SRC_DIR)/module

# Tmp subdirs
OBJ_DIR := $(TMP_DIR)/obj
PCM_DIR := $(TMP_DIR)/pcm
PCH_DIR := $(TMP_DIR)/pch
DEP_DIR := $(TMP_DIR)/dep

# C++ settings
CXX := clang++ -std=c++26
CXXFLAGS := -g \
			-O0 \
			-fsanitize=address \
			-nostdinc++ \
			-nostdlib++ \
			-I$(PROJECT_DIR)/third-party/llvm-project/build/include/c++/v1 \
			-Wno-unqualified-std-cast-call \
			-fprebuilt-module-path=$(PROJECT_DIR)/$(TMP_DIR)/pcm \
			-I$(PROJECT_DIR)/third-party/antlr/runtime/Cpp/runtime/src \
			-I$(PROJECT_DIR)/third-party/libastmatcher-parser \
			-Wno-unused-command-line-argument \
			-Wreserved-module-identifier

# Avoid llvm-libcxx iostream ABI error on macos (https://github.com/frida/frida-gum/issues/694)
ifeq ($(shell uname -s), Darwin)
	CXXFLAGS += -target x86_64-apple-macos10.9
endif

LIBS := third-party/libastmatcher-parser/libastmatcher-parser.a\
 	third-party/antlr/runtime/Cpp/build/runtime/libantlr4-runtime.a\
 	third-party/llvm-project/build/lib/libunwind.a\
 	third-party/llvm-project/build/lib/libc++experimental.a\
 	third-party/llvm-project/build/lib/libc++.a\
 	third-party/llvm-project/build/lib/libc++abi.a
