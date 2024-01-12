#pragma once

// Configure the global tapping term (default: 200ms)
// https://docs.qmk.fm/#/tap_hold?id=tapping-term
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY

// Prevent normal rollover on alphas from accidentally triggering mods.
// https://docs.qmk.fm/#/tap_hold?id=hold-on-other-key-press
#define HOLD_ON_OTHER_KEY_PRESS
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

// Tapping Force Hold is now the default behavior and the timing can be tweaked per key
// https://docs.qmk.fm/#/tap_hold?id=quick-tap-term
#define QUICK_TAP_TERM_PER_KEY

// Allow modifiers to be activated within the typing term
#define PERMISSIVE_HOLD
#define PERMISSIVE_HOLD_PER_KEY

// docs: https://docs.qmk.fm/#/feature_split_keyboard?id=handedness-by-eeprom
#define EE_HANDS

// https://beta.docs.qmk.fm/using-qmk/software-features/feature_combo
#define COMBO_VARIABLE_LEN // http://combos.gboards.ca/docs/install/#combos
#define COMBO_TERM 50 // http://combos.gboards.ca/docs/install/#combos
#define COMBO_ALLOW_ACTION_KEYS
#define COMBO_PERMISSIVE_HOLD

// https://docs.qmk.fm/#/feature_split_keyboard?id=data-sync-options
#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE

// https://docs.qmk.fm/#/feature_rgblight?id=lighting-layers
#define RGBLIGHT_LAYERS

// https://docs.qmk.fm/#/feature_rgblight?id=configuration
// RGBLIGHT_LIMIT_VAL set in info.json in the v1 folder

// https://docs.qmk.fm/#/feature_caps_word?id=customizing-caps-word
#define CAPS_WORD_IDLE_TIMEOUT 3000  // 3 seconds

// fix unresponsiveness after wake
#define USB_SUSPEND_WAKEUP_DELAY 500
