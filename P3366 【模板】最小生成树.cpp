#include<iostream>
#include<algorithm>
#include<functional>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
#define maxn 5010

struct Edge
{
	int to, next, w;
	Edge(int to, int next, int w) : to(to), next(next), w(w) {}
	Edge() {}
};

vector<Edge> edges;
int head[maxn], mindist[maxn];
bool vis[maxn];
int sumdist;
int n, m;

void addEdge()
{
	int x, y, w;
	cin >> x >> y >> w;
	Edge temp = Edge(y, head[x], w);
	head[x] = edges.size();
	edges.push_back(temp);
	temp = Edge(x, head[y], w);
	head[y] = edges.size();
	edges.push_back(temp);
}

struct Node
{
	int id, w;
	Node(int id, int w) : id(id), w(w) {}
	bool operator<(const Node& other)const
	{
		return other.w < w;
	}
};

bool prim()
{
	priority_queue<Node> pqueue;
	fill(mindist, mindist + maxn, 0x7fffffff);
	memset(vis, 0, sizeof(vis));
	pqueue.push(Node(1, 0));
	while (!pqueue.empty())
	{
		Node temp = pqueue.top();
		pqueue.pop();
		if (!vis[temp.id])
		{
			vis[temp.id] = true;
			sumdist += temp.w;
			for (int i = head[temp.id]; ~i; i = edges[i].next)
			{
				Edge& tempE = edges[i];
				if (tempE.w < mindist[tempE.to])
				{
					mindist[tempE.to] = tempE.w;
					pqueue.push(Node(tempE.to, tempE.w));
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i)
		if (!vis[i])
			return false;
	return true;
}

int main()
{
	cin >> n >> m;
	fill(head, head + n + 1, -1);
	for (int i = 0; i < m; ++i)
		addEdge();
	if (prim())
		cout << sumdist << endl;
	else
		cout << "orz" << endl;
}
