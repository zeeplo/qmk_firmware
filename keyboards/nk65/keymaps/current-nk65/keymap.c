/* Copyright 2019 Yiancar
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum my_keycodes {
  CTRL_RIGHT = SAFE_RANGE,
  CTRL_LEFT,
  VS_OPEN_TERMINAL,
  OPEN_FIREFOX,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_65_ansi( /* Base */
    KC_GESC, KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_MYCM,\
    KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_MAIL,\
    KC_LCTRL, KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  OPEN_FIREFOX,\
    KC_LSFT, KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_LEAD, \
    MO(1), KC_LGUI, KC_LALT,                KC_SPC,                          KC_RALT, MO(1),   MO(2), KC_LEFT, KC_DOWN, KC_RGHT),

[1] = LAYOUT_65_ansi( /* FN */
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  _______,\
    KC_CAPS, CTRL_LEFT, KC_UP, CTRL_RIGHT, _______, _______, KC_CALC, _______, _______, _______, _______, KC_HOME, KC_END, RESET,   _______,\
    _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______,  _______,  _______,  _______,  _______, _______, KC_PGUP, KC_PGDN,          _______, _______,\
    _______, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  VS_OPEN_TERMINAL,  KC_INS,  _______,          _______, _______,\
    _______, _______, _______,                _______,                               _______, _______, _______, _______, _______, _______),

[2] = LAYOUT_65_ansi( /* Empty for dynamic keymaps */
    TG(3), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_F13,\
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_F14,\
    _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,          _______, _______,\
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,          _______, _______,\
    _______, _______, _______,                _______,                               _______, _______, _______, _______, _______, _______),

[3] = LAYOUT_65_ansi( /* Empty for dynamic keymaps */
    TG(3), H1_INC, H2_INC, H1_DEC, H2_DEC, _______, _______, _______, _______, _______, _______, _______, _______, _______, ES_INC,\
    _______, S1_INC, S2_INC, S1_DEC, S2_DEC, _______, _______, _______, _______, _______, _______, _______, _______, _______, ES_DEC,\
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,\
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          BR_INC, _______,\
    _______, _______, _______,                _______,                               _______, _______, _______, EF_DEC, BR_DEC, EF_INC),
};

void matrix_init_user(void) {
  //user initialization
}

LEADER_EXTERNS();

void matrix_scan_user(void) {
  //user matrix
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_TWO_KEYS(KC_Y, KC_T) {
      SEND_STRING("youtube.com");
    }
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CTRL_RIGHT:
      if (record->event.pressed) {
          register_code(KC_LCTRL);
          register_code(KC_RIGHT);
      } else {
          unregister_code(KC_LCTRL);
          unregister_code(KC_RIGHT);
      }
      break;

    case CTRL_LEFT:
      if (record->event.pressed) {
          register_code(KC_LCTRL);
          register_code(KC_LEFT);
      } else {
          unregister_code(KC_LEFT);
      }
      break;
    case VS_OPEN_TERMINAL:
      if(record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_LSFT("`")));
      }
      break;
    case OPEN_FIREFOX:
      if(record->event.pressed) {
        SEND_STRING(SS_TAP(X_LGUI) SS_DELAY(100) "FIREFOX" SS_TAP(X_ENT));
      }
      break;
  }
    return true;
}