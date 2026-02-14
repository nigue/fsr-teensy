#!/bin/bash

OUTPUT="project_context.txt"
> "$OUTPUT"

echo "Generando contexto del proyecto..."
echo "Salida: $OUTPUT"
echo

find . \
  \( -type d \( -name .git -o -path "./tests/build" -o -path "./tests/third_party" \) -prune \) \
  -o \( -type f \
        ! -path "./README.md" \
        ! -path "./project_context.txt" \
        \( -name "*.ino" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" -o -name "*.c" -o -name "*.md" -o -name "*.txt" \) \
        -print0 \
     \) | \
while IFS= read -r -d '' file; do

    echo "========================================" >> "$OUTPUT"
    echo "Archivo: ${file#./}" >> "$OUTPUT"
    echo "========================================" >> "$OUTPUT"
    echo >> "$OUTPUT"
    cat "$file" >> "$OUTPUT"
    echo >> "$OUTPUT"

done

echo "Listo ✅ Archivo generado: $OUTPUT"
