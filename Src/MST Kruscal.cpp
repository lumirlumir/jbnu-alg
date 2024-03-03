#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Struct */
typedef struct {
	int p;			//Parent Node.
	int rank;	//Rank.
}NODE;

typedef struct {
	int u;				//1st Vertex.
	int v;				//2nd Vertex.
	int weight;		//가중치.
}VERTEX;

/* Function */
/* Disjoint Set*/
void DS_make(NODE* node, int u) {
	node[u].p = u;
	node[u].rank = 0;
}

int DS_find(NODE* node, int u) {
	if (node[u].p != u)
		node[u].p = DS_find(node, node[u].p);
	return node[u].p;
}

bool DS_merge(NODE* node, int u, int v) {
	int ur = DS_find(node, u);
	int vr = DS_find(node, v);
	if (ur == vr)
		return false;
	if (node[ur].rank > node[vr].rank)
		node[vr].p = ur;
	else {
		node[ur].p = vr;
		if (node[ur].rank == node[vr].rank)
			node[vr].rank += 1;
	}
	return true;
}

/* Sorting */
void merge_merge(VERTEX vertex[], int left, int middle, int right) {
   int i = left;
   int j = middle + 1;
   int t = 0;
   VERTEX* temp = (VERTEX*)calloc(right - left + 1,sizeof(VERTEX));

   while (i <= middle && j <= right) {
       if (vertex[i].weight <= vertex[j].weight)
           temp[t++] = vertex[i++];
       else
           temp[t++] = vertex[j++];
   }

   while (i <= middle)
       temp[t++] = vertex[i++];
   while (j <= right)
       temp[t++] = vertex[j++];

   i = left, t = 0;
   while (i <= right)
       vertex[i++] = temp[t++];

   free(temp);
}

void merge_sort(VERTEX vertex[], int left, int right) {
   if (left < right) {
       int middle = (left + right) / 2;
       merge_sort(vertex, left, middle);
       merge_sort(vertex, middle + 1, right);
       merge_merge(vertex, left, middle, right);
   }
}

/* Main */
int main(int argc, char* argv[]) {
	/* INPUT : n, m, idx */
	int n, m;		//n: 정점의 수, m: 간선의 수.
	int idx = 0;		//Kruscal Sequence에서 출력되어야 하는 인덱스.
	
	scanf("%d %d", &n, &m);
	scanf("%d", &idx);

	/* MAKE : VERTEX */
	VERTEX* vertex = (VERTEX*)calloc(m, sizeof(VERTEX));	//간선의 개수만큼 간선 구조체 생성. (idx 0부터 시작.)
	for (int i = 0; i < m; i++)
		scanf("%d %d %d", &vertex[i].u, &vertex[i].v, &vertex[i].weight);

	/* Test */
	//printf("*********[간선 정보]*********\n");
	//for (int i = 0; i < m; i++)
	//	printf("vertex %d : u = %d | v = %d | weight = %d\n", i, vertex[i].u, vertex[i].v, vertex[i].weight);
	
	/* MAKE : NODE*/
	NODE* node = (NODE*)calloc(n+1, sizeof(NODE));	//노드 개수만큼 노드 구제초 생성. (idx 1부터 시작.)
	for (int i = 1; i <= n; i++)
		DS_make(node, i);

	/* Test */
	//printf("*********[정점 정보]*********\n");
	//for (int i = 1; i <= n; i++)
	//	printf("node %d : p = %d | rank = %d\n", i, node[i].p, node[i].rank);

	/* Vertex Sorting */
	merge_sort(vertex, 0, m-1);

	/* Test */
	//printf("*********[간선 정보]*********\n");
	//for (int i = 0; i < m; i++)
	//	printf("vertex %d : u = %d | v = %d | weight = %d\n", i, vertex[i].u, vertex[i].v, vertex[i].weight);

	/* Kruscal */
	long long cost = 0;
	int weight = 0;
	for (int i = 0; i < m; i++) {
		if (DS_find(node, vertex[i].u) != DS_find(node, vertex[i].v)) {
			DS_merge(node, vertex[i].u, vertex[i].v);
			cost += vertex[i].weight;
			if (--idx == 0)
				weight = vertex[i].weight;

			/* Test */
			//printf("*********[간선 정보]*********\n");
			//printf("vertex %d : u = %d | v = %d | weight = %d\n", i, vertex[i].u, vertex[i].v, vertex[i].weight);
			//printf("*********[정점 정보]*********\n");
			//for (int i = 1; i <= n; i++)
			//	printf("node %d : p = %d | rank = %d\n", i, node[i].p, node[i].rank);
		}
	}

	/* Output */
	printf("%lld\n%d\n", cost, weight);

	return 0;
}

