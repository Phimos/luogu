#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
#define maxn 2008
#define maxm 10080
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
	edges[edgecnt] = Edge(v, -w, head[u]);
	head[u] = edgecnt++;
}

bool spfa(int s)
{
	memset(dist, 0x3f, sizeof(dist));
	memset(updateTime, 0, sizeof(updateTime));
	dist[s] = 0;
	queue<int> qnodes;
	qnodes.push(s);
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
	init();
	cin >> n >> m;
	int u, v, w;
	for (int i = 0; i < m; ++i)
	{
		cin >> u >> v >> w;
		addEdge(u, v, w);
	}
	int ans = 0x7fffffff;
	if (spfa(1))
	{
		cout << "Forever love" << endl;
		return 0;
	}
	else
		ans = min(ans, dist[n]);
	if (spfa(n))
	{
		cout << "Forever love" << endl;
		return 0;
	}
	else
		ans = min(ans, dist[1]);
	cout << ans << endl;
	return 0;
}