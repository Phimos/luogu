#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
#define maxn 1010
struct Node
{
	int x, y;
	Node(int x, int y) : x(x), y(y) {}
	Node() {}
};

Node grant[maxn];
Node pandog[maxn];
bool connect[maxn][maxn];
int match[maxn];
bool vis[maxn];
int n, m;

double dist(Node& a, Node& b)
{
	return sqrt((double)((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

bool dfs(int x)
{
	for (int y = 1; y < n; ++y)
	{
		if (!vis[y] && connect[x][y])
		{
			vis[y] = true;
			if (!match[y] || dfs(match[y]))
			{
				match[y] = x;
				return true;
			}
		}
	}
	return false;
}

int maxmatch()
{
	int ans = 0;
	memset(match, 0, sizeof(match));
	for (int x = 1; x <= m; ++x)
	{
		memset(vis, 0, sizeof(vis));
		if (dfs(x))
			++ans;
	}
	return ans;
}

int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		cin >> grant[i].x >> grant[i].y;
	for (int i = 1; i <= m; ++i)
		cin >> pandog[i].x >> pandog[i].y;
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j < n; ++j)
			if (dist(pandog[i], grant[j]) + dist(pandog[i], grant[j + 1]) <= 2.0 * dist(grant[j], grant[j + 1]))
				connect[i][j] = true;
	cout << maxmatch() + n << endl;
	for (int i = 1; i <= n; ++i)
	{
		if (i == 1)
			cout << grant[i].x << ' ' << grant[i].y;
		else
			cout << ' ' << grant[i].x << ' ' << grant[i].y;
		if (match[i])
			cout << ' ' << pandog[match[i]].x << ' ' << pandog[match[i]].y;
	}
	cout << endl;
}