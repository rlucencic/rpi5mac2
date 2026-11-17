#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "mac.h"

#define ROM_MAX_SIZE    (512 * 1024)

/* Load the ROM for `model` into buf (ROM_MAX_SIZE bytes): a file in the
 * machine's roms/ folder (any name) whose checksum is a ROM of that model (the
 * boards also read flash partitions). Its size in *size, its name in *name.
 */
bool rom_store_load(mac_model_t model, uint8_t *buf, uint32_t *size, const char **name);

/* The Mac II's video card ROM, the Display Card 8*24's (MAC_CARD_ROM_SIZE
 * bytes): a file in the machine's roms/ folder (any name) that is one
 */
bool rom_store_load_card(uint8_t *buf);
