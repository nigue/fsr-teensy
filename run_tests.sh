#!/usr/bin/env bash
set -e

echo "🔨 Compilando tests..."

g++ -std=c++17 \
  -I src \
  -I tests \
  tests/test_PadConfigRepository.cpp \
  src/repository/PadConfigRepository.cpp \
  -o tests/bulid/test_padconfig

echo "▶️ Ejecutando tests..."
./tests/bulid/test_padconfig -s

echo "✅ Tests finalizados"
