#pragma warning(disable:4996)
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

int comp_merge, swap_merge = 0;
int comp_quick, swap_quick = 0;
int comp_heap, swap_heap = 0;

void merge_merge(int A[], int left, int middle, int right) {
   int i = left;
   int j = middle + 1;
   int t = 0;
   int* temp = (int*)calloc(right - left + 1,sizeof(int));

   while (i <= middle && j <= right) {
       comp_merge++;
       if (A[i] <= A[j])
           temp[t++] = A[i++], swap_merge++;
       else
           temp[t++] = A[j++], swap_merge++;
   }

   while (i <= middle)
       temp[t++] = A[i++], swap_merge++;
   while (j <= right)
       temp[t++] = A[j++], swap_merge++;

   i = left, t = 0;
   while (i <= right)
       A[i++] = temp[t++], swap_merge++;

   free(temp);
}

void merge_sort(int A[], int left, int right) {
   if (left < right) {
       int middle = (left + right) / 2;
       merge_sort(A, left, middle);
       merge_sort(A, middle + 1, right);
       merge_merge(A, left, middle, right);
   }
}

int quick_partition(int A[], int left, int right) {
   int pivot = A[right];
   int i = left - 1;

   for (int j = left; j <= right - 1; j++) {
       comp_quick++;
       if (A[j] <= pivot) {
           i += 1;
           int temp = A[i];
           A[i] = A[j];
           A[j] = temp;
           swap_quick++;
       }
   }
   int temp = A[i + 1];
   A[i + 1] = A[right];
   A[right] = temp;
   swap_quick++;

   return i + 1;
}

void quick_sort(int A[], int left, int right) {
   if (left < right) {
       int p = quick_partition(A, left, right);
       quick_sort(A, left, p - 1);
       quick_sort(A, p + 1, right);
   }
}

void down_heap(int A[], int i, int n) {
   int left = 2 * i + 1;
   int right = 2 * i + 2;
   int largest = i;
   int temp = 0;

   if (left < n) {
       comp_heap++;
       if (A[left] > A[largest])
           largest = left;
   }
   if (right < n) {
       comp_heap++;
       if (A[right] > A[largest])
           largest = right;
   }
   if (largest != i) {
       temp = A[i];
       A[i] = A[largest];
       A[largest] = temp;
       swap_heap++;
       down_heap(A, largest, n);
   }
}

void heap_sort(int A[], int n) {
   for (int i = (n-1) / 2 ; i >= 0; i--)
       down_heap(A, i, n);

   for (int i = n - 1; i >= 1; i--) {
       int temp = A[0];
       A[0] = A[i];
       A[i] = temp;
       swap_heap++;
       down_heap(A, 0, i);
   }
}

void print_sort(int arr[], int n) {
   for (int i = 0; i < n; i++)
       printf("%d ", arr[i]);
   printf("\n");
}

int main(int argc, char* argv[]) {
   int n = 0;
   scanf("%d", &n);

   int* A = (int*)calloc(n, sizeof(int));
   int* B = (int*)calloc(n, sizeof(int));
   int* C = (int*)calloc(n, sizeof(int));
   for (int i = 0; i < n; i++)
       scanf("%d", &A[i]);

   memcpy(B, A, sizeof(int) * n);
   memcpy(C, A, sizeof(int) * n);

   merge_sort(A, 0, n-1);
   print_sort(A, n);//Test

   quick_sort(B, 0, n - 1);
   print_sort(B, n);//Test

   heap_sort(C, n);
   print_sort(C, n);//Test

   printf("comp: %d, swap: %d\n", comp_merge, swap_merge);
   printf("comp: %d, swap: %d\n", comp_quick, swap_quick);
   printf("comp: %d, swap: %d\n", comp_heap, swap_heap);

   free(A), free(B), free(C);
   return 0;
}