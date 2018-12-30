#include<iostream>
#include<cstring>
using namespace std;
#define maxn 250


bool vis[maxn];
int grid[maxn][maxn];
int  ymatch[maxn];
int t, n;

bool dfs(int x)
{
	for (int y = 1; y <= n; ++y)
	{
		if (grid[x][y] && !vis[y])
		{
			vis[y] = true;
			if (!ymatch[y] || dfs(ymatch[y]))
			{
				ymatch[y] = x;
				return true;
			}
		}
	}
	return false;
}

bool check()
{
	memset(ymatch, 0, sizeof(ymatch));
	for (int i = 1; i <= n; ++i)
	{
		memset(vis, 0, sizeof(vis));
		if (!dfs(i))
			return false;
	}
	return true;
}


int main()
{
	cin >> t;
	while (t--)
	{
		cin >> n;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				cin >> grid[i][j];
		if (check())
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
}