#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <queue>
#define DUMMY 0
#define INF 1e9 // use this to represent the infinity
using namespace std;

class Graph {
private:
	struct Node {
		int v; int w;
		Node(int v, int w) : v(v), w(w) { }
		bool operator < (const Node& node) const { return this->v < node.v; }
	};

	int n;	 //number of nodes
public:
	vector<vector<Node>> adj_list; //adjacency list used for Prim's algorithm
	
public:
	Graph(int n) : n(n) {
		adj_list = vector<vector<Node>>(n + 1, vector<Node>());
	}

	void insert_edge(int u, int v, int w) {
		adj_list[u].push_back(Node(v, w));
		adj_list[v].push_back(Node(u, w));
	}

	void sort_neighbors() {
		for (auto& neighbors : adj_list)
			std::sort(neighbors.begin(), neighbors.end());
	}

	/* Test */
	int test_getn() { return n; }

	void test_iterate() {
		printf("*********Start : Iterate*********\n");
		for (int i = 0; i <= n; i++) {
			printf("i = %02d ||| ", i);
			for (int j = 0; j < adj_list[i].size(); j++)
				printf("j : %02d, v = %02d, w = %02d || ", j, adj_list[i][j].v, adj_list[i][j].w);
			printf("\n");
		}
		printf("*********End : Iterate*********\n");
	}
};

class MinHeap {
private:
	struct Index {
		int cost; int i;
		Index(int cost, int i) { this->cost = cost; this->i = i; }
	};

	vector<int> array;     // array:   heap_index -> node
	vector<Index> indices; // indices: node -> (cost, heap index)

	int PARENT(int i) { return i / 2; }
	int LEFT(int i) { return 2 * i; }
	int RIGHT(int i) { return 2 * i + 1; }

	// i: heap_index, array[i] is node, and its cost is key
	int key(int i) { return indices[array[i]].cost; }

	void swap(int i, int j) { // i, j: heap_index
		std::swap(array[i], array[j]);
		indices[array[i]] = Index(key(i), i);
		indices[array[j]] = Index(key(j), j);
	}
public:
	MinHeap(int n) {
		array.push_back(DUMMY);
		for (int i = 0; i <= n; i++)
			indices.push_back(Index(DUMMY, DUMMY));
	}

	// return true if this queue is empty
	bool empty() { return array.size() - 1 == 0; }

	// return true if node is in this queue
	bool has(int node) { return indices[node].i != DUMMY; }

	void insert(int cost, int node) {
		array.push_back(node);
		int i = array.size() - 1; // index of node in the heap array
		indices[node] = Index(cost, i);
		//up-heap
		while (i != 1 && key(i) < key(PARENT(i))) {
			this->swap(i, PARENT(i));
			i = PARENT(i);
		}
	}

	// return node having the smallest cost (or distance)
	int remove() {
		int u = array[1];
		indices[u] = Index(DUMMY, DUMMY);

		array[1] = array[array.size() - 1];
		indices[array[1]] = Index(key(1), 1);

		array.pop_back(); // size - 1

		int i = 1;
		int n = array.size() - 1;

		while (i <= n) { // down-heap
			int smallest = i;
			if (LEFT(i) <= n && key(LEFT(i)) < key(smallest))  smallest = LEFT(i);
			if (RIGHT(i) <= n && key(RIGHT(i)) < key(smallest)) smallest = RIGHT(i);

			if (smallest != i) {
				this->swap(i, smallest);
				i = smallest;
			}
			else break;
		}

		return u;
	}

	void decrease_key(int node, int new_cost) {
		int i = indices[node].i;
		if (key(i) > new_cost) {
			indices[node] = Index(new_cost, i);
			// up-heap
			while (i > 1 && key(i) < key(PARENT(i))) {
				this->swap(i, PARENT(i));
				i = PARENT(i);
			}
		}
	}

	int get_key(int node) { return indices[node].cost; }
	int get_top() { return indices[array[1]].cost; }
};

///* Struct */
//struct NODE {
//	int key;
//	int idx;
//	
//	NODE(int key, int idx) : key(key), idx(idx) {}
//
//	bool operator < (const NODE s) const {
//		return this->key > s.key;
//	}
//};

/* Main */
int main(int argc, char* argv[]) {
	/* Input */
	int n, m;		//n은 정점의 수, m은 간선의 수.
	int idx;		//Prim Sequence에서 출력되어야 하는 index.
	scanf("%d %d", &n, &m);
	scanf("%d", &idx);

	/* Graph*/
	Graph g(n); //그래프 생성.
	for (int i = 0; i < m; i++) { //Edge 삽입.
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		g.insert_edge(u, v, w);
	}
	g.sort_neighbors();	 //정렬.
		
	/* Test */
	//printf("*********Start : Graph Inf*********\n");
	//printf("n : %d\n", g.test_getn());
	//printf("*********End : Graph Inf*********\n");
	//g.test_iterate();
	

	/* Prim */
	long long sum_cost = 0;
	int weight = 0;

	MinHeap q(n);
	q.insert(0, 1);	//cost, node num

	/* Test */
	//q.insert(2, 2);
	//q.insert(4, 3);
	//q.insert(6, 4);
	//q.insert(1, 5);

	for (int i = 1; i < n; i++)
		q.insert(INT_MAX, i + 1);

	while (!q.empty()) {
		sum_cost += q.get_top();
		//printf("*********Start : get_top*********\n");
		//printf("test get_top : %d\n", q.get_top());
		if (--idx == -1) weight = q.get_top();
		//printf("*********End : get_top*********\n");

		/* Remove */
		int u = q.remove();
		
		/* Test */
		//printf("*********Start : u*********\n");
		//printf("u=idx : %d\n", u);
		//printf("*********End : u*********\n");

		/* Loop */
		for (int j = 0; j < g.adj_list[u].size(); j++) {
			/* Test */
			//printf("j : %02d, v = %02d, w = %02d\n", j, g.adj_list[u][j].v, g.adj_list[u][j].w);

			//queue 탐색해서 아래 값과 같은게 있나 확인해야함.
			if (q.has(g.adj_list[u][j].v) && g.adj_list[u][j].w <q.get_key(g.adj_list[u][j].v)) {
				/* Test */
				//printf("First key : %d\n", q.get_key(g.adj_list[u][j].v));

				q.decrease_key(g.adj_list[u][j].v, g.adj_list[u][j].w);

				//printf("Changed key : %d\n", q.get_key(g.adj_list[u][j].v));
			}
		}
	}
	printf("%lld\n", sum_cost);
	printf("%d\n", weight);
	
	return 0;
}