#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
	/* Input */
	int n, m;		//n:정점, m:간선
	int s;

	scanf("%d %d", &n, &m);
	scanf("%d", &s);

	/* Edge */
	vector<vector<pair<int, int>>> adj_list(n+1, vector<pair<int,int>>());	//adj_list(weight, vertex)
	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		adj_list[u].push_back(make_pair(w, v));
		adj_list[v].push_back(make_pair(w, u));
	}
	
	/* Test */
	//for (int i = 0; i <= n; i++) {
	//	printf("i=%02d | ", i);
	//	for (int j = 0; j < adj_list[i].size(); j++) {
	//		printf("j:%02d, v=%02d, w=%02d | ", j, adj_list[i][j].first, adj_list[i][j].second);
	//	}
	//	printf("\n");
	//}
	
	/* Minimum cost path */
	int* d = (int*)calloc(n + 1, sizeof(int)); //minimum path
	for (int i = 0; i < n + 1; i++)
		d[i] = INT_MAX;

	///* Test */
	//for (int i = 1; i < n + 1; i++)
	//	printf("d[%d] : %2d\n", i, d[i]);

	/* Dijkstra */
	priority_queue<pair<int, int>> q; //cost, node
	
	d[s] = 0;

	q.push(make_pair(0, s));
	
	/* Loop */
	while (!q.empty()) {
		/* Test */
		/*printf("cost, node : %d, %d\n", -q.top().first, q.top().second);*/

		/* Init */
		int current = q.top().second;
		int current_dis = -q.top().first;
		q.pop();

		if (d[current] < current_dis)
			continue; 

		for (int i = 0; i < adj_list[current].size(); i++) {
			int next = adj_list[current][i].second;
			int next_dis = current_dis + adj_list[current][i].first;
			if (d[next] > next_dis) {
				d[next] = next_dis;
				q.push(make_pair(-next_dis, next));
			}
		}
	}

	/* Output */
	for (int i = 1; i < n + 1; i++) {
		if (d[i] == INT_MAX)
			printf("INF\n");
		else
			printf("%d\n", d[i]);
	}
		
	return 0;
}