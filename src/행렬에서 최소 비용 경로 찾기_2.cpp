#include <iostream>
#include <algorithm>
#include <climits>
#define INF (INT_MAX / 2)
using namespace std;

int M[2001][2001] = {}; // Matrix
int T[2001][2001] = {}; // Table
int n;

int dp(int col, int row) {
	if (col == 1 && row == n - 1)
		return M[col][row];

	else if (col == 0 || row == n)
		return M[col][row];

	else if (T[col][row] != 0)
		return T[col][row];

	else
		return T[col][row] = M[col][row] + min({ dp(col - 1, row + 1), dp(col - 1, row), dp(col, row + 1) });
}

int main(void) {
	/* Faster */
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	/* Input & Init */
	// n
	cin >> n;
	// M[][]
	for (int col = 1; col <= n; col++)
		for (int row = 0; row < n; row++)
			cin >> M[col][row];
	for (int i = 0; i <= n; i++) {
		M[0][i] = INF;
		M[i][n] = INF;
	}
		
	/* debug */
	//for (int i = 0; i <= n; i++) {
	//	for (int j = 0; j <= n; j++)
	//		cout << M[i][j] << ' ';
	//	cout << '\n';
	//}

	/* Output */
	cout << dp(n, 0) << '\n';

	/* Return */
	return 0;

}

/*
3
1 3 1
9 10 5
2 1 4

3
10 10 1
10 1 10
1 10 10
*/