# Ferris

![Ferris, familly pic](https://i.imgur.com/TCjkquRh.jpeg)

A split 34 keys column staggered keyboard named and decorated after the rustlang mascott. All PCB files and some thoughts on the design are available on the [project's github page](https://github.com/pierrechevalier83/ferris)

* Keyboard Maintainer: [Pierre Chevalier](https://github.com/pierrechevalier83)
* Hardware Supported:
	* Ferris 0.1 (With atmega32u4 chip. Comes in 4 variants: base, low, high and compact)
	* Ferris 0.2 (With stm32f072 chip. Comes in 4 variants: bling, mini, high and compact)
	* Ferris sweep (With pro-micro. Comes in a couple of PCB edge cut shapes, but with an identical pinout)

Make examples for this keyboard (after setting up your build environment):

    make ferris/0_1:default
    make ferris/0_2:default
    make ferris/0_2/bling:default
    make ferris/0_2/compact:default
    make ferris/0_2/mini:default
    make ferris/0_2/high:default
    make ferris/sweep:default:avrdude-split-right

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## my notes

i am using the sweep with the blok mcus and with my own keymap.

### build and flash

flash each side independently with the trrs cable disconnected.

For routine updates, enter the Blok bootloader by double-tapping the reset button
within 500 ms. This avoids invalidating saved settings. Holding the top left key
on the left board or the top right key on the right board while plugging in uses
Bootmagic, which invalidates EEPROM configuration and can reset lighting settings.

```sh
make CONVERT_TO=blok ferris/sweep:chadhs:uf2-split-left
make CONVERT_TO=blok ferris/sweep:chadhs:uf2-split-right
```

### updating from upstream

Follow the [personal keyboard maintenance guide](../../docs/chadhs-maintenance.md).
It covers pinned upstream releases, regular merge commits, left/right build-only
commands, saved settings, hardware checks, and rollback.
