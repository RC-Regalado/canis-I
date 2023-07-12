/*
  gcode.c - rs274/ngc parser.
  Part of Grbl

  Copyright (c) 2011-2016 Sungeun K. Jeon
  Copyright (c) 2009-2011 Simen Svale Skogsrud
  Copyright (c) 2021 Canis I

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

// Datos de gcode.c GRBL
#include "../utils.h"
#include "gcode.h"
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>

#define AXIS_COMMAND_NONE 0
#define AXIS_COMMAND_NON_MODAL 1
#define AXIS_COMMAND_MOTION_MODE 2

// Extructura "externa" del G-Code
parser_state_t gc_state;
parser_block_t gc_block;

#define FAIL(status) return (status);

void gc_init() { memset(&gc_state, 0, sizeof(parser_state_t)); }

uint8_t gc_execute_line(char *line) {
  memset(&gc_block, 0, sizeof(gc_modal_t));
  memcpy(&gc_block.modal, &gc_state.modal, sizeof(gc_modal_t));

  uint8_t axis_command = AXIS_COMMAND_NONE;
  uint8_t axis_0, axis_1, axis_linear;
  uint8_t coord_select = 0;

  // Primero los comando lineales
  uint16_t axis_words;

  // TODO: Implemantar movimientos otros
  uint16_t ijk_words;

  uint16_t command_words;
  uint8_t gc_parser_flags;

  uint8_t word_bit;
  uint8_t char_counter = 0;
  char letter;
  float value;
  uint8_t int_value = 0;
  uint16_t mantissa = 0;

  while (line[char_counter] != 0) {
    letter = line[char_counter];

    if ((letter < 'A') || letter > 'Z') {
      FAIL(1);
    }

    char_counter++;

    if (!read_float(line, &char_counter, &value)) {
      FAIL(2);
    }
    int_value = std::trunc(value);
    mantissa = std::round(100 * (value - int_value));

    switch (letter) {
    case 'G':
      switch (int_value) {
      case 0:
      case 1:
      case 2:
      case 3:
      case 38:
        if (axis_command) {
          FAIL(3);
        }
        axis_command = AXIS_COMMAND_MOTION_MODE;
      case 80:
        word_bit = MODAL_GROUP_G1;
        gc_block.modal.motion = int_value;

        if (int_value == 38) {
          if (!((mantissa == 20) || (mantissa == 30) || (mantissa == 40) ||
                (mantissa == 50))) {
            FAIL(2);
          }
        }
        gc_block.modal.motion += (mantissa / 10) + 100;
        mantissa = 0;
        break;
      }

      if (mantissa > 0) {
        FAIL(1);
      }
    }
  }

  return 0;
}
