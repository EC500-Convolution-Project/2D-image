/*
	Frank Tranghese
	U14307799
	EC500 E1
	2D FFT for Project
	Initial Code provided by Professor Brower.
	Additional Reference:
	https://gist.github.com/lukicdarkoo/3f0d056e9244784f8b4a
	Shady Boukhary - for OpenACC Midwestern State University
	File: fft.c
*/

#include "fft.h"

void makePhase(Complex *omega, int N ){

	int k;

	for(k = 0; k < N; k++){

		omega[k] = exp(2.0*PI*I*(double)k/(double) N);

	}
}

void makePhase2(Complex **omega, int N ){

	int k,j;

	for(k = 0; k < N; k++){
		for(j=0; j<N;j++){
			omega[k][j] = exp(2.0*PI*I*(((double)k/(double) N) + ((double)j/(double)N)));
		}
	}
}

void FFT2(Complex ** F, int N){

	int k,x,j,i;
	Complex * evens = new Complex[N/2];
	Complex * odds = new Complex[N/2];
	Complex * evens2 = new Complex[N/2];
	Complex * odds2 = new Complex[N/2];
	Complex * omegaTmp = new Complex[N];
	makePhase(omegaTmp,N);

	if(N <= 1){
		return;
	}
	
	//for each row
	for(i=0;i<N;i++){
		//split even and odd rows
		for(j=0;j<N/2;j++){
			evens[j] = F[i][2*j];
			odds[j] = F[i][(2*j)+1];
		}
		
		FFT(evens,N/2);
		FFT(odds,N/2);

		for(k = 0; k < N/2; k++){

			F[i][k] = evens[k] + (omegaTmp[k]*odds[k]);
			F[i][N/2 + k] = evens[k] - (omegaTmp[k]*odds[k]);

		}
	}
	
	//for each column
	for(i=0;i<N;i++){
		//split even and odd rows
		for(j=0;j<N/2;j++){
			evens2[j] = F[2*j][i];
			odds2[j] = F[(2*j)+1][i];
		}
		
		FFT(evens2,N/2);
		FFT(odds2,N/2);

		for(k = 0; k < N/2; k++){

			F[k][i] = evens2[k] + (omegaTmp[k]*odds2[k]);
			F[N/2 + k][i] = evens2[k] - (omegaTmp[k]*odds2[k]);

		}
	}
}


void FFTinv2(Complex ** F, Complex ** Ftilde, Complex ** omega, int N){

	int x,k,i;

//for every row
	for(i=0;i<N;i++){
		for(x = 0; x < N; x++){
		
			F[i][x] = 0.0;

			for(k = 0; k < N; k++){

				F[i][x] +=pow(omega[i][k],-x)*Ftilde[i][k]/(double) N;

			}
		}
	}

	//for every column
	for(i=0;i<N;i++){
		for(x = 0; x < N; x++){
		
			F[x][i] = 0.0;

			for(k = 0; k < N; k++){

				F[x][i] +=pow(omega[k][i],-x)*Ftilde[k][i]/(double) N;

			}
		}
	}
}


void FFT(Complex * F, int N){

	int k,x,j;
	Complex * evens = new Complex[N/2];
	Complex * odds = new Complex[N/2];
	Complex * omegaTmp = new Complex[N];
	makePhase(omegaTmp,N);

	if(N <= 1){
		return;
	}

	//split even and odd
	for(j=0;j<N/2;j++){
		evens[j] = F[2*j];
		odds[j] = F[(2*j)+1];
	}

	FFT(evens,N/2);
	FFT(odds,N/2);

	for(k = 0; k < N/2; k++){

			F[k] = evens[k] + (omegaTmp[k]*odds[k]);
			F[N/2 + k] = evens[k] - (omegaTmp[k]*odds[k]);

		}
}