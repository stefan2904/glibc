# Copyright (C) 1998-2013 Free Software Foundation, Inc.
# This file is part of the GNU C Library.

# The GNU C Library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.

# The GNU C Library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.

# You should have received a copy of the GNU Lesser General Public
# License along with the GNU C Library; if not, see
# <http://www.gnu.org/licenses/>.

#
#	Sub-makefile for nscd portion of the library.
#
subdir	:= nscd

include ../Makeconfig

ifneq ($(use-nscd),no)
routines := nscd_getpw_r nscd_getgr_r nscd_gethst_r nscd_getai \
	    nscd_initgroups nscd_getserv_r nscd_netgroup
aux	:= nscd_helper
endif

# To find xmalloc.c
vpath %.c ../locale/programs

nscd-modules := nscd connections pwdcache getpwnam_r getpwuid_r grpcache \
		getgrnam_r getgrgid_r hstcache gethstbyad_r gethstbynm3_r \
		getsrvbynm_r getsrvbypt_r servicescache \
		dbg_log nscd_conf nscd_stat cache mem nscd_setup_thread \
		xmalloc xstrdup aicache initgrcache gai res_hconf \
		netgroupcache

ifeq ($(build-nscd)$(have-thread-library),yesyes)

others += nscd
others-pie += nscd
install-sbin := nscd

extra-objs = $(nscd-modules:=.o)

endif

all-nscd-modules := $(nscd-modules) selinux
ifeq (yes,$(have-selinux))
ifeq (yes,$(have-libaudit))
libaudit = -laudit
ifeq (yes,$(have-libcap))
libcap = -lcap
endif
endif

nscd-modules += selinux
selinux-LIBS := -lselinux $(libaudit) $(libcap)

# The configure.ac check for libselinux and its headers did not use
# $SYSINCLUDES.  The directory specified by --with-headers usually
# contains only the basic kernel interface headers, not something like
# libselinux.  So the simplest thing is to presume that the standard
# system headers will be ok for this file.
$(objpfx)nscd_stat.o: sysincludes = # nothing
$(objpfx)selinux.o: sysincludes = # nothing
endif

LDLIBS-nscd = $(selinux-LIBS)

include ../Rules

CFLAGS-nscd_getpw_r.c = -fexceptions
CFLAGS-nscd_getgr_r.c = -fexceptions
CFLAGS-nscd_gethst_r.c = -fexceptions
CFLAGS-nscd_getai.c = -fexceptions
CFLAGS-nscd_initgroups.c = -fexceptions

CPPFLAGS-nonlib += -DIS_IN_nscd=1 -D_FORTIFY_SOURCE=2

ifeq (yesyes,$(have-fpie)$(build-shared))
CFLAGS-nonlib += $(pie-ccflag)
endif
ifeq (yes,$(have-ssp))
CFLAGS-nonlib += -fstack-protector
endif

ifeq (yesyes,$(have-fpie)$(build-shared))
LDFLAGS-nscd = -Wl,-z,now
endif

# This makes sure CPPFLAGS-nonlib and CFLAGS-nonlib are passed
# for all these modules.
cpp-srcs-left := $(nscd-modules:=.c)
lib := nonlib
include $(patsubst %,$(..)cppflags-iterator.mk,$(cpp-srcs-left))

$(objpfx)nscd: $(nscd-modules:%=$(objpfx)%.o)

ifeq ($(build-shared),yes)
$(objpfx)nscd: $(shared-thread-library) $(common-objpfx)nis/libnsl.so
else
$(objpfx)nscd: $(static-thread-library) $(common-objpfx)nis/libnsl.a
endif
