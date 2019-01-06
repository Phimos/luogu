#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 500010

long long arr[maxn];
int n;

struct Node
{
	long long idx, num;
	bool operator<(const Node& other)const
	{
		if (num != other.num)
			return num < other.num;
		else
			return idx < other.idx;
	}
} nums[maxn];

long long lb(long long x)
{
	return x & (-x);
}

void update(long long k)
{
	for (int i = k; i <= n; i += lb(i))
		arr[i] += 1;
}

long long getsum(long long k)
{
	long long ans = 0;
	for (int i = k; i > 0; i -= lb(i))
		ans += arr[i];
	return ans;

}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		cin >> nums[i].num;
		nums[i].idx = i;
	}
	sort(nums + 1, nums + n + 1);
	long long ans = 0;
	for (int i = 1; i <= n; ++i)
	{
		update(nums[i].idx);
		ans += i - getsum(nums[i].idx);
	}
	cout << ans << endl;
}