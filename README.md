# Parallelizing 2D Convolution of GPU using OpenACC

Boston University EC500 E1 - Parallel Programs and High Powered Computing Project

## Goals
2D convolution is a widely-used, simple, yet computationally inefficient algorithm. Our aim was to explore methods to speed it up by implementing parallelization with GPU’s with OpenACC

## File Structure
..* cpp file contains C++ files of convolution methods. These had to be convered to C code in order to run on BU's computing cluster

..* gpu file contains converted C code, parallelized using OpenACC.

..* fft file contains c++ files for 2D FFT, intended to use this to compare with direct convolution.

..* results folder contains our data and graphs for direct convolution timing for serial, multicore cpu, and gpu timings
