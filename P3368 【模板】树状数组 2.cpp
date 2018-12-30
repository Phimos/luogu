#include<iostream>
using namespace std;
#define maxn 500010

int arr[maxn];		//差分数组	differ[i]=a[i]-a[i-1] (i>0)
int n, m;			//			differ[0]=a[0]

int lowbit(int x)
{
	return x & (-x);
}
void update(int x, int k)
{
	for (int i = x; i <= n; i += lowbit(i))
		arr[i] += k;
	return;
}
int getsum(int x)
{
	int sum = 0;
	for (int i = x; i > 0; i -= lowbit(i))
		sum += arr[i];
	return sum;
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m;
	int op, x, y, k;
	cin >> x;
	update(1, x);
	for (int i = 2; i <= n; ++i)
	{
		cin >> y;
		update(i, y - x);
		x = y;
	}
	for (int i = 0; i < m; ++i)
	{
		cin >> op >> x;
		if (op == 1)
		{
			cin >> y >> k;
			update(x, k);
			update(y + 1, -k);
		}
		else
		{
			cout << getsum(x) << endl;
		}
	}
}