#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SWAP(a, b, type) do { \
	type temp = a;					\
	a = b;								\
	b = temp;							\
} while(0)

int seqsearch(int list[], int left, int right, int searchnum) { 
   //printf("list 나열 \n");
   //for (int i = left; i <= right; i++) { //test
   //    printf("list[%d] = %d \n", i, list[i]);
   //}
   //printf("\n");

   for (int i = left; i <= right; i++) { 
       if (list[i] == searchnum) { 
           return i; 
       } 
   } 
   return -1; 
}
int partition(int A[], int left, int right) {  //정상작동, left : 왼쪽 끝, right : 오른쪽 끝
   int pivot = A[right];
   int i = left - 1;

   for (int j = left; j <= right - 1; j++) {
       if (A[j] <= pivot) {
           i += 1;
           int temp = A[i];
           A[i] = A[j];
           A[j] = temp;
       }
   }
   int temp = A[i + 1];
   A[i + 1] = A[right];
   A[right] = temp;

   return i + 1;
}
int quick_select(int A[], int l, int r, int i) {    //정상작동, i번째로 작은 수와 idx는 동일하지 않음.
   if (i <= 0 || i > r - l + 1) {//오류검사
       printf("quick_select error!\n");
       return -1;
   }

   if (l == r)
       return A[l];

   int p = partition(A, l, r);
   int k = p - l + 1;

   if (i < k) return quick_select(A, l, p - 1, i);
   else if (i == k) return A[p];
   else if (i > k) return quick_select(A, p + 1, r, i - k);
}
int mom_partition(int A[], int l, int r, int M) {
   int idx = seqsearch(A, l, r, M);
   //printf("mom_partition에서 idx = %d, l = %d, r = %d, M = %d\n", idx, l, r, M);   //Test

   int tmp = A[idx];
   A[idx] = A[r];
   A[r] = tmp;

   return partition(A, l, r); //????????
}

int mom_select(int A[], int l, int r, int i) {
   //printf("mom_select 함수 진입\n");
   //for (int i = l; i <= r; i++) { //test
   //    printf("A[%d]=%d \n", i, A[i]);
   //}
   //printf("\n");
   
   
   int n = r - l + 1;
   //printf("n값은 : %d\n", n); //Test

   if (n <= 5)
       return quick_select(A, l, r, i);
   else {
       /*1단계*/
       int G = (int)(ceil((double)n / 5.0));
       int* B = (int*)calloc(G, sizeof(int)); //동적할당
      //printf("G값은 : %d\n", G); //Test

       /*2-0단계*/
       for (int j = 0; j <= G - 2; j++) {
           B[j] = quick_select(A, j * 5 + l, (j + 1) * 5 - 1 + l, 3);
           //printf("B[%d] = %d\n", j, B[j]);    //Test
       }

       /*2-1단계*/
       if (n % 5 == 4)
           B[G - 1] = quick_select(A, (G - 1) * 5 + l, G * 5 - 2 + l, 2);
       /*2-2단계*/
       else if (n % 5 == 2)
           B[G - 1] = quick_select(A, (G - 1) * 5 + l, G * 5 - 4 + l, 1);
       /*2-3단계*/
       else if (n % 5 == 1)
           B[G - 1] = quick_select(A, (G - 1) * 5 + l, G * 5 - 5 + l, 1);
       else if (n % 5 == 3)
           B[G - 1] = quick_select(A, (G - 1) * 5 + l, G * 5 - 3 + l, 2);
       else if (n % 5 == 0)
           B[G - 1] = quick_select(A, (G - 1) * 5 + l, G * 5 - 1 + l, 3);

       //printf("B[%d] = %d\n", G-1, B[G-1]);    //Test

       /*3단계*/
       //printf("3단계 mom_select 진입\n");
       int M = mom_select(B, 0, G - 1, (int)(ceil((double)G / 2.0)));
       //printf("M = %d\n", M);    //Test
      
       /*4단계*/
       int p = mom_partition(A, l, r, M);

       //printf("p = %d\n", p);    //Test

       int k = p - l+1;

       printf("%d %d %d %.2lf\n", M, k, n, (double)k / n);

       /*5단계*/
      //printf("5단계 mom_select 진입\n");
       free(B);
       if (i < k) return mom_select(A, l, p - 1, i);
       else if (i == k) return A[p];
       else if (i > k) return mom_select(A, p + 1, r, i - k);
   }
}

int main(int argc, char* argv[]) {
	int n, i = 0;
   int tmp[10] = { 3,2,4,5,7,8,9,0,6,1 };

	scanf("%d %d", &n, &i);

	int* A = (int*)calloc(n, sizeof(int));

	for (int j = 0; j < n; j++)
		scanf("%d", &A[j]);

   //printf("%d", mom_select(A, 0, n - 1, i));
   mom_select(A, 0, n - 1, i);

   //printf("%d", quick_select(tmp, 2, 9, 4));
  

   free(A);
	return 0;
}