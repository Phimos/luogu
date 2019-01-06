#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
using namespace std;
#define maxn 2000
struct Node
{
	Node* children[26];
	Node* fail;
	bool bad;
} tree[maxn];
bool dp[1000010];
int n, m;
int nodecnt = 2;
int ans;
string str;

void insert(string& s)
{
	Node* root = tree + 1;
	for (int i = 0; i < s.length(); ++i)
	{
		if (root->children[s[i] - 'a'] == NULL)
			root->children[s[i] - 'a'] = tree + (nodecnt++);
		root = root->children[s[i] - 'a'];
	}
	root->bad = true;
	return;
}


bool search(string & s, int k)
{
	Node* root = tree + 1;
	for (int i = k - 1; i >= 0; --i)
	{
		root = root->children[s[i] - 'a'];
		if (root == NULL)
			return false;
		if (root->bad && dp[i])
		{
			ans = max(ans, k);
			dp[k] = true;
			return true;
		}
	}
	return false;
}

int main()
{
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
	{
		cin >> str;
		reverse(str.begin(), str.end());
		insert(str);
	}
	for (int i = 0; i < m; ++i)
	{
		cin >> str;
		ans = 0;
		memset(dp, 0, sizeof(dp));
		dp[0] = true;
		for (int i = 1; i <= str.length(); ++i)
			search(str, i);
		cout << ans << endl;
	}
}