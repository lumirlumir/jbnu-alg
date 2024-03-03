#pragma warning(disable:4996)
#include <cstdio>

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
	/* Input */
	int n, m; //n: 정점, m: 간선.
	scanf("%d %d", &n, &m);

	/* adj_list */ //first: in-dgree & second: adj_list
	vector<pair<int, vector<int>>> adj_list(n + 1, pair<int, vector<int>>(0, vector<int>()));
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);

		adj_list[u].second.push_back(v);
		adj_list[v].first++;
	}

	/* Test */
	//for (int i = 1; i <= n; i++) {
	//	printf("i=%02d, in-degree=%02d | ", i, adj_list[i].first);
	//	for (int j = 0; j < adj_list[i].second.size(); j++) {
	//		printf("v=%02d | ", adj_list[i].second[j]);
	//	}
	//	printf("\n");
	//}

	/* Kahn */
	/* Init */
	queue<int> q;
	for (int i = 1; i <= n; i++)
		if (adj_list[i].first == 0) q.push(i);
	if (q.empty()) { printf("Yes\n"); return 0; }

	/* Loop */
	for (int i = 1; i <= n; i++) {
		if (q.empty()) { printf("Yes\n"); return 0; }

		int u = q.front();
		q.pop();

		for (int j = 0; j < adj_list[u].second.size(); j++) {
			if (--adj_list[adj_list[u].second[j]].first == 0)
				q.push(adj_list[u].second[j]);
		}
	}

	printf("No\n");

	return 0;
}
