wickerlib
=========

All my one-off implementations to figure out how things work.

**dft.c**

dft.c works with complex.h and math.h libraries

The summation() and complex\_demo() functions were functions to figur out how complex.h and summation work. 

dft() implements the discrete Fourier transform on an input array of up to 20 complex elements.

Compile with

<code>gcc -lm -std=c99 dft.c -o dft</code>

Run with

<code>usage: ./dft <int> <filename>
where <int> is an integer between 1 and 20
and <filename> is a text file to catch output data</code>

The code generates a set of 20 input x(t) and output X(k) array pairs that can be read into your graphing software of choice.

