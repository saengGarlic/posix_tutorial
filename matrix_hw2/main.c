#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "matrix.h"

void matinit(int ***p_a, int ***p_b, int ***p_c, int len);
void print_matrix(int** , char*, int);
double wtime();

int main(int argc, char** argv)
{
	int i, j, k;
	int **a;
	int **b;
	int **c;
	int len, num_thread;
	double start, stop;

	if (argc == 2){
		len = atoi(argv[1]);
		num_thread = 1;
	}//else if(argc >= 3){
//		len = atoi(argv[1]);
//		num_thread = atoi(argv[2]);
//	}
	else{
	//	printf("Usage: matrix [row] [num_thread]\n");
	//	exit(1);
	}

	matinit(&a, &b, &c, len);

	//single threaded

	start = wtime();
	if(mat_mul(a, b, c, len) != 0){
		fprintf(stderr, "Failed Matrix multiplication\n");
		exit(1);
	};
	stop = wtime();

	if(1){//argv[3] != NULL){
		print_matrix(a, "a", len);
		print_matrix(b, "b", len);
		print_matrix(c, "c", len);
	}

	printf("Single Threaded Processing time: %f\n", stop - start);


	//multi threaded
	start = wtime();
	if(mat_mul_th(a, b, c, len) != 0){
		fprintf(stderr, "Failed Matrix multiplication\n");
		exit(1);
	};
	stop = wtime();
	if(1){//argv[3] != NULL){
		print_matrix(a, "a", len);
		print_matrix(b, "b", len);
		print_matrix(c, "c", len);
	}
	printf("Multi Threaded Processing time: %f\n", stop - start);
	return 0;


}

void matinit(int ***p_a, int ***p_b, int ***p_c, int len)
{
	int **a;
	int **b;
	int **c;
	int i, j;

	a = malloc(len * sizeof(int*));
	b = malloc(len * sizeof(int*));
	c = malloc(len * sizeof(int*));

	for (i = 0; i < len; i++){
		a[i] = (int*)malloc(len * sizeof(int));
		b[i] = (int*)malloc(len * sizeof(int));
		c[i] = (int*)malloc(len * sizeof(int));
	}
	srandom((unsigned int)time(NULL));
	for (i = 0; i < len; i++){ //i(row)
		for (j = 0; j < len; j++){ //j(column)
			a[i][j] = random() % 10;
			b[i][j] = random() % 10;
			c[i][j] = 0;
		}
	}
	*p_a = a;
	*p_b = b;
	*p_c = c;
}

double wtime()
{
	static int sec = -1;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	if (sec < 0) sec = tv.tv_sec;

	return (tv.tv_sec - sec) + 1.0e-6*tv.tv_usec;
}
void print_matrix(int** matrix, char* name, int len)
{
	printf("== %s matrix =====================\n", name);
	for (int i = 0; i < len; i++){ //i(row)
		for (int j = 0; j < len; j++){ //j(column)
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}

}
