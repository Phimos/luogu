#include<iostream>
#include<queue>
#include<functional>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	int op, x;
	priority_queue<int, vector<int>, greater<int> > heap;
	while (n--)
	{
		cin >> op;
		if (op == 1)
		{
			cin >> x;
			heap.push(x);
		}
		else if (op == 2)
			cout << heap.top() << endl;
		else
			heap.pop();
	}
}
