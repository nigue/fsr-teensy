#!/bin/bash

OUTPUT="project_context.txt"
EXTENSIONS="*.ino *.cpp *.h *.hpp *.c *.md *.txt"

> "$OUTPUT"

echo "Generando contexto del proyecto..."
echo "Salida: $OUTPUT"
echo

find . \
  \( -type d \( -name .git -o -path "./tests/build" -o -path "./tests/third_party" \) -prune \) \
  -o -type f -print0 | \
while IFS= read -r -d '' file; do

    for pattern in $EXTENSIONS; do
        case "$file" in
            $pattern)
                echo "========================================" >> "$OUTPUT"
                echo "Archivo: $file" >> "$OUTPUT"
                echo "========================================" >> "$OUTPUT"
                echo >> "$OUTPUT"
                cat "$file" >> "$OUTPUT"
                echo >> "$OUTPUT"
                break
                ;;
        esac
    done

done

echo "Listo ✅ Archivo generado: $OUTPUT"
