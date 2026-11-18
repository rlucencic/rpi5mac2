# sdlmac2: the Macintosh LC and II on Linux and macOS through SDL 3

esp32mac2's Mac (`../esp32mac2/components/mac2`, platform independent) on
the sdlemu runtime (`../sdlemu`, its CLAUDE.md: the workflow, the Pi, the
lessons), the 68020 and 68881 (Musashi, `M68K_68020`) esp32emu's. The
machine's own behaviour, lessons and tests are esp32mac2's CLAUDE.md; this
project is the glue.

## Layout

| Path | What |
|---|---|
| `src/main.c` | The Mac as an `emu_machine_t`: esp32mac2's `main/main.c` through `../sdlemu/tools/port_glue.py` and `port_finish.py`, then by hand: up to 10 MB, no opcode table copies (sdlste's lesson), the ROM messages, the web script built in, `shutdown()` saves the PRAM |
| `src/settings.c` | esp32mac2's, over `emu/nvs.h` (section `mac2`, each model's PRAM as hex) |
| `src/rom_store.c` | A file of the model's ROM size in `~/sdlemu/mac/roms/` (`emu_rom_dir()`: the three Macs share it) whose checksum names that model, and the 8*24 card's ROM by its format block (any names) |
| `CMakeLists.txt` | `M68K_68020` for the whole target (Musashi's too); `sdlemu_embed()` builds in esp32mac2's `main/web/macfiles.js` (LGPL) |

Keep `src/main.c` in step with esp32mac2's `main/main.c`.

## Build, run, check

```sh
../sdlemu/tools/pi.sh sdlmac2 build
../sdlemu/tools/pi.sh sdlmac2 headless     # or run: the window here
../sdlemu/tools/console.sh i c
../sdlemu/tools/pi.sh sdlmac2 shot out.png
```

Console: the runtime's (`h`) and esp32mac2's: `k <hex>`, `K <hex> 0|1`,
`m <dx> <dy> <btn>`, `P <x> <y> <btn>` the pointer at a screen position,
`R <model> <MB> [m]`, `n` the programmer's interrupt switch.

Checked on the Pi (2026-11-15, headless): the LC (4 MB) and the II (4 MB,
the 8*24 card) at 100%, 60 frames a second, to the disk icon asking for a
system disk (~20 s: the memory test). Not yet: System 7 from a disk (none
here), the window by hand, sound heard, the mouse, 10 MB.
