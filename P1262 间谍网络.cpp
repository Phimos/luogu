#include<iostream>
#include<cstring>
#include<stack>
#include<algorithm>
using namespace std;
#define maxn 3008
#define maxm 8008

int dfn[maxn], low[maxn];
int idx, colorcnt, edgecnt;
int head[maxn], money[maxn];
int w[maxn];
int color[maxn];
bool vis[maxn];
int indeg[maxn];

struct Edge
{
	int u, v, next;
	Edge(int u, int v, int next) : u(u), v(v), next(next) {}
	Edge() {}
};

Edge edges[maxm];
int n, p, m;
stack<int> snodes;
void init()
{
	edgecnt = 0;
	fill(head, head + maxn, -1);
	fill(money, money + maxn, 0x3f3f3f3f);
}
void addEdge(int u, int v)
{
	edges[edgecnt] = Edge(u, v, head[u]);
	head[u] = edgecnt++;
}

void tarjan(int u)
{
	dfn[u] = low[u] = ++idx;
	snodes.push(u);
	vis[u] = true;
	for (int i = head[u]; i != -1; i = edges[i].next)
	{
		int v = edges[i].v;
		if (!dfn[v])
		{
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if (vis[v])
		{
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (dfn[u] == low[u])
	{
		int v;
		++colorcnt;
		do {
			v = snodes.top();
			snodes.pop();
			vis[v] = false;
			color[v] = colorcnt;
		} while (u != v);
	}
}

void maintain()
{
	edgecnt = 0;
	fill(w, w + maxn, 0x3f3f3f3f);
	for (int i = 1; i <= n; ++i)
	{
		w[color[i]] = min(w[color[i]], money[i]);
	}
	for (int i = 0; i < m; ++i)
	{
		int u = edges[i].u, v = edges[i].v;
		if (color[u] != color[v])
		{
			addEdge(color[u], color[v]);
			++indeg[color[v]];
		}
	}
}

bool check(int& ans)
{
	ans = 0;
	for (int i = 1; i <= colorcnt; ++i)
	{
		if (indeg[i] == 0)
			if (w[i] == 0x3f3f3f3f)
				return false;
			else
				ans += w[i];
	}
	return true;
}

int main()
{
	init();
	cin >> n >> p;
	int u, v;
	for (int i = 0; i < p; ++i)
	{
		cin >> u;
		cin >> money[u];
	}
	cin >> m;
	for (int i = 0; i < m; ++i)
	{
		cin >> u >> v;
		addEdge(u, v);
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i])
			tarjan(i);
	maintain();
	int ans = 0;
	if (check(ans))
		cout << "YES" << endl << ans << endl;
	else
	{
		int minpos = 0x7fffffff;
		for (int i = 1; i <= colorcnt; ++i)
			if (indeg[i] == 0 && w[i] == 0x3f3f3f3f)
				for (int j = 1; j <= n; ++j)
					if (color[j] == i)
						minpos = min(minpos, j);
		cout << "NO" << endl << minpos << endl;
	}
}