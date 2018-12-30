#include<iostream>
#include<algorithm>
using namespace std;

int dir[8][2] = { { 1, 2 }, { 1, -2 }, { -1, 2 }, { -1, -2 }, { 2, 1 }, { 2, -1 }, { -2, 1 }, { -2, -1 } };
int n, m, x, y;
long long dp[22][22];
bool mark[22][22];

void setHorse()
{
	mark[x][y] = true;
	for (int i = 0; i < 8; ++i)
	{
		int xx = x + dir[i][0];
		int yy = y + dir[i][1];
		if (xx >= 0 && xx <= n && yy >= 0 && yy <= m)
			mark[xx][yy] = true;
	}
	return;
}
int main()
{
	cin >> n >> m >> x >> y;
	setHorse();
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= m; ++j)
		{
			if (!mark[i][j])
			{
				if (i == 0 && j == 0)
					dp[i][j] = 1;
				else
				{
					if (i == 0)
						dp[i][j] = dp[i][j - 1];
					else if (j == 0)
						dp[i][j] = dp[i - 1][j];
					else
						dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
				}
			}
		}
	cout << dp[n][m] << endl;
}