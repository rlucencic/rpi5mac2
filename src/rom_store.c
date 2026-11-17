#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "emu/emu.h"
#include "emu/log.h"
#include "rom_store.h"

static const char *TAG = "rom";

static const uint32_t sizes[] = { 512 * 1024, 256 * 1024 };

/* The first file in the machine's roms/ folder of that size that `fits` */
static bool from_folder(uint32_t size, uint8_t *buf, bool (*fits)(const uint8_t *buf, void *arg), void *arg,
                        const char *what)
{
    char folder[1200];
    snprintf(folder, sizeof(folder), "%s", emu_rom_dir());
    DIR *dir = opendir(folder);
    if (dir == NULL) {
        return false;
    }
    bool ok = false;
    struct dirent *e;
    while (!ok && (e = readdir(dir)) != NULL) {
        char path[1500];
        struct stat st;
        snprintf(path, sizeof(path), "%s/%s", folder, e->d_name);
        if (e->d_name[0] == '.' || stat(path, &st) != 0 || st.st_size != size) {
            continue;
        }
        FILE *f = fopen(path, "rb");
        if (f == NULL) {
            continue;
        }
        ok = fread(buf, 1, size, f) == size && fits(buf, arg);
        fclose(f);
        if (ok) {
            EMU_LOGI(TAG, "%s from %s", what, path);
        }
    }
    closedir(dir);
    return ok;
}

/* Its checksum names a ROM of the model */
static bool is_model_rom(const uint8_t *buf, void *arg)
{
    mac_model_t model = *(mac_model_t *)arg, found;
    return mac_rom_identify(buf, sizes[model], &found) != NULL && found == model;
}

bool rom_store_load(mac_model_t model, uint8_t *buf, uint32_t *size, const char **name)
{
    if (model > MAC_MODEL_II || !from_folder(sizes[model], buf, is_model_rom, &model, "ROM")) {
        return false;
    }
    *size = sizes[model];
    *name = mac_rom_identify(buf, *size, NULL);
    return true;
}

/* ---- The 8*24 card's declaration ROM: its format block names it ---- */

static bool is_card_rom(const uint8_t *buf, void *arg)
{
    static const uint8_t tail[12] = { 0xD1, 0x62, 0x96, 0x64, 0x03, 0x01, 0x5A, 0x93, 0x2B, 0xC7, 0x00, 0x78 };
    (void)arg;
    return memcmp(buf + MAC_CARD_ROM_SIZE - sizeof(tail), tail, sizeof(tail)) == 0;
}

bool rom_store_load_card(uint8_t *buf)
{
    return from_folder(MAC_CARD_ROM_SIZE, buf, is_card_rom, NULL, "video card ROM");
}
