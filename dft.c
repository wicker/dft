// comparing my dft() to teh compute_dft() function
// from http://www.nayuki.io/res/how-to-implement-the-discrete-fourier-transform/dft.c
// both are failing 
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#define ARGS 3
#define DATAPOINTS 4

#define M_PI 3.14159265358979323846264338327
// you can use no complex to remove 'complex' keyword 
//__STDC_NO_COMPLEX__

// or implement them in some sort of struct
//typedef struct {
//  int16_t r;
//  int16_t i;
//} complex;

typedef enum { false, true } bool;

void complex_demo();
void dft(double complex in[], double complex out[], int len);
int dft_test();
void print_complex_array(int len, double complex array[]);
void compute_dft(double inreal[], double inimag[], double outreal[], double outimag[], int n);

void print_complex_array(int len, double complex array[]) {

  int i;
  for (i = 0; i < len; i++)
    printf("array[%d] = %.2f + %.2fi\n",i,__real__ array[i],__imag__ array[i]);
  
}


/* 
 * Computes the discrete Fourier transform (DFT) of the given vector.
 * All the array arguments must have the same length.
 */
void compute_dft(double inreal[], double inimag[], double outreal[], double outimag[], int n) {
  int k;
  for (k = 0; k < n; k++) {  /* For each output element */
    double sumreal = 0;
    double sumimag = 0;
    int t;
    for (t = 0; t < n; t++) {  /* For each input element */
      double angle = 2 * M_PI * t * k / n;
      sumreal +=  inreal[t] * cos(angle) + inimag[t] * sin(angle);
      sumimag += -inreal[t] * sin(angle) + inimag[t] * cos(angle);
    }
    outreal[k] = sumreal;
    outimag[k] = sumimag;
  }
}

// so I remember later how to work with complex numbers
void complex_demo() {

  int i;
  double complex a,b,c;

  printf("---------------------------------------\n");
  printf("some examples of working with complex.h\n");
  printf("---------------------------------------\n");

  // access real and imaginary parts with these operators
  __real__ a = 1.4f;
  __imag__ a = 2.0f;

  // or set entire number in this form
  c = 1.0 + 3.0I;

  // otherwise, they work like regular variables
  b = a;
  double complex x[3] = {a,b,c};

  // access the contents with the same operators
  printf("a = %.2f %.2fi\n",__real__(a), __imag__(a));
  printf("b = %.2f %.2fi\n",__real__(b), __imag__(b));
  printf("c = %.2f %.2fi\n",__real__(c), __imag__(c));

  for (i = 0; i < 3; i++) {
    printf("x[%d] = %.2f %.2fi\n",i,__real__(x[i]),__imag__(x[i]));
  }

  // add complex numbers
  c = a + b;
  printf("a + b = %.2f + %.2fi\n",__real__(c),__imag__(c));
  
  // multiply complex numbers
  c = a * b;
  printf("a * b = %.2f + %.2fi\n",__real__(c),__imag__(c));

  // print out pi
  printf("pi = %.10f\n",M_PI);
  printf("---------------------------------------\n");

}

// demo summation
// a(t) = t + 2
// b(t) = t * k
// X(k) = sum of a(t) * b(t) 
// where t0 = 0 and n = 3 but sum til n - 1
void summation() {
  int t,k;
  int n = 3;
  int X[10] = {0};
  printf("---------------------------------------\n");
  printf("      non-complex summation demo       \n");
  printf("---------------------------------------\n");
  for (k = 0; k < 10; k++) {
    for (t = 0; t < n; t++)
      X[k] += (t+2)*(k*t);
    printf("X[%d] = %d\n",k,X[k]);
  }
  printf("---------------------------------------\n");
}

// discrete fourier transform
// assumes the arrays are the same length
// assumes the arrays are x[t] in and X[k] out
void dft(double complex in[],double complex out[], int len) {
  int k = 0, t = 0;
  double angle = 0.0;
  // set up summation
  for (k = 0; k < len; k++) {
    for (t = 0; t < len; t++) {
      angle = (2 * M_PI * t * k)/len;
      //printf("%.2f\t%.2f\t%.2f\n",angle,cos(angle),sin(angle));
      __real__ out[k] += __real__ in[t] * cos(angle) + __imag__ in[t] * sin(angle);
      __imag__ out[k] += -(__real__ in[t]) * sin(angle) + __imag__ in[t] * cos(angle);
    }
  }
}

int dft_test(int test) {

  printf("---------------------------------------\n");
  printf("              dft test #%d              \n",test);
  printf("---------------------------------------\n");

  double inreal[10];
  double inimag[10];
  double outreal[10];
  double outimag[10];
  double *pir,*pii,*por,*poi;
  pir = inreal;
  pii = inimag;
  por = outreal;
  poi = outimag;

  int len = 4;
  double complex a[10] = {0.0+0.0I};
  double complex b[10] = {0.0+0.0I};
  double complex *pa = a, *pb = b;

  switch(test) {
    case 1:
      __real__ a[0] = 2.00;
      dft(pa,pb,len);
      printf("input array\n");
      print_complex_array(len,pa);
      printf("output array\n");
      print_complex_array(len,pb);
      break;
    case 2:
      __real__ a[1] = 1.00;
      dft(pa,pb,len);
      printf("input array\n");
      print_complex_array(len,pa);
      printf("output array\n");
      print_complex_array(len,pb);
      break;
    case 3:
      __real__ inreal[0] = 1.00;
      compute_dft(pir,pii,por,poi,len);
      printf("input array\n");
      int i;
      for (i = 0; i < len; i++)
        printf("%.2f + %.2fi\n",pir[i],pii[i]);
      printf("output array\n");
      for (i = 0; i < len; i++)
        printf("%.2f + %.2fi\n",por[i],poi[i]);
      break;
    default:
      printf("the requested test case does not exist.\n");
  } 
  

  return 0;
}

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("usage: ./dft <int> where <int> is an integer between and 3.\n");
    return -1;
  }

  int test = atoi(argv[1]);
  dft_test(test);
  //complex_demo();
  //summation();
  return 0;
}

