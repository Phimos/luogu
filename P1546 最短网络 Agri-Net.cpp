#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
#define maxn 105
int grid[maxn][maxn];
int dist[maxn];
bool vis[maxn];
int n;

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

int prim()
{
	fill(dist, dist + maxn, 0x7fffffff);
	memset(vis, 0, sizeof(vis));
	priority_queue<Node> pqueue;
	pqueue.push(Node(0, 0));
	dist[0] = 0;
	while (!pqueue.empty())
	{
		Node temp = pqueue.top();
		pqueue.pop();
		if (!vis[temp.to])
		{
			vis[temp.to] = true;
			for (int i = 0; i < n; ++i)
			{
				if (!vis[i] && grid[temp.to][i] < dist[i])
				{
					dist[i] = grid[temp.to][i];
					pqueue.push(Node(i, dist[i]));
				}
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < n; ++i)
		ans += dist[i];
	return ans;
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cin >> grid[i][j];
	cout << prim() << endl;
}