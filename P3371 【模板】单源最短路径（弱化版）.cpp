#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;
#define maxn 10010

struct Edge
{
	int u, v, w;
	Edge(int u, int v, int w) :
		u(u), v(v), w(w) {}
	Edge() {}
};

vector<Edge> edges;
vector<int> graph[maxn];
int dist[maxn];
int n, m, s;


struct Heap
{
	int id, w;
	Heap(int id, int w) : id(id), w(w) {}
	bool operator<(const Heap& other)const
	{
		return w > other.w;
	}
};

void Dijkstra(int s)
{
	priority_queue<Heap> Q;
	fill(dist, dist + n + 1, 0x7fffffff);
	dist[s] = 0;
	Q.push(Heap(s, dist[s]));
	while (!Q.empty())
	{
		Heap temp = Q.top();
		Q.pop();
		if (dist[temp.id] != temp.w)	//过时了
			continue;
		int u = temp.id;
		for (int i = 0; i < graph[u].size(); ++i)
		{
			int v = edges[graph[u][i]].v;
			if (dist[v] > dist[u] + edges[graph[u][i]].w)
			{
				dist[v] = dist[u] + edges[graph[u][i]].w;
				Q.push(Heap(v, dist[v]));
			}
		}
	}
	for (int i = 1; i < n; ++i)
		cout << dist[i] << ' ';
	cout << dist[n] << endl;
	return;
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m >> s;
	for (int i = 0; i < m; ++i)
	{
		int u, v, w;
		cin >> u >> v >> w;
		graph[u].push_back(edges.size());
		edges.push_back(Edge(u, v, w));
	}
	Dijkstra(s);
}