/*
	Parallelization of 2D Convolution on GPU
	Michael Clifford, Patrick Dillon, Frank Tranghese
	EC500 E1 - Parallel Programming
	Group 1
*/

#include "conv2D.h"
using namespace std;

/*
	*** INPUTS ***
	array is an array of N doubles that need to be made circulant (assumes already zero padded)
	circArray is where the circulant matrix produced will be stored
	N is # of entries in array
	
*/
void circ(double * array, double ** circArray, int N){
	int x,y,dim,dim2;

	//lower triangle
	for(x=0;x<N;x++){
		for(y=0;y<N;y++){
			if(x+y < N){
				circArray[y+x][y] = array[x];
			}
		}
	}

	//upper triangle, skip middle since already done
	dim = N-2;
	dim2 = 0;
	for(x=0;x<N;x++){
			
			for(y=1;y<N;y++){
				if(y+dim<N && y+dim2<N){
					circArray[x][y+dim2] = array[y+dim];
				}
				dim=dim-2;
			}
		
			dim2++;
			dim=N-2;
	}
	
}

/*
	*** INPUTS ***
	hpad is 2D zero-padded h to make into block circulant matrix
	circH is storage for block circulant matrix
	N is # of entries in columns of hpad, since each column a will need to be circ()
	M is # of columns in hpad
*/
void circ2(double ** hpad, double ** circH, int N, int M){

	int i,j,k,x,y,dim,dim2;
	double * arrayTmp = new double[N];
	double ** matrixTmp = new double*[N];
	for(i=0;i<N;i++){
		matrixTmp[i] = new double[N];
	}

	//for columns in hpad, create circulant matrices - lower triangle
	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
			arrayTmp[j] = hpad[j][i];
		}

		circ(arrayTmp,matrixTmp,N); // get circulant of that column
		
		//place into correct position
		for(dim=0;dim<N;dim++){
			for(x=0;x<N;x++){
				for(y=0;y<N;y++){
					if((x+(N*dim)+(i*N)) < (N*M)){
						circH[(x+(N*dim)+(i*N))][y+(N*dim)] = matrixTmp[x][y];
					}
				}
			}
		}


	}

	//for columns in hpad, create circulant matrices - upper triangle
	//skip middle portion, since already complete
	dim2 = 1;
	for(i=M-1;i>0;i--){
		for(j=0;j<N;j++){
			arrayTmp[j] = hpad[j][i];
		}

		circ(arrayTmp,matrixTmp,N); // get circulant of that column
		
		//place into correct position
		for(dim=dim2;dim<N;dim++){
			for(x=0;x<N;x++){
				for(y=0;y<N;y++){
					if((y+(N*dim2)) < (N*M)){
						circH[(x+(N*(dim-dim2)))][y+(N*dim)] = matrixTmp[x][y];
					}
				}
			}
		}

		dim2++;
	}
}

/*
	*** INPUTS ***
	f is 2D matrix of our signal/image
	h is 2D matrix of our TF/Filter/Kernel
	fpad is place to put zero-padded f
	hpad is place to put zero-padded h
*/
void padder2D(double ** f, double ** h, double ** fpad, double** hpad, int N){

	int x, y;

	int size_f = *(&f[0] + 1) - f[0] -2 ;

	//int size_h = *(&h[0] + 1) - h[0]-2 ;

	for(x = 0; x <= size_f; x++){
		for(y = 0; y <= size_f; y ++){
			fpad[x][y] = f[x][y]; 
		}
	}



	//for(x = 0; x < size_h; x++){
	//	for(y = 0; y < size_h; y ++){
	//		hpad[x+pad][y+pad] = h[x][y]; 
	//	}
	//}


	


}

/*
	*** INPUTS ***
	which - char signifying if stacking or unstacking (s or u)
	image - matrix to be row stacked or storage for unstacked image
	stacked - array to be unstacked or storage for stacked image
*/
void stacker(double ** image, double * stacked, int N){

	int x,y;
	int position = 0;



	for (x = 0; x < N; x++){
		for(y = 0; y < N; y++){
			stacked[position] = image[x][y];
			position++;
		}
	}

}


/*
	*** INPUTS ***
	image - zero matrix to be filled 
	stacked - array to be unstacked
*/

void unstacker(double * stacked, double ** image, int N){

	int x,y; 
	int position = 0;

	for (x = 0; x < N; x++){
		for (y = 0; y < N; y++){

			image[x][y] = stacked[position];
			position++;

		}
	}

}

/*
	*** INPUTS ***
	A  is 2D block circulant matrix
	fstacked is 1D array of stacked image rows
	output is an empty array that will be populated through the convolution
*/
void conv2(double ** A, double * fstacked, double * output, int N){

	int x, y; 
	int position = 0;
	int position2 = 0;


	for(x = 0; x < N; x++){
		for(y = 0; y < N ; y++){

					output[position] += A[x][y]*fstacked[position2];
					position2 ++;
					

		}

		position2 = 0;
		position++;



}
}

void conv2_dir(double ** A, double ** filter, double ** output, int N, int filter_N){

	int x, y; 
	int x_pos, y_pos;

	for(x = 0; x < N; x++){
		for(y = 0; y < N ; y++){

			for( x_pos = 0; x_pos <filter_N; x_pos++){
				for(y_pos = 0 ; y_pos < filter_N; y_pos++){


					if (x+x_pos < N && y+y_pos < N){
					output[x][y] += A[x+x_pos][y+y_pos]*filter[x_pos][y_pos];

					//cout << x+x_pos <<" , " << y+y_pos << endl;
				}

                 
				}
			}

		}
	}



}