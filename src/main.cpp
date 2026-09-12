/*

Copyright Marc Ketel
SPDX-License-Identifier: Apache-2.0

*/

#include <Arduino.h>
#include <Wire.h>

#include <RiscvEmulator.h>

#include "memory.h"

uint8_t memory[MEMORY_SIZE];

void HardFault_Handler(void) {
#if defined DEBUG
    __BKPT(3);
#endif
    NVIC_SystemReset();
    for (;;) {
    }
}

RiscvEmulatorState_t RiscvEmulatorState;

void setup() {
    pinMode(4, OUTPUT); // PA14
    pinMode(5, OUTPUT); // PA15
    digitalWrite(5, LOW);

    SerialUSB.begin(115200);

    RiscvEmulatorInit(&RiscvEmulatorState, sizeof(memory));
}

void loop() {
    for (;;) {
        digitalWrite(4, !digitalRead(4));

        RiscvEmulatorLoop(&RiscvEmulatorState);
    }
}
