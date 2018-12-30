// luogu-judger-enable-o2
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
#define maxn 2008
#define maxm 8000
struct Edge
{
	int v, w, next;
	Edge(int v, int w, int next) : v(v), w(w), next(next) {}
	Edge() {}
};

Edge edges[maxm];
int edgecnt;
int head[maxn];
int dist[maxn];
int updateTime[maxn];

int t, n, m;

void init()
{
	fill(head, head + maxn, -1);
	edgecnt = 0;
}

void addEdge(int u, int v, int w)
{
	edges[edgecnt] = Edge(v, w, head[u]);
	head[u] = edgecnt++;
	if (w >= 0)
	{
		edges[edgecnt] = Edge(u, w, head[v]);
		head[v] = edgecnt++;
	}
}

bool spfa()
{
	memset(dist, 0x3f, sizeof(dist));
	memset(updateTime, 0, sizeof(updateTime));
	dist[1] = 0;
	queue<int> qnodes;
	qnodes.push(1);
	while (!qnodes.empty())
	{
		int u = qnodes.front();
		qnodes.pop();
		for (int i = head[u]; i != -1; i = edges[i].next)
		{
			int v = edges[i].v;
			if (dist[v] > dist[u] + edges[i].w)
			{
				dist[v] = dist[u] + edges[i].w;
				qnodes.push(v);
				++updateTime[v];
				if (updateTime[v] >= n)
					return true;
			}
		}
	}
	return false;
}

int main()
{
	cin >> t;
	while (t--)
	{
		init();
		cin >> n >> m;
		int u, v, w;
		for (int i = 0; i < m; ++i)
		{
			cin >> u >> v >> w;
			addEdge(u, v, w);
		}
		if (spfa())
			cout << "YE5" << endl;
		else
			cout << "N0" << endl;
	}
}