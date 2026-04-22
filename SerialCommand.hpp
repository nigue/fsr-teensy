#pragma once

#include <Arduino.h>
#include <ctype.h>

class SerialCommand {
public:
    // Constructor
    SerialCommand(unsigned long baudRate = 9600) {
        Serial.begin(baudRate);

        // En Teensy esto es seguro, pero no bloquea infinito
        unsigned long start = millis();
        while (!Serial && (millis() - start < 2000)) {
            ; // esperar máximo 2s
        }
    }

    // Función pública
    void handle() {
        while (Serial.available() > 0) {
            char c = Serial.read();

            if (c == '\n') {
                buffer[index] = '\0';
                process(buffer);
                index = 0;
            } else {
                if (index < sizeof(buffer) - 1) {
                    buffer[index++] = c;
                }
            }
        }
    }

private:
    char buffer[8];   // "t123\0"
    uint8_t index = 0;

    // Función privada
    void process(const char* cmd) {
        if (strlen(cmd) != 4) {
            Serial.println("Error: formato invalido");
            return;
        }

        char type = cmd[0];

        if (!isdigit(cmd[1]) || !isdigit(cmd[2]) || !isdigit(cmd[3])) {
            Serial.println("Error: numeros invalidos");
            return;
        }

        int value = (cmd[1] - '0') * 100 +
                    (cmd[2] - '0') * 10 +
                    (cmd[3] - '0');

        switch (type) {
            case 't':
                Serial.print("threshold: ");
                Serial.println(value);
                break;

            case 's':
                Serial.print("sensor cmd: ");
                Serial.println(value);
                break;

            default:
                Serial.print("Error unknown command: ");
                Serial.println(type);
                break;
        }
    }
};