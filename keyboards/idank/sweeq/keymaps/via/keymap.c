// Copyright 2023 Idan Kamara (@idank)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_keycodes {
    CMD_BRACE = SAFE_RANGE,
    ALT_BRACE,
    CTL_BRACE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
      KC_W, KC_L, KC_Y, KC_P, KC_B,                           KC_Z, KC_F, KC_O, KC_U, KC_QUOT,
      KC_C, LCTL_T(KC_R), LALT_T(KC_S), LGUI_T(KC_T), KC_G,   KC_M, RGUI_T(KC_N), RALT_T(KC_E), RCTL_T(KC_I), KC_A,
      KC_Q, KC_J, KC_V, KC_D, KC_K,                           KC_X, KC_H, KC_MINS, KC_COMM, KC_DOT,
                                            MO(1), KC_LSFT,   ALL_T(KC_SPC), MO(2)
    ),

  [1] = LAYOUT(
      KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,                         KC_CIRC, KC_AMPR, KC_ASTR, KC_GRV, KC_TILD,
      KC_ESC, LCTL_T(KC_BSPC), LALT_T(KC_TAB), LGUI_T(KC_ENT), KC_EQL,  KC_SCLN, CMD_BRACE, ALT_BRACE, CTL_BRACE, KC_BSLS,
      LSFT(KC_TAB), LALT(KC_BSPC), KC_SLSH, KC_QUES, KC_DEL,            KC_COLN, KC_RCBR, KC_RPRN, KC_RBRC, KC_PIPE,
                                                       KC_NO, KC_LSFT,  ALL_T(KC_SPC), MO(3)
    ),

  [2] = LAYOUT(
      KC_SLSH, KC_1, KC_2, KC_3, KC_MINS,                      KC_NO, KC_BTN1, KC_NO, KC_BTN2, KC_CUT,
      KC_0, LCTL_T(KC_4), LALT_T(KC_5), LGUI_T(KC_6), KC_EQL,  KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_COPY,
      KC_ASTR, KC_7, KC_8, KC_9, KC_PLUS,                      KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_PSTE,
                                              MO(3), KC_LSFT,  ALL_T(KC_SPC), KC_NO
    ),
  [3] = LAYOUT(
      KC_F1, KC_F2, KC_F3, KC_F4, KC_MCTL,       KC_LPAD, KC_MPRV, KC_MNXT, KC_MPLY, KC_NO,
      KC_F5, KC_F6, KC_F7, KC_F8, KC_NO,         KC_NO, KC_VOLD, KC_VOLU, KC_MUTE, KC_NO,
      KC_F9, KC_F10, KC_F11, KC_F12, QK_BOOT,    KC_NO, KC_BRID, KC_BRIU, KC_NO, KC_NO,
                              KC_TRNS, KC_NO,    KC_NO, KC_TRNS
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t cmd_timer;
  static uint16_t alt_timer;
  static uint16_t ctl_timer;
  switch (keycode) {
    case CMD_BRACE:
      if(record->event.pressed) {
        cmd_timer = timer_read();
        if (timer_elapsed(cmd_timer) > TAPPING_TERM) {
            register_code(KC_RCMD); // Change the key to be held here
        }
      } else {
        unregister_code(KC_RCMD); // Change the key that was held here, too!
        if (timer_elapsed(cmd_timer) < TAPPING_TERM) {
          SEND_STRING("{"); // Change the character(s) to be sent on tap here
        }
      }
      return false; // We handled this keypress
    case ALT_BRACE:
      if(record->event.pressed) {
        alt_timer = timer_read();
        if (timer_elapsed(alt_timer) > TAPPING_TERM) {
            register_code(KC_RALT); // Change the key to be held here
        }
      } else {
        unregister_code(KC_RALT); // Change the key that was held here, too!
        if (timer_elapsed(alt_timer) < TAPPING_TERM) {
          SEND_STRING("("); // Change the character(s) to be sent on tap here
        }
      }
      return false; // We handled this keypress
    case CTL_BRACE:
      if(record->event.pressed) {
        ctl_timer = timer_read();
        if (timer_elapsed(ctl_timer) > TAPPING_TERM) {
            register_code(KC_RCTL); // Change the key to be held here
        }
      } else {
        unregister_code(KC_RCTL); // Change the key that was held here, too!
        if (timer_elapsed(ctl_timer) < TAPPING_TERM) {
          SEND_STRING("["); // Change the character(s) to be sent on tap here
        }
      }
      return false; // We handled this keypress
  }
  return true; // We didn't handle other keypresses
}
