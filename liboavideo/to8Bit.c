/*****************************************************************************
 *
 * to8Bit.c -- conversion to 8-bit frame formats
 *
 * Copyright 2017,2018 James Fidell (james@openastroproject.org)
 *
 * License:
 *
 * This file is part of the Open Astro Project.
 *
 * The Open Astro Project is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The Open Astro Project is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the Open Astro Project.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 *****************************************************************************/

#include <oa_common.h>

#include "to8Bit.h"

void
copyAlternate ( void* source, int offset, void* target, unsigned int length )
{
  uint8_t*	s = source;
  uint8_t*	t = target;
  
  s += offset;
  do {
    *t++ = *s++;
    s++;
    length -= 2;
  } while ( length );
}

void
oaBigEndian16BitTo8Bit ( void* source, void* target, unsigned int length )
{
  copyAlternate ( source, 0, target, length );
}


void
oaLittleEndian16BitTo8Bit ( void* source, void* target, unsigned int length )
{
  copyAlternate ( source, 1, target, length );
}


void
oaBigEndianShifted16BitTo8Bit ( void* source, void* target,
		unsigned int length, unsigned int shift )
{
  uint8_t*	s = source;
  uint8_t*	t = target;
	uint16_t	val16;
	uint8_t		val8;
  
  do {
		val16 = ( *s++ ) << 8;
		val16 |= *s++;
		val16 >>= shift;
		val8 = val16 & 0xff;
    *t++ = val8;
    length -= 2;
  } while ( length );
}


void
oaLittleEndianShifted16BitTo8Bit ( void* source, void* target,
		unsigned int length, unsigned int shift )
{
  uint8_t*	s = source;
  uint8_t*	t = target;
	uint16_t	val16;
	uint8_t		val8;
  
  do {
		val16 = *s++;
		val16 |= ( *s++ ) << 8;
		val16 >>= shift;
		val8 = val16 & 0xff;
    *t++ = val8;
    length -= 2;
  } while ( length );
}


void
oaPackedGrey12ToGrey8 ( void* source, void* target, unsigned int length )
{
  uint8_t*	s = source;
  uint8_t*	t = target;
  unsigned int	l = 0;

  // This may not be very nice if the image width is not even

  while ( length-- ) {
    if ( l % 3 != 1 ) {
      *t++ = *s;
    }
    s++;
    l++;
  }
}
