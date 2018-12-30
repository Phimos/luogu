#include<iostream>
#include<algorithm>
using namespace std;

int n, b;
int vol[24];
int farm[104];
int ans[100010];

int dp(int k)
{
	if (k < 0)
		return 0x3f3f3f3f;
	if (ans[k] != -1)
		return ans[k];
	int mincow = 0x7fffffff;
	for (int i = 0; i < b; ++i)
		mincow = min(mincow, dp(k - vol[i]) + 1);
	ans[k] = mincow;
	return ans[k];
}

int main()
{
	cin >> n >> b;
	for (int i = 0; i < b; ++i)
		cin >> vol[i];
	for (int i = 0; i < n; ++i)
		cin >> farm[i];
	int maxvol = farm[0];
	for (int i = n - 1; i > 0; --i)
	{
		farm[i] -= farm[i - 1] - (farm[i - 1] != 0);
		maxvol = max(farm[i], maxvol);
	}
	fill(ans, ans + 100010, -1);
	ans[0] = 0;
	for (int i = 1; i <= maxvol; ++i)
		dp(i);
	int sum = 0;
	for (int i = 0; i < n; ++i)
		if (ans[farm[i]] < 0x3f3f3f3f)
			sum += ans[farm[i]];
	cout << sum << endl;
}