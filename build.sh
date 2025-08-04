#!/bin/bash
set -e

BUILD_DIR="build"

if [[ "$1" == "clean" ]]; then
  echo "🧹 清理构建目录：$BUILD_DIR"
  rm -rf "$BUILD_DIR"
  exit 0
fi

echo "📁 创建构建目录：$BUILD_DIR"
cmake -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Debug

echo "🛠️  编译项目（Debug 模式）..."
cmake --build "$BUILD_DIR" --target momo  # 注意：改为 momo 而非 calendar

echo "📦 安装可执行文件到系统..."
cmake --install "$BUILD_DIR" --prefix ~/.local

echo "✅ 构建完成，执行文件位于：/usr/local/bin/momo"

