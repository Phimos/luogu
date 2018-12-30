#include<iostream>
#include<algorithm>
using namespace std;


int main()
{
	long long n, sum = 0, num, maxSum = 0x80000000;
	cin >> num;
	maxSum = sum = num;
	for (int i = 1; i < n; ++i)
	{
		if (sum < 0)
			sum = 0;
		cin >> num;
		sum += num;
		if (sum > 0)
			maxSum = max(maxSum, sum);
	}
	cout << maxSum << endl;
}