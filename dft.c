// comparing my dft() to teh compute_dft() function
// from http://www.nayuki.io/res/how-to-implement-the-discrete-fourier-transform/dft.c
// both are failing 
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#define M_PI 3.14159265358979323846264338327

// you can use no complex to remove 'complex' keyword 
//__STDC_NO_COMPLEX__

// or implement them in some sort of struct
//typedef struct {
//  int16_t r;
//  int16_t i;
//} complex;

typedef enum { false, true } bool;

void print_complex_array(int len, double complex array[], FILE* outfile, char* t);
void complex_demo();
void summation();
void dft(double complex in[], double complex out[], int len);
int dft_test(int len, FILE* outfile);
void print_dft_case(int len, double complex inarray[],double complex outarray[],FILE* outfile);

// this generates the particular gnuplot file format we want
void print_dft_case(int len, double complex inarray[],double complex outarray[],FILE* outfile) {
  int i;
  for (i = 0; i < len; i++)
    fprintf(outfile,"%d %.2f %.2f %.2f %.2f\n",i,__real__ inarray[i], __imag__ inarray[i], __real__ outarray[i], __imag__ outarray[i]);
  fprintf(outfile,"\n\n"); // add this to add output case breaks in the dat file
}


void print_complex_array(int len, double complex array[], FILE* outfile, char* t) {
  int i;
  for (i = 0; i < len; i++)
    fprintf(outfile,"%d %s %.2f %.2f\n",i,t,__real__ array[i],__imag__ array[i]);
  fprintf(outfile,"\n\n"); // add this to add output case breaks in the dat file
}

// some examples of working with complex.h library
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
  int X[10] = {0.0};
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

int dft_test(int len,FILE* outfile) {

  printf("---------------------------------------\n");
  printf("              dft test              \n");
  printf("---------------------------------------\n");

  double complex a[20] = {0.0+0.0I};
  double complex b[20] = {0.0+0.0I};
  double complex *pa = a, *pb = b;

  for (int i = 0; i < len; i++) {
    a[i] = 1.00;
    dft(pa,pb,len);
    fprintf(outfile, "\"case %d\"\n",i);
    print_dft_case(len,pa,pb,outfile);
//  fprintf(outfile,"\"case %d input\"\n",i);
//  printf("input array #%d\n",i);
//  print_complex_array(len,pa,outfile,"in");
//  fprintf(outfile,"\"case %d output\"\n",i);
//  printf("output array #%d\n",i);
//  print_complex_array(len,pb,outfile,"out");
    a[i] = 0.00;
  }

  return 0;
}

int main(int argc, char *argv[]) {

  if (argc != 3) {
    printf("usage: ./dft <int> <filename>\n"
    "where <int> is an integer between 1 and 20\n"
    "and <filename> is a text file to catch output data\n");
    return -1;
  }

  int len = atoi(argv[1]);
  if (len > 20 || len < 1) {
    printf("usage: ./dft <int> <filename>\n"
    "where <int> is an integer between 1 and 20\n"
    "and <filename> is a text file to catch output data\n");
    return -1;
  }

  FILE* outfile = fopen(argv[2],"wb");
  dft_test(len,outfile);
  fclose(outfile);

  //complex_demo();
  //summation();
    return 0;
}

