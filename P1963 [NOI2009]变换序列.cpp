#include<iostream>
#include<cstring>
using namespace std;
#define maxn 10010

int n;
bool connect[maxn][maxn];
int ymatch[maxn], xmatch[maxn];
bool vis[maxn];

bool dfs(int x)
{
	for (int y = 0; y < n; ++y)
	{
		if (!vis[y] && connect[x][y])
		{
			vis[y] = true;
			if (ymatch[y] == -1 || dfs(ymatch[y]))
			{
				ymatch[y] = x;
				xmatch[x] = y;
				return true;
			}
		}
	}
	return false;
}

bool check()
{
	fill(ymatch, ymatch + maxn, -1);
	for (int i = n - 1; i >= 0; --i)
	{
		memset(vis, 0, sizeof(vis));
		if (!dfs(i))
			return false;
	}
	return true;
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		int dist;
		cin >> dist;
		if (i - dist >= 0)
			connect[i][i - dist] = true;
		if (i + dist < n)
			connect[i][i + dist] = true;
		dist = n - dist;
		if (i - dist >= 0)
			connect[i][i - dist] = true;
		if (i + dist < n)
			connect[i][i + dist] = true;
	}
	if (check())
	{
		cout << xmatch[0];
		for (int i = 1; i < n; ++i)
			cout << ' ' << xmatch[i];
		cout << endl;
	}
	else
		cout << "No Answer" << endl;
}