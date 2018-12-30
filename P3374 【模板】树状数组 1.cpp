#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 500010
int arr[maxn];
int n, m;

int lowbit(int x)
{
	return x & (-x);
}
void update(int index, int k)
{
	for (int i = index; i <= n; i += lowbit(i))
		arr[i] += k;
	return;
}
int getsum(int index)
{
	int sum = 0;
	for (int i = index; i > 0; i -= lowbit(i))
		sum += arr[i];
	return sum;
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m;
	int op, x, y;
	for (int i = 1; i <= n; ++i)
	{
		cin >> x;
		update(i, x);
	}
	for (int i = 0; i < m; ++i)
	{
		cin >> op >> x >> y;
		if (op == 1)
			update(x, y);
		else
			cout << getsum(y) - getsum(x - 1) << endl;
	}
}