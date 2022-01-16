/*

find parameter c from it's multiplier
for 
fc(z) = z^2+c



c console program

gcc c.c -Wall -lm
./a.out


*/
#include <stdio.h>
#include <math.h>
#include <complex.h>




/*
https://mathr.co.uk/blog/2013-04-01_interior_coordinates_in_the_mandelbrot_set.html

There is an algorithm to find points on the boundary of the Mandelbrot set, 
given a particular hyperbolic component and the desired internal angle. 
It involves Newton's method in two complex variables to solve

Fp(z,c)=z∂∂z
Fp(z,c)=b

where 
F0(z,c)=z and 
Fq+1(z,c)=Fq(F(z,c)2+c), 
p is the period of the target component, 
and m=e2πiθ with the θ the desired internal angle. 
The resulting c is the coordinates of the point on the boundary. 
It can also be modified to find points in the interior, simply set m=re2πiθ with |r|≤1.

*/


complex double aproximate_c( const int p, const complex double center, const complex double m){


	complex double c = 0.0;
	return c;
}







complex double give_c(const int p, const complex double center, const double angle, const double r )
{
	/*
	input:
	Internal Radius = r in [0,1] ; double
  	Internal Angle In Turns = t  or theta in range [0,1) ; double  
  	p = period ; int 
  	
  	output = c = complex point of 2D parameter plane  
  	*/
  	

	complex double m = 0.0; // multiplier
	complex double c = 0.0; // result 
	double t = angle;
	
	t = t*2*M_PI; // from turns to radians
	m = r* cexp(I*t); // point of unit circle
  		
	// map circle to component
	switch (p){
	
		case 1: c = (2.0*m - m*m)/4.0; break;
		case 2: c = (m -4.0)/ 4.0; break;
		default : c = aproximate_c( p, center, m); // for higher periods there is no exact method; use numerical aproximation	 
	
  
	}
	return c; 
}


// *****************************************************

int main (){

	// input
	int p= 1;
	complex double center = 0.0; // = nucleus = center of hyperbolic component of the Mandelbrot set with period p ; there are more then 1 components with periods > 2
	double angle = 0.0;
	double radius = 1.0;
	// output
	complex double c ;
	
	
	c = give_c(p, center, angle, radius);
	printf (" c = %.16f%+.16f*I\n", creal(c), cimag(c));

	
	return 0;
}

