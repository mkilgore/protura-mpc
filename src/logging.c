/* logging.c -- "Dummy" functions logging calls to real mpc functions.

Copyright (C) INRIA, 2011

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

#include "config.h"
#include <stdio.h>

#ifdef HAVE_INTTYPES_H
#include <inttypes.h>
#endif
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif

#include "mpc-log.h"

#include <dlfcn.h>

typedef int (*c_c_func_ptr) (mpc_ptr, mpc_srcptr, mpc_rnd_t);
typedef int (*c_cc_func_ptr) (mpc_ptr, mpc_srcptr, mpc_srcptr, mpc_rnd_t);
typedef int (*c_ccc_func_ptr) (mpc_ptr, mpc_srcptr, mpc_srcptr, mpc_srcptr, mpc_rnd_t);
typedef int (*cc_c_func_ptr) (mpc_ptr, mpc_ptr, mpc_srcptr, mpc_rnd_t, mpc_rnd_t);

#define MPC_LOGGING_OUT_PREC(z) \
   do { \
      fprintf (stderr, " %li %li", (long) mpfr_get_prec (mpc_realref (z)),  \
                                (long) mpfr_get_prec (mpc_imagref (z))); \
   } while (0);

#define MPC_LOGGING_OUT_C(z) \
   do { \
      MPC_LOGGING_OUT_PREC (z); \
      fprintf (stderr, " "); \
      mpc_out_str (stderr, 16, 0, z, MPC_RNDNN); \
   } while (0);

#define MPC_LOGGING_FUNC_TYPE(funcname, type) \
   do { \
      fprintf (stderr, "mpc_"#funcname" "#type); \
   } while (0);

#define MPC_LOGGING_C_C(funcname) \
__MPC_DECLSPEC int mpc_log_##funcname (mpc_ptr rop, mpc_srcptr op, mpc_rnd_t rnd) \
{ \
   static c_c_func_ptr func = NULL; \
   if (func == NULL) \
      func = (c_c_func_ptr) (intptr_t) dlsym (NULL, "mpc_"#funcname); \
   MPC_LOGGING_FUNC_TYPE (funcname, c_c); \
   MPC_LOGGING_OUT_PREC (rop); \
   MPC_LOGGING_OUT_C (op); \
   fprintf (stderr, "\n"); \
   return func (rop, op, rnd); \
}

#define MPC_LOGGING_C_CC(funcname) \
__MPC_DECLSPEC int mpc_log_##funcname (mpc_ptr rop, mpc_srcptr op1, mpc_srcptr op2, mpc_rnd_t rnd) \
{ \
   static c_cc_func_ptr func = NULL; \
   if (func == NULL) \
      func = (c_cc_func_ptr) (intptr_t) dlsym (NULL, "mpc_"#funcname); \
   MPC_LOGGING_FUNC_TYPE (funcname, c_cc); \
   MPC_LOGGING_OUT_PREC (rop); \
   MPC_LOGGING_OUT_C (op1); \
   MPC_LOGGING_OUT_C (op2); \
   fprintf (stderr, "\n"); \
   return func (rop, op1, op2, rnd); \
}

#define MPC_LOGGING_C_CCC(funcname) \
__MPC_DECLSPEC int mpc_log_##funcname (mpc_ptr rop, mpc_srcptr op1, mpc_srcptr op2, mpc_srcptr op3, mpc_rnd_t rnd) \
{ \
   static c_ccc_func_ptr func = NULL; \
   if (func == NULL) \
      func = (c_ccc_func_ptr) (intptr_t) dlsym (NULL, "mpc_"#funcname); \
   MPC_LOGGING_FUNC_TYPE (funcname, c_ccc); \
   MPC_LOGGING_OUT_PREC (rop); \
   MPC_LOGGING_OUT_C (op1); \
   MPC_LOGGING_OUT_C (op2); \
   MPC_LOGGING_OUT_C (op3); \
   fprintf (stderr, "\n"); \
   return func (rop, op1, op2, op3, rnd); \
}

#define MPC_LOGGING_CC_C(funcname) \
__MPC_DECLSPEC int mpc_log_##funcname (mpc_ptr rop1, mpc_ptr rop2, mpc_srcptr op, mpc_rnd_t rnd1, mpc_rnd_t rnd2) \
{ \
   static cc_c_func_ptr func = NULL; \
   if (func == NULL) \
      func = (cc_c_func_ptr) (intptr_t) dlsym (NULL, "mpc_"#funcname); \
   MPC_LOGGING_FUNC_TYPE (funcname, cc_c); \
   MPC_LOGGING_OUT_PREC (rop1); \
   MPC_LOGGING_OUT_PREC (rop2); \
   MPC_LOGGING_OUT_C (op); \
   fprintf (stderr, "\n"); \
   return func (rop1, rop2, op, rnd1, rnd2); \
}

MPC_LOGGING_C_C (sqr)
MPC_LOGGING_C_C (conj)
MPC_LOGGING_C_C (neg)
MPC_LOGGING_C_C (sqrt)
MPC_LOGGING_C_C (proj)
MPC_LOGGING_C_C (exp)
MPC_LOGGING_C_C (log)
MPC_LOGGING_C_C (sin)
MPC_LOGGING_C_C (cos)
MPC_LOGGING_C_C (tan)
MPC_LOGGING_C_C (sinh)
MPC_LOGGING_C_C (cosh)
MPC_LOGGING_C_C (tanh)
MPC_LOGGING_C_C (asin)
MPC_LOGGING_C_C (acos)
MPC_LOGGING_C_C (atan)
MPC_LOGGING_C_C (asinh)
MPC_LOGGING_C_C (acosh)
MPC_LOGGING_C_C (atanh)

MPC_LOGGING_C_CC (add)
MPC_LOGGING_C_CC (sub)
MPC_LOGGING_C_CC (mul)
MPC_LOGGING_C_CC (div)
MPC_LOGGING_C_CC (pow)

MPC_LOGGING_C_CCC (fma)

MPC_LOGGING_CC_C (sin_cos)