#include<iostream>
#include<string>
#include<vector>
using namespace std;
#define maxn 1000010
int NEXT[maxn];
string S1, S2;

void getnext()
{
	int k = -1, i = 0;
	NEXT[i] = k;
	while (i < S2.length())
	{
		while (k >= 0 && S2[i] != S2[k])
			k = NEXT[k];
		++k;
		++i;
		NEXT[i] = k;
	}
}

int main()
{
	cin >> S1 >> S2;
	vector<int> ans;
	getnext();
	int i = 0, j = 0;
	for (; i <= S1.length();)
	{
		if (j == S2.length())
		{
			j = NEXT[j];
			ans.push_back(i + 1 - S2.length());
			continue;
		}
		if (i == S1.length())
			break;
		if (S1[i] == S2[j])
			++i, ++j;
		else
		{
			j = NEXT[j];
			if (j == -1)
				++i, ++j;
		}
	}
	for (int i = 0; i < ans.size(); ++i)
		cout << ans[i] << endl;
	cout << NEXT[1];
	for (int i = 2; i <= S2.length(); ++i)
		cout << ' ' << NEXT[i];
	cout << endl;
}