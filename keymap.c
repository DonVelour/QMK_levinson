// Copyright 2023 donvelour
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_danish.h"
#include "os_detection.h"

extern keymap_config_t keymap_config;

enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _NUMPAD,
    _MOUSE,
};

enum custom_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  LCBR,
  RCBR,
  SS,
};

#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,------------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  ||   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  ||   H  |   J  |   K  |   L  |   æ  |  ø   |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  ||   N  |   M  |   ,  |   .  |   -  | Enter|
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Ctrl |      | GUI  | Alt  |Lower |    Space     |Raise | Left | Down |  Up  | Right|
 * `------------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12(
  KC_ESC,  KC_Q,  KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_TAB,  KC_A,  KC_S,    KC_D,    KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,  KC_X,    KC_C,    KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  KC_LCTL, KC_NO, KC_LGUI, KC_LALT, LOWER, KC_SPC, KC_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower
 * ,------------------------------------------------------------------------------------.
 * |  SS  |  F1  |  F2  |  F3  |  F4  |  F5  || Home | End  |      |      |      | Bksp |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Caps |  F6  |  F7  |  F8  |  F9  |  F10 || PgUp |      |      |      |      | Del  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Trans|  F11 |  F12 |  F13 |  F14 |  F15 || PgDn |      |      |      |      | Play |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Trans|NUMPAD| Trans| Trans|Lower |    Space     |Raise | Prev | Vol- | Vol+ | Next |
 * `------------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12(
  SS,        KC_F1,        KC_F2,    KC_F3,    KC_F4,   KC_F5,  KC_HOME,  KC_END,  KC_NO,   KC_NO,   KC_NO,   KC_BSPC,
  KC_CAPS,   KC_F6,        KC_F7,    KC_F8,    KC_F9,   KC_F10, KC_PGUP,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_DEL,
  _______,   KC_F11,       KC_F12,   KC_F13,   KC_F14,  KC_F15, KC_PGDN,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_MPLY,
  _______,   TO(_NUMPAD),  _______,  _______,  _______, KC_SPC, KC_SPC, _______, KC_MRWD, KC_VOLD, KC_VOLU, KC_MFFD
),

/* Raise
 * ,------------------------------------------------------------------------------------.
 * |  GRV |   1  |   2  |   3  |   4  |   5  ||   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Altgr|      |      |      |      |      ||  +,? |¨,^,~ |   [  |   ]  |   å  | Del  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Trans|      |      |      |      |      ||   $  |  ´,` |   {  |   }  | '',* | Play |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Trans|NUMPAD| Trans| Trans| Lower|    Space     | Raise| Prev | Vol- | Vol+ | Next |
 * `------------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12(
  KC_GRV,  KC_1,        KC_2,    KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_RALT, KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_MINS,  DK_DIAE, DK_LBRC, DK_RBRC, KC_LBRC, KC_DEL,
  _______, KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NUBS,  DK_ACUT, LCBR,    RCBR,    KC_BSLS, KC_MPLY,
  _______, TO(_NUMPAD), _______, _______, _______, KC_SPC,  KC_SPC,   _______, KC_MRWD, KC_VOLD, KC_VOLU, KC_MFFD
),

/* Adjust (Lower + Raise)
 * ,------------------------------------------------------------------------------------.
 * |ERESET|      |      |      |      |TSKMGR|| RGB_T| RGB+ | RGB- | BL_C | BL_B |      |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |      |      |      |      |      |AS_TOG|| BL_T | Hue+ | Hue- | BL+  | BL-  |      |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |      |      |      |      |      | MOUSE||      | Sat+ | Sat- |RGB_L+|RGB_L-|      |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | RESET|      |      |      |      |      ||      |      |      |      |      |      |
 * `------------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_4x12(
  EE_CLR,  KC_NO,  KC_NO, KC_NO, KC_NO,   TSKMGR,     RGB_TOG, RGB_MOD, RGB_RMOD, BL_STEP, BL_BRTG, KC_NO,
  KC_NO,   KC_NO,  KC_NO, KC_NO, KC_NO,   AS_TOGG,    BL_TOGG, RGB_HUI, RGB_HUD,  BL_UP,   BL_DOWN, KC_NO,
  KC_NO,   KC_NO,  KC_NO, KC_NO, KC_NO,   TO(_MOUSE), KC_NO,   RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_NO,
  QK_BOOT, KC_NO,  KC_NO, KC_NO, _______, KC_NO,      KC_NO,   _______, KC_NO,    KC_NO,   KC_NO,   KC_NO
),

/* Numpad
 * ,------------------------------------------------------------------------------------.
 * |QWERTY|      |      |      |      |      || Num_L|   7  |   8  |   9  |   +  | BSPC |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |      |      |      |      |      |      ||      |   4  |   5  |   6  |   -  |   =  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |      |      |      |      |      |      ||      |   1  |   2  |   3  |   *  | Enter|
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |      |      |      |      |      |    Space     |   0  |   ,  | Left |   /  | Right|
 * `------------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_ortho_4x12(
  TO(_QWERTY), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NUM, KC_P7, KC_P8,   KC_P9,   KC_PPLS, KC_BSPC,
  KC_NO,       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,  KC_P4, KC_P5,   KC_P6,   KC_PMNS, DK_EQL,
  KC_NO,       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,  KC_P1, KC_P2,   KC_P3,   KC_PAST, KC_ENT,
  KC_NO,       KC_NO, KC_NO, KC_NO, KC_NO, KC_SPC, KC_SPC, KC_P0, KC_PDOT, KC_LEFT, KC_PSLS, KC_RGHT
),

/* Mouse
 * ,------------------------------------------------------------------------------------.
 * |  Esc |   Q  |   W  |   E  |   R  |   T  ||M_ACC0|      | MWUp |  MUp |MWDown|      |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |  Tab |   A  |   S  |   D  |   F  |   G  ||M_ACC1|      | MLeft| MDown|MRight|      |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  ||M_ACC2|      |      |      |      |  M2  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Ctrl |QWERTY|  GUI |  Alt |      | Space||   M1 |      |      |      |      |      |
 * `------------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT_ortho_4x12(
  KC_ESC,  KC_Q,        KC_W,    KC_E,    KC_R,  KC_T,   KC_ACL0, KC_NO, KC_WH_U, KC_MS_U, KC_WH_D, KC_NO,
  KC_TAB,  KC_A,        KC_S,    KC_D,    KC_F,  KC_G,   KC_ACL1, KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO,
  KC_LSFT, KC_Z,        KC_X,    KC_C,    KC_V,  KC_B,   KC_ACL2, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_BTN2,
  KC_LCTL, TO(_QWERTY), KC_LGUI, KC_LALT, KC_NO, KC_SPC, KC_BTN1, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  int OS = detected_host_os();
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case LCBR:
      if (record->event.pressed) {
        if (OS == OS_MACOS) {
          tap_code16(S(LOPT(KC_8)));
        } else {
          tap_code16(RALT(KC_7));
        }
      }
      return false;
      break;
    case RCBR:
      if (record->event.pressed) {
        if (OS == OS_MACOS) {
          tap_code16(S(LOPT(KC_9)));
        } else {
          tap_code16(RALT(KC_0));
        }
      }
      return false;
      break;
    case SS:
      if (record->event.pressed) {
        if (OS == OS_MACOS) {
          tap_code16(S(C(G(KC_4))));
        } else {
          tap_code16(G(S(KC_S)));
        }
      }
      return false;
      break;
  }
  return true;
}

/* Key leds
 * ,------------------------------------------------------------------------------------.
 * |  0   |  1   |  2   |  4   |  5   |  6   ||  36  |  37  |  38  |  40  |  41  |  42  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |  14  |  12  |  11  |  10  |  9   |  7   ||  50  |  48  |  47  |  46  |  45  |  43  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |  15  |  16  |  17  |  18  |  19  |  20  ||  51  |  52  |  53  |  54  |  55  |  56  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |  29  |  27  |  26  |  24  |  23  |  21  ||  65  |  63  |  62  |  60  |  59  |  57  |
 * `------------------------------------------------------------------------------------'
 */


