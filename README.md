wickerlib
=========

All my one-off implementations to figure out how things work.

**dft.c implements the discrete Fourier transform**

The summation() and complex\_demo() functions are reference functions for how complex.h and summation work. dft() implements the discrete Fourier transform on an input array of up to 20 complex elements and it depends on the complex.h and math.h libraries.

Compile with

<code>gcc -lm -std=c99 dft.c -o dft</code>

Run with

    ./dft 'int' 'filename'
    where 'int' is an integer between 1 and 20
    and 'filename' is a text file to catch output data

The code generates a set of 20 input x(t) and output X(k) array pairs that can be read into your graphing software of choice.

