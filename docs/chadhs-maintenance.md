# Personal keyboard maintenance

Preserve the behavior of `boardsource/microdox/v1:chadhs` and
`ferris/sweep:chadhs CONVERT_TO=blok` when updating QMK. A passing build is only
the software gate. Each physical keyboard must pass the hardware checklist
before a release is marked validated.

## November 2026 reconciliation

- Source baseline: `ed31fd69ec82c7578cb28bd5e0927772e31dfb6d`, the April 23 sync
  incorporating upstream 0.32.12. Backup branch:
  `backup/2026-11-15-before-qmk-0.34.8`.
- Update target: QMK `0.34.8`, commit
  `ec8a1b6549` including the ChibiOS USB control OUT buffer fix.
- Reconciliation branch: `2026-11-15-reconcile-upstream`.
- Local archive: `../qmk_firmware-backups/2026-11-15-reconcile-0.34.8/`.
  `existing-firmware/` preserves the preexisting binaries with SHA-256 hashes;
  their original build settings and whether they are currently flashed are not
  established. `baseline-builds/` contains fresh builds of the source baseline.
  `updated-builds/` contains candidate firmware, generated settings, and logs.
- Hardware acceptance is pending. No firmware was flashed during reconciliation.

The April sync was squash-merged. Its preserved `codex/qmk-2026-sync` branch had
an identical tree, so merging that branch restored ancestry without changing
files. The next merge integrated 0.34.8 with its exact dependency revisions,
including ChibiOS, ChibiOS-Contrib, Pico SDK, and googletest.

The cleanup reconciled 104 differences whose blobs matched historical upstream
content, plus stale edits to the merge-conflict tutorial, `tbkmini/info.json`,
the docs and VIA conversion CLI commands, an unused core include, and Microdox
whitespace. These changes restore the upstream versions or upstream deletions;
they are not new keyboard features. The archive records the reviewed paths in
`historical-upstream-leftovers.txt` and `differences-to-review.txt`.

Personal changes are limited to the two `chadhs` keymaps, Microdox's feature
overrides and saved VIA files, personal documentation, and the existing local
tool settings. The saved VIA files are retained for reference; neither active
`chadhs` build enables VIA. QMK core, drivers, build tooling, and submodule pins
match the pinned upstream release.

## Behavior to preserve

| Setting | Microdox v1 | Sweep with Blok |
| --- | --- | --- |
| Layout | Five existing layers; outer thumb keys unused | Same five functional layers with four thumb keys |
| Tap and hold | 200 ms base, 275 ms for the eight home-row mods | Same |
| Quick tap | 150 ms for number/backspace, function/space, command/enter; existing defaults elsewhere | Same |
| Combos | All 18 entries, 50 ms term, existing action-key behavior | Same |
| Caps Word | Existing continuation rules, 3-second timeout | Same |
| Lighting | 12 LEDs, 6 per side, D3, brightness limit 150 | 2 controller LEDs, 1 per side, GP25, brightness limit 72 |
| Lighting states | Existing white base, blue gaming, green caps, orange anti-idle layers and their priority | Same colors and priority |
| KVM double taps | Right Ctrl, Right Ctrl, port 1–4, with 100 ms delays | Same sequence plus Enter |
| KVM single taps | KVM 1–4 emit A/R/S/T | Same |
| Anti-idle | Z on the existing 30-second timer when enabled | X on the existing 30-second timer when enabled |
| USB and split | NKRO disabled, 500 ms wake delay, EEPROM handedness, matrix/layer/LED synchronization | Same |
| Board-specific behavior | Bit-C status LED off; Bootmagic, OLED, mouse keys disabled | Blok converter and Bootmagic retained |

Do not enable new tap-hold algorithms, unify the two KVM sequences, alter RGB
layers, or reset EEPROM as incidental cleanup. Move the Microdox feature
overrides from its shared `info.json` into keymap configuration only in a separate
change with equivalent generated settings verified.

The inherited Microdox build uses `BOOTLOADER=caterina`, while the personal
flashing notes use DFU and the keymap controls a Bit-C LED. Confirm the physical
controller and bootloader before flashing. This update keeps the inherited
setting; build success does not resolve that discrepancy.

## Repeatable upstream update

1. Start with a clean checkout. Archive existing `.hex`, `.uf2`, and `.bin` files
   outside the repository before running any build or clean command. Record
   `git rev-parse HEAD`, `git submodule status`, `qmk doctor`, compiler versions,
   the exact build commands, and SHA-256 hashes. Preserve a dated backup ref.
   A Git ref alone does not save ignored firmware files or settings on hardware.
2. Create a dated reconciliation branch from the current personal branch. Fetch
   upstream tags, choose a reviewed stable tag, and read every intervening
   breaking-change changelog. Merge that tag with `git merge --no-ff <tag>`.
   Resolve submodules to the release's pins and run
   `git submodule update --init --recursive`; do not update them to arbitrary
   newest revisions. Inspect `git diff <tag>` to explain every remaining fork
   difference.
3. Build both baseline and candidate targets in clean build directories. Compare
   generated `info_config.h`, `info_rules.mk`, layouts, enabled features, custom
   source, and flash sizes. Retain firmware and build logs separately for each
   version. Run strict lint and the relevant input regression suites below.
4. Confirm the baseline behavior on hardware, then test one complete keyboard
   while keeping the other usable. Complete the checklist below. Preserve saved
   lighting configuration and handedness. Roll back the entire keyboard if a
   regression appears.
5. After hardware acceptance, merge the reconciliation branch with a regular
   merge commit, preserving upstream ancestry. Do not squash or rebase-merge the
   sync PR. Tag the hardware-validated commit and archive its firmware, commands,
   dependency pins, checksums, and checklist results for the next update.

