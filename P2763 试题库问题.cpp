#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
#define maxn 1200
struct Edge
{
	int to, capacity, flow, next;
	Edge(int to, int capacity, int flow, int next) :
		to(to), capacity(capacity), flow(flow), next(next) {}
	Edge() {}
};

vector<Edge> edges;
int head[maxn];
int cur[maxn], degree[maxn];
bool vis[maxn];
int n, k, s, t;
int paper[20];
vector<int> ans[20];


void addEdge(int u, int v, int cap)
{
	edges.push_back(Edge(v, cap, 0, head[u]));
	head[u] = edges.size() - 1;
	edges.push_back(Edge(u, 0, 0, head[v]));
	head[v] = edges.size() - 1;
}

bool bfs()
{
	memset(vis, 0, sizeof(vis));
	vis[s] = true;
	degree[s] = false;
	queue<int> travel;
	travel.push(s);
	while (!travel.empty())
	{
		int u = travel.front();
		travel.pop();
		for (int i = head[u]; i != -1; i = edges[i].next)
		{
			Edge& temp = edges[i];
			if (!vis[temp.to] && temp.capacity > temp.flow)
			{
				vis[temp.to] = true;
				degree[temp.to] = degree[u] + 1;
				travel.push(temp.to);
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
	for (int& i = cur[u]; i != -1; i = edges[i].next)
	{
		Edge& temp = edges[i];
		if (degree[temp.to] == degree[u] + 1 && (f = dfs(temp.to, min(inflow, temp.capacity - temp.flow))) > 0)
		{
			inflow -= f;
			flow += f;
			temp.flow += f;
			edges[i ^ 1].flow -= f;
			if (k < u && u < t && temp.to > 0 && temp.to <= k)
			{
				ans[temp.to].push_back(u);
			}
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
		for (int i = 0; i < maxn; ++i)
			cur[i] = head[i];
		flow += dfs(s, 0x7fffffff);
	}
	return flow;
}

int main()
{
	cin >> k >> n;
	s = 0, t = k + n + 1;
	int sum = 0;
	fill(head, head + maxn, -1);
	for (int i = 1; i <= k; ++i)
	{
		cin >> paper[i];
		sum += paper[i];
		addEdge(i, t, paper[i]);
	}
	for (int i = k + 1; i < t; ++i)
	{
		addEdge(s, i, 1);
		int p, w;
		cin >> p;
		for (int j = 0; j < p; ++j)
		{
			cin >> w;
			addEdge(i, w, 0x7fffffff);
		}
	}
	if (maxflow() == sum)
	{
		for (int i = 1; i <= k; ++i)
		{
			cout << i << ':';
			for (int j = 0; j < ans[i].size(); ++j)
				cout << ' ' << ans[i][j] - k;
			cout << endl;
		}
	}
	else
		cout << "No Solution!" << endl;
}