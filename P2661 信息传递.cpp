#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define maxn 200010

int partner[maxn];
int vis[maxn];
int n, cnt, s, ans;

void dfs(int k)
{
	while (!vis[partner[k]])
	{
		vis[partner[k]] = ++cnt;
		k = partner[k];
	}
	if (vis[partner[k]] >= s)
		ans = min(1 + vis[k] - vis[partner[k]], ans);
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> partner[i];
	cnt  = 0;
	ans = 0x7fffffff;
	for (int i = 1; i <= n; ++i)
	{
		if (!vis[i])
		{
			vis[i] = ++cnt;
			s = vis[i];
			dfs(i);
		}
	}
	cout << ans << endl;
}