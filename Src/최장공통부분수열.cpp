#pragma warning(disable:4996)
#include <string>
#include <iostream>
using namespace std;

#define MIN2(a, b) (((a) < (b)) ? (a) : (b))
#define MIN3(a, b, c) (((a) < (b)) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
#define MAX2(a, b) (((a) > (b)) ? (a) : (b))
#define MAX3(a, b, c) (((a) > (b)) ? ((a) > (c) ? (a) : (c)) : ((b) > (c) ? (b) : (c)))

int DP[101][101][101] = { 0 };

int main(void) {
	string S1, S2, S3;
	cin >> S1 >> S2 >> S3;
	int L1 = S1.length();
	int L2 = S2.length();
	int L3 = S3.length();

	for (int i = 1; i <= L1; i++)
		for (int j = 1; j <= L2; j++) {
			for (int k = 1; k <= L3; k++) {
				if (S1[i - 1] == S2[j - 1] && S2[j - 1] == S3[k - 1])
					DP[i][j][k] = DP[i - 1][j - 1][k - 1] + 1;
				else
					DP[i][j][k] = MAX3(DP[i - 1][j][k], DP[i][j - 1][k], DP[i][j][k - 1]);
			}
		}

	cout << DP[L1][L2][L3];

	return 0;
}