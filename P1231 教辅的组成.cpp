#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#include<vector>
using namespace std;

int N1, N2, N3, N;
int M1, M2;

struct Edge
{
	int u, v, capacity, flow;
	Edge(int u, int v, int capacity, int flow):
		u(u), v(v), capacity(capacity), flow(flow) {}
};

vector<Edge> edges;
vector<int>  graph[maxn];
int degree[maxn];
int cur[maxn];
bool vis[maxn];

void addEdge(int u, int v, int cap)
{
	edges.push_back(Edge(u, v, cap, 0));
	edges.push_back(Edge(v, u, 0, 0));
	int m = edges.size();
	graph[u].push_back(m - 2);
	graph[v].push_back(m - 1);
}

bool bfs()
{
	memset(vis, 0, sizeof(vis));
	queue<int> travel;
	vis[0] = true;
	degree[0] = 0;
	travel.push(0);
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
	return vis[1];
}

int dfs(int u, int inflow)
{
	if (u == 1 || inflow == 0)
		return inflow;
	int flow = 0, f;
	for (int& i = cur[u]; i <= graph[u].size(); ++i)
	{
		Edge& temp = edges[graph[u][i]];
		if (degree[temp.v] == degree[u] + 1 && (f = dfs(temp.v, min(inflow, temp.capacity - temp.flow))) > 0)
		{
			flow += f;
			inflow -= f;
			temp.flow += f;
			edges[graph[u][i] ^ 1] -= f;
		}
		if (!inflow)
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
		f += dfs(0, 0x7fffffff);
	}
	return flow;
}

int main()
{
	cin >> N1 >> N2 >> N3;
	N = N1 + N2 + N3;
	cin >> M1;
	for (int i = 0; i < M1; ++i)
	{
		int x, y;
		cin >> x >> y;
		addEdge((N1 << 1 | 1) + y, x << 1, 1, 0);
	}
	cin >> M2;
	for (int i = 0; i < M2; ++i)
	{
		int x, y;
		cin >> x >> y;
		addEdge(x << 1 | 1, (N1 << 1 | 1) + N2 + y, 1, 0);
	}
	for (int i = 1; i <= N1; ++i)
		addEdge(x << 1, x << 1 | 1, 1, 0);
	for (int i = 1; i <= N2; ++i)
		addEdge(0, (N1 << 1 | 1) + i, 1, 0);
	for (int i = 1; i <= N3; ++i)
		addEdge((N1 << 1 | 1) + N2 + i, 1, 1, 0);
	cout << maxflow() << endl;
}