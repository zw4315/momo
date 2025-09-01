#!/usr/bin/env bash
set -e

# 脚本当前目录
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# 项目根目录
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
BUILD_DIR="$ROOT_DIR/build"
echo "BUILD_DIR = $BUILD_DIR"
# export LLVM_PREFIX="$(brew --prefix llvm)"
export LLVM_PREFIX="/usr"
cmake -S "$ROOT_DIR" -B "$BUILD_DIR" \
  -DCMAKE_C_COMPILER="$LLVM_PREFIX/bin/clang" \
  -DCMAKE_CXX_COMPILER="$LLVM_PREFIX/bin/clang++" \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build -j