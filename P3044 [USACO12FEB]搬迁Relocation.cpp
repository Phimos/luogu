// luogu-judger-enable-o2
#include<iostream>
#include<algorithm>
#include<map>
#include<queue>
using namespace std;
#define maxm 100010
#define maxn 10010

int n, m, k;
struct Edge
{
	int to, next, dist;
	Edge(int to, int dist, int next) :
		to(to), dist(dist), next(next) {}
	Edge() {}
} edges[maxm];
int head[maxn];
int town[10];
int mindist[6][maxn];
int edgecnt = 0;

struct Node
{
	int to, dist;
	Node(int to, int dist) :
		to(to), dist(dist) {}
	Node() {}
	bool operator<(const Node& other)const
	{
		return other.dist < dist;
	}
};

void addEdge(int u, int v, int w)
{
	edges[edgecnt] = Edge(v, w, head[u]);
	head[u] = edgecnt++;
	edges[edgecnt] = Edge(u, w, head[v]);
	head[v] = edgecnt++;
}

void dijkstra(int k, int s)
{
	priority_queue<Node> travel;
	fill(mindist[k], mindist[k] + maxn, 0x3f3f3f3f);
	mindist[k][town[k]] = 0;
	travel.push(Node(s, 0));
	while (!travel.empty())
	{
		Node temp = travel.top();
		travel.pop();
		int u = temp.to;
		for (int i = head[u]; i != -1; i = edges[i].next)
		{
			int v = edges[i].to;
			if (mindist[k][v] > edges[i].dist + mindist[k][u])
			{
				mindist[k][v] = edges[i].dist + mindist[k][u];
				travel.push(Node(v, mindist[k][v]));
			}
		}
	}
	return;
}

int solve(int t)
{
	int temp[5];
	map<int, int> order;
	for (int i = 0; i < k; ++i)
	{
		order[town[i]] = i;
		temp[i] = town[i];
		if (temp[i] == t)
			return 0x7fffffff;
	}
	sort(temp, temp + k);
	int minans = 0x7fffffff;
	do {
		int ans = mindist[order[temp[0]]][t] + mindist[order[temp[k - 1]]][t], flag = 0;
		if (ans >= 0x3f3f3f3f)
			continue;
		for (int i = 1; i < k; ++i)
		{
			if (mindist[order[temp[i]]][temp[i - 1]] < 0x3f3f3f3f)
				ans += mindist[order[temp[i]]][temp[i - 1]];
			else
			{
				flag = 1;
				break;
			}
		}
		if (flag)
			continue;
		minans = min(minans, ans);
	} while (next_permutation(temp, temp + k));
	return minans;
}

int main()
{
	cin >> n >> m >> k;
	fill(head, head + maxn, -1);
	for (int i = 0; i < k; ++i)
		cin >> town[i];
	for (int i = 0; i < m; ++i)
	{
		int u, v, w;
		cin >> u >> v >> w;
		addEdge(u, v, w);
	}
	for (int i = 0; i < k; ++i)
		dijkstra(i, town[i]);
	int ans = 0x7fffffff;
	for (int i = 1; i <= n; ++i)
		ans = min(ans, solve(i));
	cout << ans << endl;
}