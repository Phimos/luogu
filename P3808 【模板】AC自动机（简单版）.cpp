#include<iostream>
#include<string>
#include<queue>
using namespace std;
#define maxn 1000010
struct Node
{
	Node* pchild[26];
	Node* fail;
	int match_cnt;
	Node()
	{
		memset(pchild, 0, sizeof(pchild));
		fail = NULL;
		match_cnt = 0;
	}
};

Node tree[maxn];
int nodecnt = 2;

void insert(Node *root, string s)
{
	for (int i = 0; i < s.length(); ++i)
	{
		if (root->pchild[s[i] - 'a'] == NULL)
			root->pchild[s[i] - 'a'] = tree + (nodecnt++);
		root = root->pchild[s[i] - 'a'];
	}
	root->match_cnt++;
}

void buildDFA()
{
	for (int i = 0; i < 26; ++i)
		tree[0].pchild[i] = tree + 1;
	tree[1].fail = tree;
	queue<Node*> qnodes;
	qnodes.push(tree + 1);
	while (!qnodes.empty())
	{
		Node* proot = qnodes.front();
		qnodes.pop();
		for (int i = 0; i < 26; ++i)
		{
			Node* pnode = proot->pchild[i];
			if (pnode)
			{
				Node *pfail = proot->fail;
				pnode->fail = pfail->pchild[i];
				qnodes.push(pnode);
			}
			else
			{
				if (proot == tree + 1)
					proot->pchild[i] = tree + 1;
				else
					proot->pchild[i] = proot->fail->pchild[i];
			}
		}
	}
}

int search(string s)
{
	int ans = 0;
	Node* pnode = tree + 1;
	for (int i = 0; i < s.length(); ++i)
	{
		pnode = pnode->pchild[s[i] - 'a'];
		while (pnode->match_cnt != -1)
		{
			ans += pnode->match_cnt;
			pnode->match_cnt = -1;
		}
	}
	return ans;
}

int main()
{
	int k;
	string s;
	cin >> k;
	for (int i = 0; i < k; ++i)
	{
		cin >> s;
		insert(tree + 1, s);
	}
	buildDFA();
	cin >> s;
	cout << search(s) << endl;
}