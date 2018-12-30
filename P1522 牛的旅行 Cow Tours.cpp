#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define maxn 160
int x[maxn], y[maxn];
char grid[maxn][maxn];
double d[maxn][maxn];
double maxdist[maxn];
bool vis[maxn];
double ans1, ans;
int n;

double dist(int i, int j)
{
	double ans = sqrt((double)((y[j] - y[i]) * (y[j] - y[i]) + (x[j] - x[i]) * (x[j] - x[i])));
	return ans;
}

void floyd()
{
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			d[i][j] = 1e20;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (grid[i][j] == '1')
				d[i][j] = dist(i, j);
	for (int i = 0; i < n; ++i)
		d[i][i] = 0;
	for (int k = 0; k < n; ++k)
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	memset(maxdist, 0, sizeof(maxdist));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (i != j && d[i][j] != 1e20)
				maxdist[i] = max(maxdist[i], d[i][j]);
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> x[i] >> y[i];
	for (int i = 0; i < n; ++i)
		cin >> grid[i];
	floyd();
	ans = 1e20;
	ans1 = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (d[i][j] != 1e20)
				ans1 = max(ans1, d[i][j]);
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			if (d[i][j] == 1e20)
				ans = min(ans, maxdist[i] + maxdist[j] + dist(i, j));
	printf("%.6lf\n", max(ans1, ans));
}
