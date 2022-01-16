/*

find multiplier for given c

for 
fc(z) = z^2+c

it can be used for : 
* multiplier map : https://commons.wikimedia.org/wiki/File:Mandelbrot_set_-_multiplier_map.png
* internal rays
* checking stability of periodic points z




c console program

gcc m.c -Wall -lm
./a.out


*/
#include <stdio.h>
#include <math.h>
#include <complex.h>

static const double twopi = 6.283185307179586;

double cabs2(double complex z) {
  return creal(z) * creal(z) + cimag(z) * cimag(z);
}




/* newton function : N(z) = z - (fp(z)-z)/f'(z)) */
complex double N( complex double c, complex double zn , int pMax, double er2){

  
	complex double z = zn;
	complex double d = 1.0; /* d = first derivative with respect to z */
	int p; 

	for (p=0; p < pMax; p++){

   		//printf ("p = %d ;  z = %f ; %f ;  d = %f ; %f \n", p, creal(z), cimag(z), creal(d), cimag(d)); 
   		d = 2*z*d; /* first derivative with respect to z */
   		z = z*z +c ; /* complex quadratic polynomial */
   		//if (cabs(z) >er2) break;
	}

 
 
	 //printf (" next \n\n"); 
	 //if ( cabs2(d) > 2) 
	z = zn - (z - zn)/(d - 1) ;
    	return z;
}


/* 
compute periodic point of complex quadratic polynomial
using Newton iteration = numerical method 

*/

complex double give_periodic(complex double c, complex double z0, int period, double eps2, double er2){

complex double z = z0;
complex double zPrev = z0; // prevoiuus value of z
int n ; // iteration
const int nMax = 64;

for (n=0; n<nMax; n++) {
     
    z = N( c, z, period, er2);
    if (cabs2(z - zPrev)< eps2) break;
    
    zPrev = z; }

return z;
}

complex double aproximate_multiplier(complex double c, int period, double eps2, double er2){
     
     complex double z;  // variable z 
     complex double zp ; // periodic point 
     complex double zcr = 0.0; // critical point
     complex double d = 1.0; // derivative = multiplier
     
     
     
     
     int p;
     
     zp =  give_periodic( c, zcr, period,  eps2, er2); // Find periodic point z0 such that f^p(z0,c)=z0 using Newton's method in one complex variable
     //zp = find(-1, 0, period, c); 
     //printf (" zp = %f ; %f p = %d \n", creal(zp), cimag(zp), period); 
     
     // Find w by evaluating first derivative with respect to z of f^p at z0 
	if ( cabs2(zp)<er2) {
     
     		//printf (" zp = %f ; %f p = %d \n", creal(zp), cimag(zp), period); 
     		z = zp;
     		for (p=0; p < period; p++){
        		d = 2*z*d; /* first derivative with respect to z */
        		z = z*z +c ; /* complex quadratic polynomial */
     			}
        	}
     		else {d= 10000;}

	return d;
}




complex double give_multiplier(complex double c, int period){


	double eps2 = 1e-16;
     	double er2 = 100.0; // bailout = ER2 = (EscapeRadius)^2
	complex double m;
	switch(period){
		case 1  : m = 1.0 - csqrt(1.0-4.0*c); 					break; // explicit
		case 2  : m = 4.0*c + 4; 			 					break; //explicit
		default : m = aproximate_multiplier(c, period, eps2, er2);	break; //  numerical approximation

	}

	return m;

}

/* argument in turns of complex number z  */

double cturn( double complex z){
double t;

  t =  carg(z);
  t /= twopi; // now in turns
  if (t<0.0) t += 1.0; // map from (-1/2,1/2] to [0, 1) 
  return (t);
}





// *****************************************************

int main (){

	complex double examples[7] = {
	0.254763149847213 		+0.498166625409228*I, 
	0.251518755582843  		+0.498567173513134*I,
	0.254418285260390  		+0.497476896235582*I, 
	0.254763149847213 		+0.498166625409228*I,
	0.251518755582843  		+0.498567173513134*I,
	0.250548544047613  		+0.499466516591390*I,
	0.2478165365298108694533 - 0.5027951422378465886278*I   // location by Bernd Schmidt https://github.com/bernds/GAPFixFractal
	
	};


	// input
	complex double c ;
	int period= 4;
	
	
	// output
	complex double m ; //  multiplier
	double angle ;
	double radius ;
	
	int iMax = sizeof(examples)/sizeof(examples[0]);
	
	for (int i = 0 ; i < iMax; i++)	
	{
		c = examples[i];
		m = give_multiplier( c, period);
	
		angle = cturn(m);
		radius = cabs(m);
		printf (" c = %.16f%+.16f*I \t m(c) = %.16f%+.16f*I \t r(m) = %.16f \t t(m) = %.16f \tperiod = %d\n", creal(c), cimag(c), creal(m), cimag(m), radius, angle , period);
	}
	
	return 0;
}