Release tags: https://github.com/qmk/qmk_firmware/tags

Breaking changes: https://docs.qmk.fm/breaking_changes_history

## Software checks

These commands build and test only; none flashes a keyboard. Archive outputs
before `make clean` and before producing a different handedness variant.

```sh
qmk doctor
qmk lint -kb boardsource/microdox/v1 -km chadhs --strict
qmk lint -kb ferris/sweep -km chadhs --strict
make clean
make boardsource/microdox/v1:chadhs -j4
make CONVERT_TO=blok ferris/sweep:chadhs -j4
```

Input suites used for this reconciliation:

```sh
make test:combo test:combo/combo_repress \
  test:caps_word test:caps_word/caps_word_combo \
  test:tap_dance test:tap_dance/tap_dance_layers \
  test:tap_hold_configurations/default_mod_tap \
  test:tap_hold_configurations/quick_tap \
  test:tap_hold_configurations/permissive_hold \
  test:tap_hold_configurations/hold_on_other_key_press -j4
```

These are QMK's upstream suites, not a substitute for testing the exact personal
combos and timings on the keyboards. The reconciliation also compares expanded
custom code, generated keyboard configuration, and compiled keymap/lighting
data with the baseline. Reports are in the local archive.

The 0.34.8 software checks passed: both clean firmware builds, both strict lint
checks, and 237 tests across the 10 executables above, with no compiler warnings
in the test run. Generated keyboard settings and expanded custom keymap, combo,
and lighting code matched the baseline. Compiled keymap and lighting segment
data also matched byte for byte. Microdox flash usage changed from 25,186 to
25,168 bytes out of 28,672; Sweep ELF text size changed from 49,880 to 49,912 bytes.
Separate Sweep left/right build-only variants passed with the expected
handedness defines. These results do not establish hardware acceptance.

## Sweep handedness without flashing

The usual `:uf2-split-left` and `:uf2-split-right` targets flash hardware. To
prepare equivalent handedness settings without deploying anything, use the
normal build target with the same initialization define through `EXTRAFLAGS`:

```sh
make CONVERT_TO=blok ferris/sweep:chadhs EXTRAFLAGS=-DINIT_EE_HANDS_LEFT -j4
cp ferris_sweep_chadhs_blok.uf2 /path/to/archive/ferris_sweep_chadhs_blok_left.uf2
make CONVERT_TO=blok ferris/sweep:chadhs EXTRAFLAGS=-DINIT_EE_HANDS_RIGHT -j4
cp ferris_sweep_chadhs_blok.uf2 /path/to/archive/ferris_sweep_chadhs_blok_right.uf2
```

Choose an existing archive directory in place of `/path/to/archive`. The build
output name is reused, so copy each variant before building the next. Never put
a left-hand image on the right controller or the reverse. A generic build has
neither initialization define and relies on the stored handedness.

For routine Sweep updates, double-tap the reset button within 500 ms to enter
the Blok bootloader. Avoid the hold-a-key Bootmagic route when preserving saved
settings: Bootmagic invalidates EEPROM configuration. Do not use an EEPROM
clear or RP2040 flash-nuke image as part of the normal update. Firmware archives
do not contain the live EEPROM settings; record the current lighting state
before hardware work.

## Hardware acceptance

Flash one half at a time with the TRRS cable disconnected. Disconnect power
before reconnecting the split cable. Use matching firmware versions on both
halves before testing the assembled keyboard. Keep the other keyboard available.

Complete these checks separately for Microdox and Sweep:

- [ ] Every physical key and all five layers match the existing layout. Both
  halves work, with the expected handedness and USB connection behavior.
- [ ] Home-row rolls, held shortcuts, thumb layer taps, quick-tap repeats, all
  18 combos, Caps Word continuation/timeout, gaming toggles, and Vim macros
  behave as before. Check quick repeated combos and simultaneous modifiers.
- [ ] All four KVM ports switch correctly; single taps, media keys, ordinary
  USB reconnects, and at least three sleep/wake cycles work without stuck keys.
- [ ] Both halves display the expected base, gaming, caps, and anti-idle colors.
  Check overlapping lighting states, the RGB toggle, brightness, restart
  persistence, and the Microdox controller LED. Test anti-idle in an empty editor
  for over 30 seconds, confirm Z or X as appropriate, and switch it off afterward.
- [ ] A normal typing session and power cycle reveal no regressions. Record the
  date, firmware checksum, and result before tagging the release validated.

Current result: neither keyboard has completed this checklist for 0.34.8.

## Recovery

Stop using a candidate that changes typing, lighting, KVM behavior, or split
operation. Restore both halves to the matching baseline version. Preserve
EEPROM unless there is a diagnosed reason to reset it; a reset can lose saved
lighting settings and handedness.

Fresh baseline builds are in `baseline-builds/`, and untouched preexisting files
are in `existing-firmware/`. The fresh baseline Sweep UF2 is generic and relies
on stored handedness. If handedness is missing or incorrect, rebuild the backup
ref with its recorded submodule revisions and generate separate left/right UF2s
using the build-only commands above. The Microdox recovery flash method depends
on confirming its actual bootloader; its historical DFU split targets also set
EEPROM handedness.

For source recovery, use the backup branch in a separate checkout or restore it
only after saving current work. Restore its exact submodule revisions before
building. Do not force-reset the reconciliation branch or discard the archive.

Restoring old firmware does not restore EEPROM values changed during testing.
Reapply the recorded lighting state and verify handedness after recovery.
