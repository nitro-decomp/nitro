# NitroSDK Decompilation
**Work in progress!** This project aims to recreate source code for NitroSDK. The repository does not contain any of the original objects, nor does it make use of any leaked source material. To work on this project, you must own one of the supported games to extract code from.

## Setup
1. Place a supported base ROM into the [`extract/`](/extract/). The list of supported games is in [`extract/README.md`](/extract/).
2. Run `python tools/configure.py <game_name>` to set up the Ninja build system. Replace `<game_name>` with the base ROM's file name without the file extension, e.g. `pm4_jp`.
3. Run `ninja objdiff` to create an `objdiff.json` file and start decompiling.
