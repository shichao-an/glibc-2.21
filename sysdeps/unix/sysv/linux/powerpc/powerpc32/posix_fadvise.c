/* Copyright (C) 2003-2015 Free Software Foundation, Inc.
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

#include <errno.h>
#include <fcntl.h>
#include <sysdep.h>

/* Advice the system about the expected behaviour of the application with
   respect to the file associated with FD.  */

int
posix_fadvise (int fd, off_t offset, off_t len, int advise)
{
#ifdef __NR_fadvise64
  INTERNAL_SYSCALL_DECL (err);
  int ret = INTERNAL_SYSCALL (fadvise64, err, 6, fd, 0,
			      __LONG_LONG_PAIR (offset >> 31, offset), len,
			      advise);
  if (INTERNAL_SYSCALL_ERROR_P (ret, err))
    return INTERNAL_SYSCALL_ERRNO (ret, err);
  return 0;
#else
  return ENOSYS;
#endif
}
