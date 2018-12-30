#include<iostream>
#include<cstring>
#include<queue>
#include<stack>
using namespace std;
#define maxn 10010
#define maxm 100010
//tarjan缩点+topo+dp
struct Edge
{
	int u, v, next;
	Edge(int u, int v, int next) : u(u), v(v), next(next) {}
	Edge() {}
};

Edge edges[maxm];
int edgecnt, ind, colorcnt;
int w[maxn], head[maxn];
int low[maxn], dfn[maxn];
int color[maxn], ww[maxn];
int maxsum[maxn];
int indeg[maxn];
bool vis[maxn];
stack<int> snodes;
int n, m;

void init()
{
	edgecnt = 0;
	ind = 0;
	colorcnt = 0;
	fill(head, head + maxn, -1);
	memset(ww, 0, sizeof(ww));
	memset(vis, 0, sizeof(vis));
}

void addEdge(int u, int v)
{
	edges[edgecnt] = Edge(u, v, head[u]);
	head[u] = edgecnt++;
}

void tarjan(int u)
{
	dfn[u] = low[u] = ++ind;
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
			vis[v] = 0;
			color[v] = colorcnt;
			ww[colorcnt] += w[v];
		} while (u != v);
	}
}

void maintain()
{
	edgecnt = 0;
	fill(head, head + maxn, -1);
	memset(indeg, 0, sizeof(indeg));
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

int topo()
{
	queue<int> qnodes;
	for (int i = 1; i <= colorcnt; ++i)
	{
		maxsum[i] = ww[i];
		if (indeg[i] == 0)
			qnodes.push(i);
	}
	while (!qnodes.empty())
	{
		int u = qnodes.front();
		qnodes.pop();
		for (int i = head[u]; i != -1; i = edges[i].next)
		{
			int v = edges[i].v;
			--indeg[v];
			maxsum[v] = max(maxsum[v], maxsum[u] + ww[v]);
			if (indeg[v] == 0)
				qnodes.push(v);
		}
	}
	int ans = 0;
	for (int i = 1; i <= colorcnt; ++i)
		ans = max(ans, maxsum[i]);
	return ans;
}

int main()
{
	init();
	int u, v;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		cin >> w[i];
	for (int i = 0; i < m; ++i)
	{
		cin >> u >> v;
		addEdge(u, v);
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i])
			tarjan(i);
	maintain();
	cout << topo() << endl;
}