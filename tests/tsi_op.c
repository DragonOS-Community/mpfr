/* Test file for mpfr_add_si, mpfr_sub_si, mpfr_si_sub, mpfr_mul_si, 
   mpfr_div_si, mpfr_si_div

Copyright 2004 Free Software Foundation.

This file is part of the MPFR Library.

The MPFR Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version.

The MPFR Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the MPFR Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA. */

#include <stdio.h>
#include <stdlib.h>

#include "mpfr-test.h"

#define ERROR1(s, i, z, exp) \
{\
  printf("Error for "s" and i=%d\n", i);\
  printf("Expected %s\n", exp);\
  printf("Got      "); mpfr_out_str (stdout, 16, 0, z, GMP_RNDN);\
  putchar ('\n');\
  exit(1);\
}

const struct {
  const char * op1;
  long int op2;
  const char * res_add;
  const char * res_sub;
  const char * res_mul;
  const char * res_div;
} tab[] = { 
  {"10", 0x1, "11", "0F", "10", "10"},
  {"1", -1,  "0",   "2",   "-1",  "-1"},
  {"17.42", -0x17, "0.42", "2E.42", "-216.ee", "-1.02de9bd37a6f4"},
  {"-1024.0", -0x16,  "-103A", "-100E", "16318", "bb.d1745d1745d0"}
};

int
main (int argc, char *argv[])
{
  mpfr_t x, z;
  int y;
  int i;

  tests_start_mpfr ();
  mpfr_inits2 (53, x, z, NULL);
  for(i = 0 ; i < numberof (tab) ; i++)
    {
      mpfr_set_str (x, tab[i].op1, 16, GMP_RNDN);
      y = tab[i].op2;
      mpfr_add_si (z, x, y, GMP_RNDZ);
      if (mpfr_cmp_str (z, tab[i].res_add, 16, GMP_RNDN))
	ERROR1("add_si", i, z, tab[i].res_add);
      mpfr_sub_si (z, x, y, GMP_RNDZ);
      if (mpfr_cmp_str (z, tab[i].res_sub, 16, GMP_RNDN))
        ERROR1("sub_si", i, z, tab[i].res_sub);
      mpfr_si_sub (z, y, x, GMP_RNDZ);
      mpfr_neg (z, z, GMP_RNDZ);
      if (mpfr_cmp_str (z, tab[i].res_sub, 16, GMP_RNDN))
        ERROR1("si_sub", i, z, tab[i].res_sub);
      mpfr_mul_si (z, x, y, GMP_RNDZ);
      if (mpfr_cmp_str (z, tab[i].res_mul, 16, GMP_RNDN))
        ERROR1("mul_si", i, z, tab[i].res_mul);
      mpfr_div_si (z, x, y, GMP_RNDZ);
      if (mpfr_cmp_str (z, tab[i].res_div, 16, GMP_RNDN))
        ERROR1("div_si", i, z, tab[i].res_div);
    }
  mpfr_set_str1 (x, "1");
  mpfr_si_div (z, 1024, x, GMP_RNDN);
  if (mpfr_cmp_str1 (z, "1024"))
    ERROR1("si_div", i, z, "1024");
  mpfr_si_div (z, -1024, x, GMP_RNDN);
  if (mpfr_cmp_str1 (z, "-1024"))
    ERROR1("si_div", i, z, "-1024");

  mpfr_clears (x, z, NULL);
  tests_end_mpfr ();
  return 0;
}
