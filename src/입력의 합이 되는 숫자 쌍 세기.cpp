#pragma warning(disable:4996)
#include <cstdio>
#include <cstdlib>
#include <queue>
using namespace std;

int binary_search(int A[], int n, int key) {
	int low = 0;
	int mid = 0;
	int high = n - 1;

	while (low <= high) {
		mid = (low + high) / 2;
		if (key == A[mid])		        //탐색 성공
			return mid;
		else if (key < A[mid])			//탐색 범위 아래쪽
			high = mid - 1;
		else if (key > A[mid])         //탐색 범위 위쪽
			low = mid + 1;
	}
	return -1;                              //탐색 실패
}
int radix_sort_getmax(int* A, int n) {
	int max_val = 0;
	for (int i = 0; i < n; i++)
		if (max_val < A[i])
			max_val = A[i];
	int max_radix = 1;
	while (max_val / 10 > 0) {
		max_val /= 10;
		max_radix *= 10;
	}
	return max_radix;
}
void radix_sort(int* A, int n) {
	int max_radix = radix_sort_getmax(A, n);
	queue<int> q[10];

	for (int i = 1; i <= max_radix; i *= 10) {
		for (int j = 0; j < n; j++) {
			int digit = 0;

			if (A[j] >= i) {
				digit = (A[j] / i) % 10;
			}

			q[digit].push(A[j]);
		} //queue에 넣는 작업.

		int idx = 0;
		for (int j = 0; j < 10; j++) {
			while (!q[j].empty()) {
				A[idx] = q[j].front();
				q[j].pop();
				idx++;
			}
		} //queue에서 빼내는 작업.
	}
}
void print_test(int* A, int n) {
	for (int i = 0; i < n; i++)
		printf("[%d]=%d\t", i, A[i]);
	printf("\n");
}

int main(int argc, char* argv[]) {
	int n = 0; //배열의 길이
	int m = 0; //입력 합
	int count = 0;
	scanf("%d %d", &n, &m);

	int* arr = (int*)calloc(n, sizeof(int));
	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	//print_test(arr, n); //Test
	radix_sort(arr, n);
	//print_test(arr, n); //Test

	for (int i = 0; i < n; i++) {
		if (binary_search(arr, n, m - arr[i]) != (-1)) { //찾는 값이 있는 경우
			if (arr[i] != m - arr[i]) {
				//printf("Pair : %d %d\n", arr[i], m - arr[i]); //Test
				count++;
			}
		}
	}

	printf("%d", count / 2);

	return 0;
}