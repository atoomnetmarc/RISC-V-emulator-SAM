/*

Copyright Marc Ketel
SPDX-License-Identifier: Apache-2.0

*/

#include <stdbool.h>
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
 * @return true when the address is mapped, false otherwise.
 */
extern inline bool RiscvEmulatorLoad(uint32_t address, void *destination, uint8_t length) {

    if (address >= RAM_ORIGIN) {
        memcpy(destination, &memory[address - RAM_ORIGIN], length);
        return true;
    }

    if (address >= ROM_ORIGIN) {
        memcpy(destination, &firmware[address - ROM_ORIGIN], length);
        return true;
    }

    return false;
}

/**
 * Stores bytes from emulator RAM to RISC-V memory.
 *
 * @param address The byte address in memory.
 * @param destination The destination address to copy the data to.
 * @param length The length in bytes of the data.
 * @return true when the address is mapped, false otherwise.
 */
extern inline bool RiscvEmulatorStore(uint32_t address, const void *source, uint8_t length) {
    if (address >= RAM_ORIGIN) {
        memcpy(&memory[address - RAM_ORIGIN], source, length);
        return true;
    }

    if (address == UART_ORIGIN) {
        const uint8_t *bytes = (const uint8_t *)source;
        for (uint8_t i = 0; i < length; i++) {
            SerialUSB.write(bytes[i]);
        }
        return true;
    }

    return false;
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
 * Handles an ECALL.
 */
extern inline void RiscvEmulatorHandleECALL(RiscvEmulatorState_t *state) {
#if (RVE_E_ZICSR == 1)
    if (state->csr.mtvec.base != 0) {
        return;
    }
#endif

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
