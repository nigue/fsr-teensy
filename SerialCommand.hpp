#pragma once

#include <Arduino.h>

class SerialCommand {
public:
    // Inicializar Serial (llamar en setup si quieres)
    static void begin(unsigned long baudRate = 9600) {
        Serial.begin(baudRate);
        while (!Serial) {
            ; // Esperar conexión (útil en Teensy)
        }
    }

    // Procesa comandos de 1 carácter
    static void handle() {
        
        while (Serial.available() > 0) {
            size_t kBufferSize = 64;
            char buffer_[kBufferSize];
            size_t bytes_read = Serial.readBytesUntil('\n', buffer_, kBufferSize - 1);
            buffer_[bytes_read] = '\0';
            if (bytes_read == 0) { return; }
            switch(buffer_[0]) {
                case 't':
                    Serial.println("threshold values");
                    break;

                case 's':
                    Serial.println("sensor values");
                    break;

                default:
                    Serial.print("Error unknown command: ");
                    //Serial.println(buffer_[0]);
                    break;
            }
        }
    }
};
