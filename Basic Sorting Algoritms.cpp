#pragma warning(disable:4996)
#include <cstdio>
#include <cstdlib>
#include <iostream>

/* ArgMax Test
unsigned int argmax(unsigned int A[], unsigned int i) {
   unsigned int max_j = 1;
   for (int j = 2; j <= i; j++) {
       if (A[j] > A[max_j])
           max_j = j;
   }
   return max_j;
}
*/
void selection_sort(unsigned int arr[], unsigned int n) {
   unsigned int* A = (unsigned int*)calloc(n, sizeof(unsigned int));
   unsigned int k = 0;
   unsigned int tmp = 0;
   unsigned int count_comp = 0;
   unsigned int count_swap = 0;
   
   for (int i = 0; i < n; i++)
       A[i] = arr[i];  //배열복사
     
   for (int i = n-1; i >= 1; i--) {
       k = 0;
       for (int j = 1; j <= i; j++) {
           count_comp++;
           if (A[k] < A[j]) {
               k = j;
           }
       }
       if (k != i) {
           count_swap++;
           tmp = A[k];
           A[k] = A[i];
           A[i] = tmp;
       }
   }
   printf("comp: %u, swap: %u\n", count_comp, count_swap);

   // Test용도
   /*
   printf("[selection_sort] : ");
   for (int i = 0; i < n; i++)
       printf("%u ", A[i]);
   printf("\n");
   */

   free(A);
}

void bubble_sort(unsigned int arr[], unsigned int n) {
   unsigned int* A = (unsigned int*)calloc(n, sizeof(unsigned int));
   unsigned int tmp = 0;
   unsigned int count_comp = 0;
   unsigned int count_swap = 0;

   for (int i = 0; i < n; i++) {
       A[i] = arr[i];
   } //배열복사

   for (int i = n - 1; i >= 1; i--) {
       for (int j = 0; j <= i - 1; j++) {
           count_comp++;
           if (A[j] > A[j + 1]) {
               tmp = A[j];
               A[j] = A[j + 1];
               A[j + 1] = tmp;
               count_swap++;
           }
       }
   }

   printf("comp: %u, swap: %u\n", count_comp, count_swap);

   /*
   printf("[bubble_sort] : ");
   for (int i = 0; i < n; i++)
       printf("%u ", A[i]);
   printf("\n");
   */

   free(A);
}

void insertion_sort(unsigned int arr[], unsigned int n) {
   unsigned int* A = (unsigned int*)calloc(n, sizeof(unsigned int));
   int loc = 0;
   int item = 0;
   unsigned int count_comp = 0;
   unsigned int count_swap = 0;

   for (int i = 0; i < n; i++) {
       A[i] = arr[i];
   }
   // 2 1 3 4 5 [5개] &  2 3 1 4 5
   for (int i = 1; i <= n - 1; i++) {
       loc = i - 1;
       item = A[i];
       while (loc >= 0) {
           count_comp++;
           if (A[loc] > item) {
               A[loc + 1] = A[loc];
               loc -= 1;
               count_swap++;
           }
           else
               break;
       }
       A[loc + 1] = item;
       count_swap++;
   }

   printf("comp: %u, swap: %u\n", count_comp, count_swap);

   /*
   printf("[insertion_sort] : ");
   for (int i = 0; i < n; i++)
       printf("%u ", A[i]);
   printf("\n");
   */

   free(A);
}

int main(int argc, char *argv[]) {

   unsigned int n=0;
   scanf("%u", &n);

  unsigned int* arr = (unsigned int*)calloc(n, sizeof(unsigned int));
   for (int i = 0; i < n; i++)
       scanf("%u", &arr[i]);

   selection_sort(arr, n);
   bubble_sort(arr, n);
   insertion_sort(arr, n);

   free(arr);
   return 0;
}