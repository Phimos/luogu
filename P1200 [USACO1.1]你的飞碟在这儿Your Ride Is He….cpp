#include<iostream>
#include<string>
using namespace std;

int Hash(string& s)
{
	int ans = 1;
	for (int i = 0; i < s.size(); ++i)
		ans *= s[i] - 'A' + 1;
	return ans % 47;
}

int main()
{
	string group, comet;
	cin >> comet >> group;
	if (Hash(group) == Hash(comet))
		cout << "GO" << endl;
	else
		cout << "STAY" << endl;
}