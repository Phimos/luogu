#include<iostream>
using namespace std;

int carpets[10010][4];
int n, a, b;

bool cover(int i)
{
	return carpets[i][0] <= a && a <= carpets[i][0] + carpets[i][2] && carpets[i][1] <= b && b <= carpets[i][1] + carpets[i][3];
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < 4; ++j)
			cin >> carpets[i][j];
	cin >> a >> b;
	for (int i = n - 1; i >= 0; --i)
		if (cover(i))
		{
			cout << i + 1 << endl;
			return 0;
		}
	cout << -1 << endl;
}