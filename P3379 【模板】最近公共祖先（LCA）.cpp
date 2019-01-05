#include<cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
#include<cstring>
using namespace std;
#define maxn 500010

int ast[maxn][21];
int head[maxn], depth[maxn];
int lg[maxn];
int n, m, s;
int cnt;

struct Edge
{
	int to, next;
	Edge(int to, int next) : to(to), next(next) {}
	Edge() {}
} edges[maxn << 1];


void addEdge(int x, int y)
{
	edges[cnt].to = y;
	edges[cnt].next = head[x];
	head[x] = cnt++;
	edges[cnt].to = x;
	edges[cnt].next = head[y];
	head[y] = cnt++;
}

void dfs(int u, int fa)
{
	depth[u] = depth[fa] + 1;
	ast[u][0] = fa;
	for (int i = 0; ast[u][i]; ++i)
		ast[u][i + 1] = ast[ast[u][i]][i];
	for (int i = head[u]; ~i; i = edges[i].next)
		if (edges[i].to != fa)
			dfs(edges[i].to, u);
	return;
}

int query(int x, int y)
{
	if (depth[x] < depth[y])
		swap(x, y);
	while (depth[x] > depth[y])
		x = ast[x][lg[depth[x] - depth[y]] - 1];	//优化
	if (x == y)
		return x;
	for (int i = lg[depth[x]] - 1; i >= 0; --i)
		if (ast[x][i] != ast[y][i])
		{
			x = ast[x][i];
			y = ast[y][i];
		}
	return ast[x][0];
}

int main()
{
	scanf("%d%d%d", &n, &m, &s);
	int x, y;
	fill(head, head + maxn, -1);
	for (int i = 1; i < n; ++i)
	{
		scanf("%d%d", &x, &y);
		addEdge(x, y);
	}
	dfs(s, 0);
	for (int i = 1; i <= n; ++i)
		lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
	for (int i = 0; i < m; ++i)
	{
		scanf("%d%d", &x, &y);
		printf("%d\n", query(x, y));
	}
}