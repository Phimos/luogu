#include<iostream>
#include<queue>
#include<vector>
#include<altorithm>
#include<cstring>
using namespace std;
#define maxn 10010
int n, m, s, t;
int degree[maxn], cur[maxn];
bool vis[maxn];
struct Edge
{
	int u, v, capacity, flow;
	Edge(int u, int v, int capacity, int flow):
		u(u), v(v), capacity(capacity), flow(flow) {}
};
vector<Edge> edges;
vector<int> graph[maxn];

void addEdge(int u, int v, int cap)
{
	edges.push_back(Edge(u, v, cap, 0));
	edges.push_back(Edge(v, u, 0, 0));
	int k = edges.size();
	graph[u].push_back(k - 2);
	graph[v].push_back(k - 1);
}

bool bfs()
{
	memset(vis, 0, sizeof(vis));
	degree[s] = 0;
	vis[s] = true;
	queue<int> travel;
	travel.push(s);
	while (!travel.empty())
	{
		int u = travel.front();
		travel.pop();
		for (int i = 0; i < graph[u].size(); ++i)
		{
			Edge& temp = edges[graph[u][i]];
			if (!vis[temp.v] && temp.capacity > temp.flow)
			{
				vis[temp.v] = true;
				degree[temp.v] = degree[u] + 1;
				travel.push(temp.v);
			}
		}
	}
	return vis[t];
}

int dfs(int u, int inflow)
{
	if (u == t || inflow == 0)
		return inflow;
	int flow = 0, f;
	for (int& i = cur[u]; i < graph[u].size(); ++i)
	{
		Edge& temp = edges[graph[u][i]];
		if (degree[temp.v] == degree[u] + 1 && (f = dfs(temp.v, min(inflow, temp.capacity - temp.flow))) > 0)
		{
			inflow -= f;
			flow += f;
			temp.flow += f;
			edges[graph[u][i] ^ 1].flow -= f;
		}
		if (inflow == 0)
			break;
	}
	return flow;
}

int maxflow()
{
	int flow = 0;
	while (bfs())
	{
		memset(cur, 0, sizeof(cur));
		flow += dfs(s, 0x7fffffff);
	}
	return flow;
}

int main()
{
	cin >> n >> m >> s >> t;
	int u, v, cap;
	for (int i = 0; i < m; ++i)
	{
		cin >> u >> v >> cap;
		addEdge(u, v, cap);
	}
	cout << maxflow() << endl;
}