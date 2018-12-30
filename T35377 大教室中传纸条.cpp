#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 208
int n, m;
int room[maxn][maxn];
int dp[maxn][maxn];
int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			cin >> room[i][j];
	for (int k = 3; k <= m + n; ++k)
	{
		for (int i = n; i > 0; --i)
		{
			if (k - i <= 0)
				continue;
			for (int j = i - 1; j > 0; --j)
			{
				dp[i][j] = room[i][k - i] + room[j][k - j] + max(max(dp[i - 1][j - 1], dp[i][j]), max(dp[i][j - 1], dp[i - 1][j]));
			}
		}
	}
	cout << dp[n][n - 1] << endl;
}