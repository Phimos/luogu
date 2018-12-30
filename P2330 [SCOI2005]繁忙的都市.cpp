#include<iostream>
#include<algorithm>
#include<queue>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
#define maxn 505


struct Node
{
	int u, v, dist;
	Node(int u, int v, int dist) : u(u), v(v), dist(dist) {}
	Node() {}
	bool operator<(const Node& other)const
	{
		return other.dist < dist;
	}
};

int fa[maxn];
priority_queue<Node> pqueue;
int x[maxn], y[maxn];
int n, m;

int getroot(int k)
{
	return fa[k] == k ? k : fa[k] = getroot(fa[k]);
}

void merge(int a, int b)
{
	int ra = getroot(a);
	int rb = getroot(b);
	if (ra != rb)
		fa[rb] = ra;
	return;
}

bool query(int a, int b)
{
	int ra = getroot(a);
	int rb = getroot(b);
	return ra == rb;
}

double kruskal()
{
	int cnt = n - 1;
	int maxdist = 0;
	while (cnt)
	{
		Node temp = pqueue.top();
		pqueue.pop();
		if (query(temp.u, temp.v))
			continue;
		merge(temp.u, temp.v);
		--cnt;
		maxdist = max(maxdist, temp.dist);
	}
	return maxdist;
}


int main()
{
	cin >> n >> m;
	int xx, yy;
	int u, v, c;
	for (int i = 0; i < m; ++i)
	{
		cin >> u >> v >> c;
		pqueue.push(Node(u, v, c));
	}
	for (int i = 0; i < n; ++i)
		fa[i] = i;
	cout << n - 1 << ' ' << kruskal() << endl;
}