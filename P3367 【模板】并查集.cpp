#include<iostream>
using namespace std;
#define maxn 10010
int parent[maxn];
int n, m;

int getroot(int x)
{
	return x == parent[x] ? x : parent[x] = getroot(parent[x]);
}

void merge(int a, int b)
{
	int pa = getroot(a);
	int pb = getroot(b);
	if (pa != pb)
		parent[pb] = pa;
	return;
}

bool query(int a, int b)
{
	int pa = getroot(a);
	int pb = getroot(b);
	return pa == pb;
}

int main()
{
	cin >> n >> m;
	int op, x, y;
	for (int i = 1; i <= n; ++i)
		parent[i] = i;
	for (int i = 0; i < m; ++i)
	{
		cin >> op >> x >> y;
		if (op == 1)
			merge(x, y);
		else
		{
			if (query(x, y))
				cout << 'Y' << endl;
			else
				cout << 'N' << endl;
		}
	}
}