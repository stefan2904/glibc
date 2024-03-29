/* Procedure definition for FE_NOMASK_ENV for Linux/ppc.
   Copyright (C) 2000-2013 Free Software Foundation, Inc.
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
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <sysdep.h>
#include <sys/prctl.h>
#include <kernel-features.h>
#include <shlib-compat.h>

const fenv_t *
__fe_nomask_env (void)
{
  INTERNAL_SYSCALL_DECL (err);
  INTERNAL_SYSCALL (prctl, err, 2, PR_SET_FPEXC, PR_FP_EXC_PRECISE);

  return FE_ENABLED_ENV;
}
#if SHLIB_COMPAT (libm, GLIBC_2_1, GLIBC_2_18)
compat_symbol (libm, __fe_nomask_env, __fe_nomask_env, GLIBC_2_1);
#endif
