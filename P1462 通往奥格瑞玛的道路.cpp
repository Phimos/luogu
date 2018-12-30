#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
#define maxn 10010
#define maxm 50010

struct Node
{
	int v, blood;
	Node(int v, int blood) : v(v), blood(blood) {}
	Node() {}
	bool operator<(const Node& other)const
	{
		return other.blood < blood;
	}
};

struct Edge
{
	int u, v, lost, next;
	Edge(int u, int v, int lost, int next) : u(u), v(v), lost(lost), next(next) {}
	Edge() {}
} edges[maxm << 1];
int head[maxn];
bool vis[maxn];
int cost[maxn];
int sortedcost[maxn];
int dist[maxn];
int cnt = -1, n, m, b;

void addEdge(int u, int v, int lost)
{
	edges[++cnt] = Edge(u, v, lost, head[u]);
	head[u] = cnt;
	edges[++cnt] = Edge(v, u, lost, head[v]);
	head[v] = cnt;
}

bool dijkstra(int c)
{
	if (c < cost[1] || c < cost[n])
		return false;
	fill(dist, dist + maxn, 0x3fffffff);
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; ++i)
		if (c < cost[i])
			vis[i] = true;
	dist[1] = 0;
	priority_queue<Node> pqueue;
	pqueue.push(Node(1, 0));
	while (!pqueue.empty())
	{
		Node temp = pqueue.top();
		pqueue.pop();
		if (!vis[temp.v])
		{
			vis[temp.v] = true;
			for (int i = head[temp.v]; i != -1; i = edges[i].next)
			{
				if (dist[edges[i].v] > dist[edges[i].u] + edges[i].lost)
				{
					dist[edges[i].v] = dist[edges[i].u] + edges[i].lost;
					pqueue.push(Node(edges[i].v, dist[edges[i].v]));
				}
			}
		}
	}
	return dist[n] <= b;
}


int main()
{
	cin >> n >> m >> b;
	fill(head, head + n + 1, -1);
	for (int i = 1; i <= n; ++i)
		cin >> cost[i];
	int x, y, c;
	for (int i = 0; i < m; ++i)
	{
		cin >> x >> y >> c;
		addEdge(x, y, c);
	}
	memcpy(sortedcost, cost, sizeof(cost));
	sort(sortedcost + 1, sortedcost + n + 1);
	if (!dijkstra(sortedcost[n]))
		cout << "AFK" << endl;
	else
	{
		int l = 1, r = n, mincost;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			if (dijkstra(sortedcost[mid]))
			{
				mincost = sortedcost[mid];
				r = mid - 1;
			}
			else
				l = mid + 1;
		}
		cout << mincost << endl;
	}
}