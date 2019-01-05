#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
#define maxn 105

int n, s, t;
int grid[maxn][maxn];
int dist[maxn];

struct Node
{
	int to, d;
	Node(int to, int d) : to(to), d(d) {}
	Node() {}
	bool operator<(const Node& other)const
	{
		return other.d < d;
	}
};

int dijkstra()
{
	fill(dist, dist + maxn, 0x7fffffff);
	priority_queue<Node> pqueue;
	dist[s] = 0;
	pqueue.push(Node(s, 0));
	while (!pqueue.empty())
	{
		Node temp = pqueue.top();
		pqueue.pop();
		if (dist[temp.to] == temp.d)
		{
			for (int i = 1; i <= n; ++i)
			{
				if (grid[temp.to][i] != 0x7fffffff && dist[i] > dist[temp.to] + grid[temp.to][i])
				{
					dist[i] = dist[temp.to] + grid[temp.to][i];
					pqueue.push(Node(i, dist[i]));
				}
			}
		}
	}
	if (dist[t] == 0x7fffffff)
		return -1;
	else
		return dist[t];
}

int main()
{
	cin >> n >> s >> t;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			grid[i][j] = 0x7fffffff;
	for (int i = 1; i <= n; ++i)
	{
		int k, c;
		cin >> k;
		if (k > 0)
		{
			cin >> c;
			grid[i][c] = 0;
			for (int j = 1; j < k; ++j)
			{
				cin >> c;
				grid[i][c] = 1;
			}
		}
	}
	cout << dijkstra() << endl;
}