# What is this?

This is the little brother of [RISC-V-emulator-AVR](https://github.com/atoomnetmarc/RISC-V-emulator-AVR): a project that uses my [RISC-V emulator library](https://github.com/atoomnetmarc/RISC-V-emulator) and runs on an ARM Cortex-M0+ microcontroller, specifically the [Adafruit Metro M0 Express](https://www.adafruit.com/product/3505) (SAMD21) compatible board.

The purpose is simple: prove that the same RISC-V emulator that runs on an 8-bit AVR also runs on a Cortex-M0. No external RAM, no SPI flash, no SD-card, no display. Just the microcontroller and its internal SRAM.

# Memory layout

Everything fits in the internal SRAM of the SAMD21. The RISC-V firmware is linked into the flash of the microcontroller as a byte array ([src/firmware.c](src/firmware.c)) and the emulated RAM is a plain 8 KiB array ([include/memory.h](include/memory.h)).

| Name | Address    | Length | Note                                        |
| ---- | ---------- | ------ | ------------------------------------------- |
| UART | 0x10000000 |        | Writes are forwarded to the native USB CDC. |
| ROM  | 0x20000000 |        | Compiled-in firmware array.                 |
| RAM  | 0x80000000 | 8 KiB  | Internal SRAM.                              |

# How to make RV32I programs?

Compile a RV32I program using gcc.

| Setting | Value  |
| ------- | ------ |
| mabi    | ilp32  |
| march   | rv32i  |
| mcmodel | medlow |

Link it at the ROM origin (0x20000000) with entry at 0x0, then convert the binary to a C array and place it in [src/firmware.c](src/firmware.c).

# How does to make it work?

Compile this code into firmware using PlatformIO (on Visual Studio Code). The `[env:mzeroUSB]` environment in [platformio.ini](platformio.ini) builds the emulator for the Metro M0 with the M, A and Zicsr extensions enabled.

Upload the firmware using an ATMEL-ICE (`upload_protocol = atmel-ice`) or any other supported uploader for the board.

Power-on the board and open a serial monitor on the native USB port (115200 8N1). The emulator starts executing code at address 0x0 in the compiled-in ROM at virtual address 0x20000000, and anything the RISC-V program writes to the UART appears on the USB serial port.

# License

I license my code Apache License, Version 2.0.

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
