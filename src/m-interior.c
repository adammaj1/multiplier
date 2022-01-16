// mandelbrot-numerics -- numerical algorithms related to the Mandelbrot set
// Copyright (C) 2015-2017 Claude Heiland-Allen
// License GPL3+ http://www.gnu.org/licenses/gpl.html
/*

 
 Files:
 https://code.mathr.co.uk/mandelbrot-numerics/blob_plain/HEAD:/c/bin/m-interior.c
 https://code.mathr.co.uk/mandelbrot-numerics/blob_plain/HEAD:/c/bin/m-util.h
 
 
 description:
 https://en.wikibooks.org/wiki/Fractals/mandelbrot-numerics#m-interior
 
 
 
 
 gcc m-interior.c -Wall -std=c99 -lm -o m-interior
 
 
 ./a.out
 
 usage: ./m-interior precision z-guess-re z-guess-im c-guess-re c-guess-im interior-r interior-t period maxsteps
 
 
 example :
 
 ./a.out double 0 0 0 0 1 0 1 100
 
 Output computed with precision = 53 bits is :
 z =  (5.0000000000000000e-01 ;  0.0000000000000000e+00) 
 c = ( 2.5000000000000000e-01;  0.0000000000000000e+00) 

*/

#include <stdio.h>
// #include <mandelbrot-numerics.h>
// #include "m-util.h"
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>
/*

*/
// mandelbrot-numerics/c/include/mandelbrot-numerics.h


enum m_newton { m_failed, m_stepped, m_converged };
typedef enum m_newton m_newton;







// mandelbrot-numerics/c/bin/m-util.h

static const double twopi = 6.283185307179586;
// epsilon^2
static const double epsilon2 = 1.9721522630525295e-31;

static inline bool arg_precision(const char *arg, bool *native, int *bits) {
  if (0 == strcmp("double", arg)) {
    *native = true;
    *bits = 53;
    return true;
  } else {
    char *check = 0;
    errno = 0;
    long int li = strtol(arg, &check, 10);
    bool valid = ! errno && arg != check && ! *check;
    int i = li;
    if (valid && i > 1) {
      *native = false;
      *bits = i;
      return true;
    }
  }
  return false;
}

static inline bool arg_double(const char *arg, double *x) {
  char *check = 0;
  errno = 0;
  double d = strtod(arg, &check);
  if (! errno && arg != check && ! *check) {
    *x = d;
    return true;
  }
  return false;
}

static inline bool arg_int(const char *arg, int *x) {
  char *check = 0;
  errno = 0;
  long int li = strtol(arg, &check, 10);
  if (! errno && arg != check && ! *check) {
    *x = li;
    return true;
  }
  return false;
}


static inline double cabs2(double _Complex z) {
  return creal(z) * creal(z) + cimag(z) * cimag(z);
}

static inline bool cisfinite(double _Complex z) {
  return isfinite(creal(z)) && isfinite(cimag(z));
}



// mandelbrot-numerics/c/lib/m_d_interior.c 
// double precision: m_d_*()  


extern m_newton m_d_interior_step(double _Complex *z_out, double _Complex *c_out, double _Complex z_guess, double _Complex c_guess, double _Complex interior, int period) {
  double _Complex c = c_guess;
  double _Complex z = z_guess;
  double _Complex dz = 1;
  double _Complex dc = 0;
  double _Complex dzdz = 0;
  double _Complex dcdz = 0;
  for (int p = 0; p < period; ++p) {
    dcdz = 2 * (z * dcdz + dc * dz);
    dzdz = 2 * (z * dzdz + dz * dz);
    dc = 2 * z * dc + 1;
    dz = 2 * z * dz;
    z = z * z + c;
  }
  double _Complex det = (dz - 1) * dcdz - dc * dzdz;
  double _Complex z_new = z_guess - (dcdz * (z - z_guess) - dc * (dz - interior)) / det;
  double _Complex c_new = c_guess - ((dz - 1) * (dz - interior) - dzdz * (z - z_guess)) / det;
  if (cisfinite(z_new) && cisfinite(c_new)) {
    *z_out = z_new;
    *c_out = c_new;
    if (cabs2(z_new - z_guess) <= epsilon2 && cabs2(c_new - c_guess) <= epsilon2) {
      return m_converged;
    } else {
      return m_stepped;
    }
  } else {
    *z_out = z_guess;
    *c_out = c_guess;
    return m_failed;
  }
}