// Define the size of your LED matrix
#define ARRAY_ROWS 4
#define ARRAY_COLS 12

//underglow leds 3,8,13,22,25,28,39,44,49,58,61,64

// Define the integer array representing the LED status
int lower_leds[ARRAY_ROWS][ARRAY_COLS] = {
    {4, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 4},
    {4, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 4},
    {4, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 4},
    {4, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 4}
};
int raise_leds[ARRAY_ROWS][ARRAY_COLS] = {
    {2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2}
};
int numpad_leds[ARRAY_ROWS][ARRAY_COLS] = {
    {1, 6, 6, 6, 6, 6, 1, 5, 5, 5, 1, 1},
    {6, 6, 6, 6, 6, 6, 6, 5, 5, 5, 1, 1},
    {6, 6, 6, 6, 6, 6, 6, 5, 5, 5, 1, 1},
    {6, 6, 6, 6, 6, 6, 1, 5, 1, 1, 1, 1}
};
int mouse_leds[ARRAY_ROWS][ARRAY_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
int keyboard[ARRAY_COLS][ARRAY_COLS] = {
    {0, 1, 2, 4, 5, 6, 36, 37, 38, 40, 41, 42},
    {14, 12, 11, 10, 9, 7, 50, 48, 47, 46, 45, 43},
    {15, 16, 17, 18, 19, 20, 51, 52, 53, 54, 55, 56},
    {29, 27, 26, 24, 23, 21, 65, 63, 62, 60, 59, 57}
};

// Function to turn on LEDs based on the provided array
void update_led_matrix(int (*array)[ARRAY_COLS], int x, int y) {
    for (int row = 0; row < x; ++row) {
        for (int col = 0; col < y; ++col) {
          switch(array[row][col]) {
            case 6:
                rgb_matrix_set_color(keyboard[row][col], RGB_OFF);
                break;
            case 5:
                rgb_matrix_set_color(keyboard[row][col], RGB_GREEN);
                break;
            case 4:
                rgb_matrix_set_color(keyboard[row][col], RGB_TEAL);
                break;
            case 2:
                rgb_matrix_set_color(keyboard[row][col], RGB_MAGENTA);
                break;
            case 1:
                rgb_matrix_set_color(keyboard[row][col], RGB_BLUE);
                break;
            default:
                break;
          }
        }
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case 5:
            update_led_matrix(mouse_leds, ARRAY_ROWS, ARRAY_COLS);
            break;
        case 4:
            update_led_matrix(numpad_leds, ARRAY_ROWS, ARRAY_COLS);
            break;
        case 2:
            update_led_matrix(raise_leds, ARRAY_ROWS, ARRAY_COLS);
            break;
        case 1:
            update_led_matrix(lower_leds, ARRAY_ROWS, ARRAY_COLS);
            break;
        default:
            break;
    }

    // check if caps lock is on
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(20, RGB_RED);
        rgb_matrix_set_color(21, RGB_RED);
        rgb_matrix_set_color(51, RGB_RED);
        rgb_matrix_set_color(65, RGB_RED);
    }
return false;
}
