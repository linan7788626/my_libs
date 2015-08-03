#include <stdlib.h>

void test(int **out1, int **out2) {
	int i;
	int N;
	N = 10;
	int *data1, *data2;
	data1 = (int *)malloc(sizeof(int) * (N+1));
	data2 = (int *)malloc(sizeof(int) * (N+1));
	data1[0] = N;
	data2[0] = N;
	for (i = 0; i < N; i++){
		data1[i+1] = i;
		data2[i+1] = i * 2;
	}
	*out1 = data1;
	*out2 = data2;
}

void return_m(int **out) {
	int i;
	int N;
	N = 10;
	int *data;
	data = (int *)malloc(sizeof(int) * (N+1));
	data[0] = N;
	for (i = 0; i < N; i++){
		data[i+1] = i;
	}

	*out = data;
}