extern m_newton m_d_interior(double _Complex *z_out, double _Complex *c_out, double _Complex z_guess, double _Complex c_guess, double _Complex interior, int period, int maxsteps) {
  m_newton result = m_failed;
  double _Complex z = z_guess;
  double _Complex c = c_guess;
  for (int i = 0; i < maxsteps; ++i) {
    if (m_stepped != (result = m_d_interior_step(&z, &c, z, c, interior, period))) {
      break;
    }
  }
  *z_out = z;
  *c_out = c;
  return result;
}






static void usage(const char *progname) {
  fprintf
    ( stderr
    , "usage: %s precision z-guess-re z-guess-im c-guess-re c-guess-im interior-r interior-t period maxsteps\n"
    , progname
    );
}

extern int main(int argc, char **argv) {
  
  
  // check input
  if (argc != 10) {
    usage(argv[0]);
    return 1;
  }
  bool native = true;
  int bits = 0;
  if (! arg_precision(argv[1], &native, &bits)) { return 1; }
  
  
  if (native) {
    // double precision 
    double zre = 0;
    double zim = 0;
    double cre = 0;
    double cim = 0;
    double ir = 0;
    double it = 0;
    int period = 0;
    int maxsteps = 0;
    if (! arg_double(argv[2], &zre)) { return 1; }
    if (! arg_double(argv[3], &zim)) { return 1; }
    if (! arg_double(argv[4], &cre)) { return 1; }
    if (! arg_double(argv[5], &cim)) { return 1; }
    if (! arg_double(argv[6], &ir)) { return 1; }
    if (! arg_double(argv[7], &it)) { return 1; }
    if (! arg_int(argv[8], &period)) { return 1; }
    if (! arg_int(argv[9], &maxsteps)) { return 1; }
    complex double z = 0;
    complex double c = 0;
    m_d_interior(&z, &c, zre + I * zim, cre + I * cim, ir * cexp(I * twopi * it), period, maxsteps);
    printf("Output computed with precision = %d bits is :\n z =  (%.16e ;  %.16e) \n c = ( %.16e;  %.16e) \n", bits, creal(z), cimag(z), creal(c), cimag(c));
    return 0;
  } else {
  
    // mpc and mpfr = arbitrary precision
  /* 
    mpc_t z, c, i, interior;
    mpfr_t p;
    mpc_init2(z, bits);
    mpc_init2(c, bits);
    mpc_init2(i, bits);
    mpc_init2(interior, bits);
    mpfr_init2(p, bits);
    int period = 0;
    int maxsteps = 0;
    if (! arg_mpc(argv[2], argv[3], z)) { return 1; }
    if (! arg_mpc(argv[4], argv[5], c)) { return 1; }
    if (! arg_mpc(argv[6], argv[7], i)) { return 1; }
    if (! arg_int(argv[8], &period)) { return 1; }
    if (! arg_int(argv[9], &maxsteps)) { return 1; }
    // interior = ir * cexp(I * twopi * it);
    mpfr_const_pi(p, MPFR_RNDN);
    mpfr_mul(mpc_imagref(i), mpc_imagref(i), p, MPFR_RNDN);
    mpfr_mul_2si(mpc_imagref(i), mpc_imagref(i), 1, MPFR_RNDN);
    mpfr_sin_cos(mpc_imagref(interior), mpc_realref(interior), mpc_imagref(i), MPFR_RNDN);
    mpc_mul_fr(interior, interior, mpc_realref(i), MPC_RNDNN);
    m_r_interior(z, c, z, c, interior, period, maxsteps);
    mpfr_printf("%Re %Re %Re %Re\n", mpc_realref(z), mpc_imagref(z), mpc_realref(c), mpc_imagref(c));
    mpc_clear(z);
    mpc_clear(c);
    mpc_clear(i);
    mpc_clear(interior);
    mpfr_clear(p);
    return 0;
   */ 
  }
  return 1;
}
