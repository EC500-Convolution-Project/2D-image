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

void FFT2(double ** F, Complex **Ftilde, int N){

	int k,x,j,i;
	Complex * evens = new Complex[N/2];
	Complex * odds = new Complex[N/2];
	Complex * evens2 = new Complex[N/2];
	Complex * odds2 = new Complex[N/2];
	Complex * omegaTmp = new Complex[N];
	makePhase(omegaTmp,N);

	//make Complex F
	Complex ** Ftmp = new Complex*[N];
	for(int i=0;i<N;i++){
		Ftmp[i] = new Complex[N];
		for(int j =0;j<N;j++){
			Ftmp[i][j] = (Complex)F[i][j]; 
		}
	}

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

			Ftilde[i][k] = evens[k] + (omegaTmp[k]*odds[k]);
			Ftilde[i][N/2 + k] = evens[k] - (omegaTmp[k]*odds[k]);

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

			Ftilde[k][i] = evens2[k] + (omegaTmp[k]*odds2[k]);
			Ftilde[N/2 + k][i] = evens2[k] - (omegaTmp[k]*odds2[k]);

		}
	}
}


void FFTinv2(double ** F, Complex ** Ftilde, Complex ** omega, int N){

	int x,k,i;
	Complex ** Ftmp = new Complex*[N];
	for(i=0;i<N;i++){
		Ftmp[i] = new Complex[N];
	}
//for every row
	for(i=0;i<N;i++){
		for(x = 0; x < N; x++){
		
			F[i][x] = 0.0;

			for(k = 0; k < N; k++){

				Ftmp[i][x] +=pow(omega[i][k],-x)*Ftilde[i][k]/(double) N;

			}
		}
	}

	//for every column
	for(i=0;i<N;i++){
		for(x = 0; x < N; x++){
		
			F[x][i] = 0.0;

			for(k = 0; k < N; k++){

				Ftmp[x][i] +=pow(omega[k][i],-x)*Ftilde[k][i]/(double) N;

			}
		}
	}

	for(i=0;i<N;i++){
		for(k=0;k<N;k++){
			F[i][k] = (double)abs(real(Ftmp[i][k]));
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

void allToAll(Complex **Ftilde, Complex **Htilde, double ** F, int N){

	//storage for intermediate value
	Complex ** FtildeTmp = new Complex*[N];
	//storage for omega
	Complex ** omegaTmp = new Complex*[N];

	for(int k=0;k<N;k++){
		FtildeTmp[k] = new Complex[N];
		omegaTmp[k] = new Complex[N];
	}
	makePhase2(omegaTmp,N);

	for(int i=0;i<N;i++){
		for(int j =0;j<N;j++){
			FtildeTmp[i][j] = Ftilde[i][j] * Htilde[i][j];
		}
	}

	FFTinv2(F,FtildeTmp,omegaTmp,N);
}

void FFTConv(double ** F, double ** H, double ** output, int N){

	Complex ** Ftildetmp = new Complex*[N];
	Complex ** Htildetmp = new Complex*[N];
	for(int i=0;i<N;i++){
		Ftildetmp[i] = new  Complex[N];
		Htildetmp[i] = new  Complex[N];
	}

	FFT2(F,Ftildetmp,N);
	FFT2(H,Htildetmp,N);
	allToAll(Ftildetmp,Htildetmp,output,N);
}