#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
#define maxn 1010
//匈牙利算法
bool grid[maxn][maxn];
bool vis[maxn];
int xmatch[maxn], ymatch[maxn];
int n, m, e;

bool dfs(int x)
{
	for (int y = 1; y <= m; ++y)
	{
		if (grid[x][y] && !vis[y])
		{
			vis[y] = true;
			if (!ymatch[y] || dfs(ymatch[y]))
			{
				xmatch[x] = y;
				ymatch[y] = x;
				return true;
			}
		}
	}
	return false;
}

int maxmatch()
{
	int ans = 0;
	for (int i = 1; i <= n; ++i)
	{
		memset(vis, 0, sizeof(vis));
		if (dfs(i))
			++ans;
	}
	return ans;
}


int main()
{
	cin >> n >> m >> e;
	memset(grid, 0, sizeof(grid));
	for (int i = 0; i < e; ++i)
	{
		int x, y;
		cin >> x >> y;
		if (x > 0 && x <= n && y > 0 && y <= m)
			grid[x][y] = true;
	}
	cout << maxmatch() << endl;
}