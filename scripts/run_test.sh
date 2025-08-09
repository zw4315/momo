#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
BUILD_DIR="$ROOT_DIR/build"
LOG_DIR="$ROOT_DIR/test_logs"

mkdir -p "$LOG_DIR"

cmake -S "$ROOT_DIR" -B "$BUILD_DIR" -DBUILD_TESTING=ON
cmake --build "$BUILD_DIR" --parallel

# 生成时间戳文件名
LOG_FILE="$LOG_DIR/test_$(date +%F_%H-%M-%S).log"

# 同时输出到终端和文件
ctest --test-dir "$BUILD_DIR" --output-on-failure 2>&1 | tee "$LOG_FILE"

echo "测试结果已保存到: $LOG_FILE"

