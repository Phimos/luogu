#include<iostream>
using namespace std;
int dp[210][8];
int solve(int n, int k)
{
	if (n < 0)
		return 0;
	if (dp[n][k] != 0)
		return dp[n][k];
	if (k == 1 || n == 1 || n == 0)
		return 1;
	else
	{
		dp[n][k] = solve(n - k, k) + solve(n, k - 1);
		return dp[n][k];
	}
}

int main()
{
	int n, k;
	cin >> n >> k;
	cout << solve(n - k, k);
}