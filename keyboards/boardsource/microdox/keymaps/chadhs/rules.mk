OLED_DRIVER_ENABLE = no
RGBLIGHT_ENABLE = yes
COMMAND_ENABLE = no # https://beta.docs.qmk.fm/using-qmk/advanced-keycodes/feature_command
NKRO_ENABLE = no # usb nkey rollover
FORCE_NKRO = no
COMBO_ENABLE = yes
VPATH += keyboards/gboards/ # enables combos.def support
SRC += features/layer_lock.c # https://getreuer.info/posts/keyboards/layer-lock/index.html
