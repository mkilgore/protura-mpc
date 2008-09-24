/* tmul -- test file for mpc_mul.

Copyright (C) 2002, 2005, 2008 Andreas Enge, Paul Zimmermann

This file is part of the MPC Library.

The MPC Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version.

The MPC Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the MPC Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA. */

#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"
#include "mpfr.h"
#include "mpc.h"
#include "mpc-impl.h"

static int
mpc_mul_ui_ref (mpc_t, mpc_srcptr, unsigned long int, mpc_rnd_t);

#include "random.c"
#define REFERENCE_FUNCTION mpc_mul_ui_ref
#define TEST_FUNCTION mpc_mul_ui
#include "tgeneric_ccu.c"

static int
mpc_mul_ui_ref (mpc_t z, mpc_srcptr x, unsigned long int y, mpc_rnd_t rnd)
/* computes the product of x and y using mpc_mul_fr using the rounding mode rnd */
{
  mpfr_t yf;
  int inexact_z;

  mpfr_init2 (yf, 8 * sizeof (long int));
  mpfr_set_ui (yf, y, GMP_RNDN);

  inexact_z = mpc_mul_fr (z, x, yf, rnd);

  mpfr_clear (yf);

  return inexact_z;
}

int
main (void)
{
  test_start ();

  tgeneric (2, 1024, 7, -1);

  test_end ();

  return 0;
}