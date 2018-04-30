/*
	Frank Tranghese
	U14307799
	EC500 E1
	2D FFT for Project
	Initial Code provided by Professor Brower.
	Additional Reference:
	https://gist.github.com/lukicdarkoo/3f0d056e9244784f8b4a
	Shady Boukhary - for OpenACC Midwestern State University
	File: fft.h
*/

#ifndef FFT_H
#define FFT_H

#include <stdio>
#include <cmath>
#include <cstdlib>
#include <complex>

#define PI 3.141592653589793
#define I Complex(0.0, 1.0)
typedef complex <double> Complex;

void FFT2(Complex ** F, int N);
void FFTinv2(Complex ** F, Complex ** Ftilde, Complex ** omega, int N);
void FFT(Complex * F, int N);
void makePhase(Complex *omega, int N );
void makePhase2(Complex **omega, int N );

#endif