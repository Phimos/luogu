#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 210
int n, m;
int dist[maxn][maxn];
int t[maxn];

void update(int k)
{
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			dist[i][j] = min(dist[i][k] + dist[k][j], dist[i][j]);
}

int main()
{
	cin >> n >> m;
	int p, x, y, q, cnt = 0;
	for (int i = 0; i < n; ++i)
		cin >> t[i];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			dist[i][j] = 0x3fffffff;
	for (int i = 0; i < n; ++i)
		dist[i][i] = 0;
	for (int i = 0; i < m; ++i)
	{
		cin >> x >> y >> p;
		dist[x][y] = dist[y][x] = p;
	}
	cin >> q;
	for (int i = 0; i < q; ++i)
	{
		cin >> x >> y >> p;
		while (t[cnt] <= p && cnt < n)
			update(cnt++);
		cout << ((dist[x][y] == 0x3fffffff || x >= cnt || y >= cnt) ? -1 : dist[x][y]) << endl;
	}
}