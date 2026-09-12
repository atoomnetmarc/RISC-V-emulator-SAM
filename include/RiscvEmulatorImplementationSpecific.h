/*

Copyright Marc Ketel
SPDX-License-Identifier: Apache-2.0

*/

#include <string.h>

#include <RiscvEmulatorDefine.h>
#include <RiscvEmulatorType.h>

#include "firmware.h"
#include "memory.h"

#ifndef RiscvEmulatorImplementationSpecific_H_
#define RiscvEmulatorImplementationSpecific_H_

/**
 * Loads bytes from RISC-V memory in emulator RAM.
 *
 * @param address The byte address in memory.
 * @param destination The destination address to copy the data to.
 * @param length The length in bytes of the data.
 */
extern inline void RiscvEmulatorLoad(uint32_t address, void *destination, uint8_t length) {

    if (address >= RAM_ORIGIN) {
        memcpy(destination, &memory[address - RAM_ORIGIN], length);
        return;
    }

    if (address >= ROM_ORIGIN) {
        memcpy(destination, &firmware[address - ROM_ORIGIN], length);
        return;
    }
}

/**
 * Stores bytes from emulator RAM to RISC-V memory.
 *
 * @param address The byte address in memory.
 * @param destination The destination address to copy the data to.
 * @param length The length in bytes of the data.
 */
extern inline void RiscvEmulatorStore(uint32_t address, const void *source, uint8_t length) {
    if (address >= RAM_ORIGIN) {
        memcpy(&memory[address - RAM_ORIGIN], source, length);
        return;
    }

    if (address == UART_ORIGIN) {
        for (uint8_t i = 0; i < length; i++) {
            SerialUSB.write(*(uint8_t *)(source + i));
        }
    }
    return;
}

/**
 * Handles a fault where the instruction is somehow not recognized.
 *
 * Something wrong happened at the current programcounter.
 * Use a listing file of the risc-v program to better understand the wrong.
 * The failed machine instruction is found in state.instruction.value.
 */
extern inline void RiscvEmulatorIllegalInstruction(RiscvEmulatorState_t *state) {
    for (;;) {
    };
}

/**
 * Handles a fault where the CSR is not recognized.
 */
extern inline void RiscvEmulatorUnknownCSR(RiscvEmulatorState_t *state) {
    for (;;) {
    };
}

/**
 * Handles an ECALL.
 */
extern inline void RiscvEmulatorHandleECALL(RiscvEmulatorState_t *state) {
    for (;;) {
    };
}

/**
 * Handles an EBREAK.
 */
extern inline void RiscvEmulatorHandleEBREAK(RiscvEmulatorState_t *state) {
    for (;;) {
    };
}
#endif
