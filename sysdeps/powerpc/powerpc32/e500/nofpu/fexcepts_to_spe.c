/* Convert floating-point exceptions to SPEFSCR form.
   Copyright (C) 2013 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <fenv_libc.h>

/* Convert EXCEPTS from FE_* form to SPEFSCR bits, returning the
   converted value.  */

int
__fexcepts_to_spe (int excepts)
{
  int result = 0;
  if (excepts & FE_INEXACT)
    result |= SPEFSCR_FINXS;
  if (excepts & FE_DIVBYZERO)
    result |= SPEFSCR_FDBZS;
  if (excepts & FE_UNDERFLOW)
    result |= SPEFSCR_FUNFS;
  if (excepts & FE_OVERFLOW)
    result |= SPEFSCR_FOVFS;
  if (excepts & FE_INVALID)
    result |= SPEFSCR_FINVS;
  return result;
}

libm_hidden_def (__fexcepts_to_spe)
