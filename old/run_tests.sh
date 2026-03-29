#!/usr/bin/env bash
set -e

echo "🔨 Compilando tests..."

g++ -std=c++17 \
  -I src \
  -I tests \
  tests/test_PadConfigRepository.cpp \
  src/repository/PadConfigRepository.cpp \
  -o tests/build/test_padconfig

echo "▶️ Ejecutando tests..."
./tests/build/test_padconfig -s

echo "✅ Tests finalizados"
