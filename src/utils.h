/*
  nuts_bolts.c - Shared functions
  Part of Grbl

  Copyright (c) 2011-2016 Sungeun K. Jeon for Gnea Research LLC
  Copyright (c) 2009-2011 Simen Svale Skogsrud

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

#include <cstdint>

#define MAX_INT_DIGITS 8 // Maximum number of digits in int32 (and float)

// Extracts a floating point value from a string. The following code is based
// loosely on the avr-libc strtod() function by Michael Stumpf and Dmitry
// Xmelkov and many freely available conversion method examples, but has been
// highly optimized for Grbl. For known CNC applications, the typical decimal
// value is expected to be in the range of E0 to E-4. Scientific notation is
// officially not supported by g-code, and the 'E' character may be a g-code
// word on some CNC systems. So, 'E' notation will not be recognized. NOTE:
// Thanks to Radu-Eosif Mihailescu for identifying the issues with using
// strtod().
uint8_t read_float(char *line, uint8_t *char_counter, float *float_ptr); 
