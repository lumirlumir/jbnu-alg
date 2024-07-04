#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

void DS_make_set(int p[], int u) {
	p[u] = u;
}

int DS_find_set(int p[], int u) { //Root Node를 찾음.
	if (u == p[u])
		return u;
	else
		return p[u] = DS_find_set(p, p[u]);
}

int DS_Union(int p[], int size[], int u, int v) {
	if (DS_find_set(p, v) == DS_find_set(p, u)) //사이클 판독
		return true;
	else {
		size[DS_find_set(p, u)] += size[DS_find_set(p, v)];

		p[DS_find_set(p, v)] = DS_find_set(p, u); 

		return false;
	}
}

void print_test(int p[], int size[], int n, int cycle) { //Test
	for (int i = 1; i <= n; i++)
		printf("%d ", p[i]);
	printf("\n");
	for (int i = 1; i <= n; i++)
		printf("%d ", size[i]);
	printf("\n");
	printf("cycle? : %d\n", cycle);
}

int max(int n[], int size) {
	int max = n[0];

	for (int i = 1; i < size; i++)
		if (n[i] > max) max = n[i];

	return max;
}

int main(int argc, char* argv[]) {
	int n, m = 0; 	//n : 정점의 수, m : 간선의 수
	int cycle = false;
	int rootnum = 0; // 루트의 개수

	scanf("%d %d", &n, &m);
	
	int* p = (int*)calloc(n+1,sizeof(int)); // 배열 NULL로 초기화.
	for (int i = 1; i <= n; i++)
		DS_make_set(p, i);

	int* size = (int*)calloc(n+1, sizeof(int)); // 배열 NULL로 초기화.
	for (int i = 1; i <= n; i++)
		size[i] = 1;

	for (int i = 0; i < m; i++) {
		int buf1, buf2 = 0;
		scanf("%d %d", &buf1, &buf2);
		if(DS_Union(p, size, buf1, buf2)==true)
			cycle = true;

		//print_test(p, size, n, cycle); // TEST
	}

	for (int i = 1; i <= n; i++) //Root 찾기
		if (i == p[i])
			rootnum++;

	//답 제출
	printf("%s\n", cycle == true ? "Found" : "Not found");
	printf("%d\n", rootnum);
	printf("%d", max(size, n + 1));

	free(p);
	free(size);

	return 0;
}