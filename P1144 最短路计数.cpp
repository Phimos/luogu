#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
#define maxn 1000010
#define MOD 100003
struct Edge
{
	int to, next;
	Edge(int to, int next) : to(to), next(next) {}
	Edge() {}
} edges[maxn << 2];
int head[maxn];
int ans[maxn];
int degree[maxn];
int edgecnt = 0;
int n, m;

void addEdge(int u, int v)
{
	edges[edgecnt++] = Edge(v, head[u]);
	head[u] = edgecnt - 1;
	edges[edgecnt++] = Edge(u, head[v]);
	head[v] = edgecnt - 1;
}

void bfs()
{
	queue<int> travel;
	memset(ans, 0, sizeof(ans));
	memset(degree, 0, sizeof(degree));
	degree[1] = 1;
	ans[1] = 1;
	travel.push(1);
	while (!travel.empty())
	{
		int u = travel.front();
		travel.pop();
		for (int i = head[u]; i != -1; i = edges[i].next)
		{
			int v = edges[i].to;
			if (degree[v] == 0)
			{
				degree[v] = degree[u] + 1;
				travel.push(v);
			}
			if (degree[v] == degree[u] + 1)
			{
				ans[v] = (ans[v] + ans[u]) % MOD;
			}
		}
	}
}

int main()
{
	cin >> n >> m;
	int a, b;
	fill(head, head + n + 1, -1);
	for (int i = 0; i < m; ++i)
	{
		cin >> a >> b;
		addEdge(a, b);
	}
	bfs();
	for (int i = 1; i <= n; ++i)
		cout << ans[i] << endl;
}