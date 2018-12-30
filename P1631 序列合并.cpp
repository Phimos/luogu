#include<iostream>
#include<algorithm>
#include<functional>
#include<queue>
using namespace std;
#define maxn 100010
int n;
int a[maxn], b[maxn];
int ans[maxn];

int main()
{
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	for (int i = 0; i < n; ++i)
		cin >> b[i];
	priority_queue<int> pqueue;
	for (int i = 0; i < n; ++i)
		pqueue.push(a[0] + b[i]);
	for (int i = 1; i < n; ++i)
		for (int j = 0; j < n; ++j)
		{
			if (a[i] + b[j] < pqueue.top())
			{
				pqueue.pop();
				pqueue.push(a[i] + b[j]);
			}
			else
				break;
		}
	for (int i = 1; i <= n; ++i)
	{
		ans[n - i] = pqueue.top();
		pqueue.pop();
	}
	cout << ans[0];
	for (int i = 1; i < n; ++i)
		cout << ' ' << ans[i];
	cout << endl;
}