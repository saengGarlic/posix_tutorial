#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

typedef struct {
	int row_size;
	int row_start;
	int** src1;
	int** src2;
	int** dst;
	int len;
} matmul_arg_t;


void *mat_mul_th_kernel(void *arg)
{
	int i, j, k;
	int result = 0;
	matmul_arg_t *parg = (matmul_arg_t*)arg;

	int row_size = parg->row_size;
	int row_start = parg->row_start;
	int **src1 = parg->src1;
	int **src2 = parg->src2;
	int **dst = parg->dst;
	int len = parg->len;

	//printf("%dth thread started @ %dth row\n", row_start/row_size, row_start);
	for (i = row_start; i < row_start + row_size; i++){
		for (j = 0; j < len; j++){ //j(column)
			result = 0;
			for (k = 0; k < len; k++){

				result += src1[i][k] * src2[k][j];
			}
			dst[i][j] = result;
		}
	}

}

int mat_mul_th(int** src1, int** src2, int** dst, int len, int num_thread)
{
	int i, j, k, res, row_size, residue, row_start;
	matmul_arg_t *arg;
	pthread_t *a_thread;
	void *thread_result;

	row_start = 0;
	row_size = (int)ceil((double)(len) / (double)(num_thread));
	residue =  len % num_thread;


	a_thread = (pthread_t*)malloc(sizeof(pthread_t) * num_thread);

	for (i = 0; i < num_thread; i++){
		arg = (matmul_arg_t*)malloc(sizeof(matmul_arg_t));

		arg->row_size = row_size;
		arg->row_start = row_start;
		arg->src1 = src1;
		arg->src2 = src2;
		arg->dst = dst;
		arg->len = len;

		//printf("residue: %d row_size: %d row_start: %d\n",residue,row_size,row_start);

		res = pthread_create(a_thread+i, NULL, mat_mul_th_kernel, (void*)arg);
		if(res != 0){
			perror("Thread creation failed\n");
			exit(EXIT_FAILURE);
		}
		residue--;
		row_start += row_size;
		if(residue == 0){
			row_size--;
		}
	}

	for (i = 0; i < num_thread; i++){
		res = pthread_join(a_thread[i], &thread_result);
		if(res != 0){
			perror("Thread join failed");
			exit(EXIT_FAILURE);
		}
	}


	return 0;
}

int mat_mul(int** src1, int** src2, int** dst, int len)
{
	int i, j, k;
	int result = 0;
	for (i = 0; i < len; i++){ //i(row)
		for (j = 0; j < len; j++){ //j(column)
		//	c[i][j] = a[i][j] + b[i][j] //add matrix
			result = 0;
			for (k = 0; k < len; k++){
				result += src1[i][k] * src2[k][j];
			}
			dst[i][j] = result;
		}
	}
	return 0;
}
