// Datos de gcode.c GRBL
#include <cstdint>
#include <cstring>
#include "gcode.h"

#define AXIS_COMMAND_NONE 0
#define AXIS_COMMAND_NON_MODAL 1
#define AXIS_COMMAND_MOTION_MODE 2

// Extructura "externa" del G-Code
parser_state_t gc_state;
parser_block_t gc_block;

#define FAIL(status) return(status);

void gc_init() {
    memset(&gc_state, 0, sizeof(parser_state_t));
}


uint8_t gc_execute_line(char *line){
  uint8_t axis_command = AXIS_COMMAND_NONE;

  return 0;
}
