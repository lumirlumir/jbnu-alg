#pragma warning(disable:4996)
#include <stdio.h>

#define MIN2(a, b) (((a) < (b)) ? (a) : (b))
#define MIN3(a, b, c) (((a) < (b)) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
#define MAX2(a, b) (((a) > (b)) ? (a) : (b))
#define MAX3(a, b, c) (((a) > (b)) ? ((a) > (c) ? (a) : (c)) : ((b) > (c) ? (b) : (c)))

int arr[2001][2001] = { 0 };
int memo[2001][2001] = { 0 };

int matrix_path(int n) {
	for (int i = 1; i <= n; i++) {
		for (int j = n - 1; j >= 0; j--) {
			if (memo[i][j + 1] == 0 && memo[i - 1][j] == 0 && memo[i - 1][j + 1] == 0)
				memo[i][j] = arr[i][j] + MIN3(memo[i][j + 1], memo[i - 1][j], memo[i - 1][j + 1]);
			else if (memo[i][j + 1] != 0 && memo[i - 1][j] == 0 && memo[i - 1][j + 1] == 0)
				memo[i][j] = arr[i][j] + memo[i][j + 1];
			else if (memo[i][j + 1] == 0 && memo[i - 1][j] != 0 && memo[i - 1][j + 1] == 0)
				memo[i][j] = arr[i][j] + memo[i - 1][j];
			else
				memo[i][j] = arr[i][j] + MIN3(memo[i][j + 1], memo[i - 1][j], memo[i - 1][j + 1]);
		}
	}
	return memo[n][0];
}

int main(void) {
	int n;
	scanf("%d", &n);
	
	for (int i = 1; i <= n; i++) // i는 세로
		for (int j = 0; j <= n - 1; j++) // j는 가로
			scanf("%d", &arr[i][j]);

	/*
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++)
			printf("%3d ", arr[i][j]);
		printf("\n");
	} //Test Case
	*/

	printf("%d", matrix_path(n));

	return 0;
}