# rpi5mac2

A colour Macintosh LC or Macintosh II for the Raspberry Pi 5, in a window
of its own: [esp32mac2](https://github.com/rlucencic/esp32mac2)'s Mac (with
esp32emu's 68020 and 68881, Musashi) on the
[rpi5emu](https://github.com/rlucencic/rpi5emu) runtime.

- The 68020 (and the II's 68881), 640×480 in 256 colours (or 512×384 in up
  to 32,768 on the LC), up to 10 MB, System 7.5.5, disk images of any size
  in three drives.
- The setup screen (model, memory, monitor, sound, the drives), the web
  page for the disk images (StuffIt, Compact Pro, BinHex and MacBinary
  files become HFS disks in the browser), the console, as the rest of the
  family.

## Building

See [rpi5emu](https://github.com/rlucencic/rpi5emu#building): esp32emu,
rpi5emu, esp32mac2 and rpi5mac2 cloned side by side, then

```sh
cd rpi5mac2 && cmake -S . -B build -G Ninja && cmake --build build
```

## ROMs

The LC's (512 KB) or the II's (256 KB) and, for the II, the Display Card
8•24's declaration ROM (341-0868), in the data folder's `roms/`
(`~/rpi5emu/roms`), under any name (esp32mac2's: `lc.rom`, `ii.rom`,
`mdc824.rom`): they're found by their contents. Not part of this
repository.

## Running

```sh
build/rpi5mac2                              # the setup screen first
build/rpi5mac2 -S --choice "Model=Mac II"
build/rpi5mac2 System755.hda                # with a disk in drive 1
```

Disk images live in `~/rpi5emu/disks/` (shared with rpi5mac and rpi5mac3).
The keyboard by position (US); the mouse after a click in the window.

## Licence

MIT. The web page's converters (esp32mac2's `main/web/macfiles.js`) are
LGPL.
