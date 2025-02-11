# Ferris

![Ferris, familly pic](https://i.imgur.com/TCjkquRh.jpeg)

A split 34 keys column staggered keyboard named and decorated after the rustlang mascott. All PCB files and some thoughts on the design are available on the [project's github page](https://github.com/pierrechevalier83/ferris)

* Keyboard Maintainer: [Pierre Chevalier](https://github.com/pierrechevalier83)
* Hardware Supported:
	* Ferris 0.1 (With atmega32u4 chip. Comes in 4 variants: base, low, high and compact)
	* Ferris 0.2 (With stm32f072 chip. Comes in 4 variants: bling, mini, high and compact)
	* Ferris sweep (With pro-micro. Comes in a couple of PCB edge cuts shapes, but with identical pinout)
* Hardware Availability: [Cuddly Keyboards](https://cuddlykeyboards.com)

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

hold the top left most key on the left board or the top right most key on the right board while plugging in the side.

```sh
make CONVERT_TO=blok ferris/sweep:chadhs:uf2-split-left
make CONVERT_TO=blok ferris/sweep:chadhs:uf2-split-right
```

### updating from upstream

review latest release tags: https://github.com/qmk/qmk_firmware/tags

review breaking changes: https://docs.qmk.fm/breaking_changes_history

create a new feature branch and name it YYYY-MM-DD-reconcile-upstream

fetch and merge the tag commits into your reconcile feature branch
```sh
git fetch upstream tag 0.27.12
git merge FETCH_HEAD
```

run qmk setup and qmk doctor and address any output there
