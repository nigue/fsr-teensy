#pragma once

#include <Arduino.h>
#include <ctype.h>
#include "PadObj.hpp"

class SerialCommand {
public:
    // Constructor con referencia a Pad
    SerialCommand(PadObj& padRef, unsigned long baudRate = 9600) : pad(padRef) {

        Serial.begin(baudRate);

        unsigned long start = millis();
        while (!Serial && (millis() - start < 2000)) {
            ;
        }
    }

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
    PadObj& pad;

    char buffer[8];
    uint8_t index = 0;

    void process(const char* cmd) {
        if (strlen(cmd) != 4) {
            Serial.println("Error formato");
            return;
        }

        char type = cmd[0];

        if (!isdigit(cmd[1]) || !isdigit(cmd[2]) || !isdigit(cmd[3])) {
            Serial.println("Error numeros");
            return;
        }

        int value = (cmd[1] - '0') * 100 +
                    (cmd[2] - '0') * 10 +
                    (cmd[3] - '0');

        switch (type) {
            case 't':
                printThresholds();
                break;
            case 's':
                printSensors();
                break;
            default:
                applyThreshold(type, value);
                break;
        }
    }

    void printThresholds() {
        Serial.print(pad.getLeft().getSensorA().getThreshold());
        Serial.print(",");
        Serial.print(pad.getLeft().getSensorB().getThreshold());

        Serial.print(",");
        Serial.print(pad.getDown().getSensorA().getThreshold());
        Serial.print(",");
        Serial.print(pad.getDown().getSensorB().getThreshold());

        Serial.print(",");
        Serial.print(pad.getUp().getSensorA().getThreshold());
        Serial.print(",");
        Serial.print(pad.getUp().getSensorB().getThreshold());

        Serial.print(",");
        Serial.print(pad.getRight().getSensorA().getThreshold());
        Serial.print(",");
        Serial.println(pad.getRight().getSensorB().getThreshold());
    }

    void printSensors() {
        Serial.print(pad.getLeft().getSensorA().getValue());
        Serial.print(",");
        Serial.print(pad.getLeft().getSensorB().getValue());

        Serial.print(",");
        Serial.print(pad.getDown().getSensorA().getValue());
        Serial.print(",");
        Serial.print(pad.getDown().getSensorB().getValue());

        Serial.print(",");
        Serial.print(pad.getUp().getSensorA().getValue());
        Serial.print(",");
        Serial.print(pad.getUp().getSensorB().getValue());

        Serial.print(",");
        Serial.print(pad.getRight().getSensorA().getValue());
        Serial.print(",");
        Serial.println(pad.getRight().getSensorB().getValue());
    }

    void applyThreshold(char type, int value) {
        PanelObj* panel = nullptr;
        SensorObj* sensor = nullptr;

        switch (type) {
            case 'l': panel = &pad.getLeft();  sensor = &panel->getSensorA(); break;
            case 'L': panel = &pad.getLeft();  sensor = &panel->getSensorB(); break;

            case 'd': panel = &pad.getDown();  sensor = &panel->getSensorA(); break;
            case 'D': panel = &pad.getDown();  sensor = &panel->getSensorB(); break;

            case 'u': panel = &pad.getUp();    sensor = &panel->getSensorA(); break;
            case 'U': panel = &pad.getUp();    sensor = &panel->getSensorB(); break;

            case 'r': panel = &pad.getRight(); sensor = &panel->getSensorA(); break;
            case 'R': panel = &pad.getRight(); sensor = &panel->getSensorB(); break;

            default:
                Serial.println("Error comando");
                return;
        }

        sensor->setThreshold(value);

        Serial.print("OK ");
        Serial.print(type);
        Serial.print(" = ");
        Serial.println(value);
    }
};