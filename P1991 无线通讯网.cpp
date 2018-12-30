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
	int u, v;
	double dist;
	Node(int u, int v, double dist) :u(u), v(v), dist(dist) {}
	Node() {}
	bool operator<(const Node& other)const
	{
		return other.dist < dist;
	}
};

int fa[maxn];
priority_queue<Node> pqueue;
int x[maxn], y[maxn];
int s, p;

double getdist(int a, int b)
{
	return sqrt(double((x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b])));
}

void init()
{
	for (int i = 0; i < p; ++i)
		for (int j = i + 1; j < p; ++j)
			pqueue.push(Node(i, j, getdist(i, j)));
	for (int i = 0; i < p; ++i)
		fa[i] = i;

}

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
	int cnt = p - s;
	double maxdist = 0;
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
	cin >> s >> p;
	int xx, yy;
	for (int i = 0; i < p; ++i)
	{
		cin >> xx >> yy;
		x[i] = xx;
		y[i] = yy;
	}
	init();
	printf("%.2lf\n", kruskal());
}