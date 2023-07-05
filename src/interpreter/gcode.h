/*
  gcode.h - rs274/ngc parser.
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

// Only a part used

#ifndef GCODE_H_
#define GCODE_H_

// First stage *Linear motion*
#include <cstdint>
#define N_AXIS 3

#define MODAL_GROUP_G1 1 // [G0,G1,G2,G3,G38.2,G38.3,G38.4,G38.5,G80] Motion

#define MOTION_MODE_SEEK 0 // G0 (Default: Must be zero)
#define MOTION_MODE_LINEAR 1 // G1 (Do not alter value)
#define MOTION_MODE_CW_ARC 2  // G2 (Do not alter value)
#define MOTION_MODE_CCW_ARC 3  // G3 (Do not alter value)
#define MOTION_MODE_PROBE_TOWARD 140 // G38.2 (Do not alter value)
#define MOTION_MODE_PROBE_TOWARD_NO_ERROR 141 // G38.3 (Do not alter value)
#define MOTION_MODE_PROBE_AWAY 142 // G38.4 (Do not alter value)
#define MOTION_MODE_PROBE_AWAY_NO_ERROR 143 // G38.5 (Do not alter value)
#define MOTION_MODE_NONE 80 // G80 (Do not alter value)

typedef struct {
  uint8_t motion;          // {G0,G1,G2,G3,G38.2,G80}
} gc_modal_t;

typedef struct {
  float xyz[3];   // X, Y, Z axes
} gc_values_t;

typedef struct {
  gc_modal_t modal; 
  int32_t line_number;          // Last line number sent

  float position[N_AXIS];       // Where the interpreter considers ths tool to be at this point in the code
  float coord_offset[N_AXIS];   // Retains the G92 coordinate offset (work coordinates) relative to
                                // machine zero in mm.
} parser_state_t;

extern parser_state_t gc_state;

typedef struct {
  uint8_t non_modal_command;
  gc_modal_t modal;
  gc_values_t values;
} parser_block_t;

void gc_init();
uint8_t gc_execute_line(char* line);
void gc_sync_position();
#endif
