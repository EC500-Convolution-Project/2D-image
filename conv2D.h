/*
	Parallelization of 2D Convolution on GPU
	Michael Clifford, Patrick Dillon, Frank Tranghese
	EC500 E1 - Parallel Programming
	Group 1
*/
#ifndef CONV2D_H
#define CONV2D_H

#define MPI_REAL_TYPE MPI_DOUBLE
#define MAX_MPI_SIZE 16

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <complex>
#include <string>
using namespace std;

#pragma acc routine seq
void circ(double * array, double ** circArray, int N);
#pragma acc routine seq
void circ2(double ** hpad, double ** circH, int N, int M);
#pragma acc routine seq
void padder2D(double ** f, double ** h, double ** fpad, double** hpad, int pad);
void stacker(double ** image, double * stacked, int N);
void unstacker(double * stacked, double ** image, int N);
#pragma acc routine seq
void conv2(double ** A, double * fstacked, double * output, int N);

#endif