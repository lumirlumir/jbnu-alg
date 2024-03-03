#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

void radix_sort(int* A, int height, int width) {
	int max_radix = 10000000;
	queue<int> q[10];

	for (int j = 1; j <= max_radix; j *= 10) {
		for (int k = 0; k < height; k++) {
			int digit = 0;

			if (A[k] >= j) {
				digit = (A[k] / j) % 10;
			}

			q[digit].push(A[k]);
		} //queue에 넣는 작업.

		int idx = 0;
		for (int k = 0; k < 10; k++) {
			while (!q[k].empty()) {
				A[idx] = q[k].front();
				q[k].pop();
				idx++;
			}
		} //queue에서 빼내는 작업.
	}
}
void print_test(int*** A, int height, int width) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			printf("[%d][%d]=%d\t", i, j, (*A)[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void print_test(char*** A, int height, int width) {
	for (int i = 0; i < height; i++) {
		printf("str[%d] : %s\t", i, (*A)[i]);
		printf("\n");
	}
}
void print_test(int* A, int height, int width) {
	for (int i = 0; i < height; i++) {
		printf("arr1[%d] : %d\t", i, A[i]);
		printf("\n");
	}
}

int main(void) {
	int height = 0;
	int width = 3;
	scanf("%d", &height);
	//세로 정보 받음.

	int * arr = (int*)calloc(width, sizeof(int));
	//1차원 배열 동적할당.(int)

	char** str = (char**)calloc(height, sizeof(char*));
	for (int i = 0; i < height; i++)
		str[i] = (char*)calloc(9, sizeof(char));
	//2차원 배열 동적할당.(char)

	for (int i = 0; i < height; i++) {
		scanf("%d %d %d", &arr[0], &arr[1], &arr[2]);
		//printf("%d %d %d\n", arr[0], arr[1], arr[2]);

		if (1 <= arr[1] && arr[1] <= 9) {
			if (1 <= arr[0] && arr[0] <= 9)
				sprintf(str[i], "%d0%d0%d", arr[2], arr[1], arr[0]);// printf("case1");

			else
				sprintf(str[i], "%d0%d%d", arr[2], arr[1], arr[0]);// printf("case2");
		}
		else {
			if (1 <= arr[0] && arr[0] <= 9)
				sprintf(str[i], "%d%d0%d", arr[2], arr[1], arr[0]);// printf("case3");
			else
				sprintf(str[i], "%d%d%d", arr[2], arr[1], arr[0]);// printf("case4");
		}
	}
	free(arr);
	//값 입력받음.

	//print_test(&str, height, width); //Test

	int* arr1 = (int*)calloc(height, sizeof(int));
	for (int i = 0; i < height; i++)
		arr1[i] = atoi(str[i]);

	//print_test(arr1, height, width); //Test

	radix_sort(arr1, height, width);

	//print_test(arr1, height, width); //Test

	for (int i = 0; i < height; i++) {
		printf("%d %d %d\n", arr1[i] % 100, (arr1[i] / 100) % 100, arr1[i] / 10000);
		free(str[i]);
	}
	free(str);

	return 0;
}