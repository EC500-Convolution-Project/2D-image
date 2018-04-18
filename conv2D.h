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

void circ(double * array, double ** circArray);
void padder2D(double ** f, double ** h, double ** fpad, double** hpad);
void stacker(double ** image, double * stacked, char which);

#endif