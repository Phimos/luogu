#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
#define maxn 1010
#define maxm 100010

struct Edge
{
	int u, v, w;
	Edge(int u, int v, int w) : u(u), v(v), w(w) {}
	Edge() {}
	bool operator<(const Edge& other)const
	{
		return other.w < w;
	}
};

priority_queue<Edge> edges;
int fa[maxn];
int n, m;

int getroot(int k)
{
	return k == fa[k] ? k : fa[k] = getroot(fa[k]);
}

int kruskal()
{
	for (int i = 1; i <= n; ++i)
		fa[i] = i;
	int cnt = 0;
	while (!edges.empty())
	{
		Edge temp = edges.top();
		edges.pop();
		if (getroot(temp.u) != getroot(temp.v))
		{
			fa[getroot(temp.u)] = getroot(temp.v);
			++cnt;
			if (cnt == n - 1)
				return temp.w;
		}
	}
	return -1;
}

int main()
{
	cin >> n >> m;
	int u, v, w;
	for (int i = 0; i < m; ++i)
	{
		cin >> u >> v >> w;
		edges.push(Edge(u, v, w));
	}
	cout << kruskal() << endl;
}