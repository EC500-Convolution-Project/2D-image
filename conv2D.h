/*
	Parallelization of 2D Convolution on GPU
	Michael Clifford, Patrick Dillon, Frank Tranghese
	EC500 E1 - Parallel Programming
	Group 1
*/
#ifndef CONV2D_H
#define CONV2D_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <complex>
#include <string>
using namespace std;

void circ(double * array, double ** circArray, int N);
void circ2(double ** hpad, double ** circH, int N, int M);
void padder2D(double ** f, double ** h, double ** fpad, double** hpad);
void stacker(double ** image, double * stacked, int N);
void unstacker(double * stacked, double ** image, int N);
void conv2(double ** A, double * fstacked);

#endif