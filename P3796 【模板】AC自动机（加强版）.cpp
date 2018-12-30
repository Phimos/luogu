#include<iostream>
#include<cstring>
#include<string>
#include<queue>
#include<algorithm>
using namespace std;
#define maxn 200010

struct Node
{
	Node* children[26];
	Node *fail, *last;
	int bad;
	Node()
	{
		memset(children, 0, sizeof(children));
		fail = last = NULL;
		bad = 0;
	}
};

Node tree[maxn];
string strs[160];
int n, cnt[160];
int nodecnt = 2, badcnt = 1;

void init()
{
	memset(tree, 0, sizeof(tree));
	memset(cnt, 0, sizeof(cnt));
	nodecnt = 2;
	badcnt = 1;
}

void insert(string& s)
{
	Node* root = tree + 1;
	for (int i = 0; i < s.length(); ++i)
	{
		if (root->children[s[i] - 'a'] == NULL)
			root->children[s[i] - 'a'] = tree + (nodecnt++);
		root = root->children[s[i] - 'a'];
	}
	root->bad = badcnt++;
	return;
}

void buildlast(Node* pchild)
{
	if (pchild->fail->bad)
		pchild->last = pchild->fail;
	else
		pchild->last = pchild->fail->last;
}

void buildDFA()
{
	for (int i = 0; i < 26; ++i)
		tree->children[i] = tree + 1;
	tree[1].fail = tree;
	queue<Node*> qnodes;
	qnodes.push(tree + 1);
	while (!qnodes.empty())
	{
		Node* proot = qnodes.front();
		qnodes.pop();
		for (int i = 0; i < 26; ++i)
		{
			Node* pchild = proot->children[i];
			if (pchild)
			{
				pchild->fail = proot->fail->children[i];
				buildlast(pchild);
				qnodes.push(pchild);
			}
			else
			{
				if (proot == tree + 1)
					proot->children[i] = tree + 1;
				else
					proot->children[i] = proot->fail->children[i];
			}
		}
	}
}

void search(const string& s)
{
	Node* pnode = tree + 1;
	for (int i = 0; i < s.length(); ++i)
	{
		pnode = pnode->children[s[i] - 'a'];
		for (Node* p = pnode; p; p = p->last)
			if (p->bad)
				cnt[p->bad]++;
	}
	return;
}

struct sort_node
{
	int i, times;
	sort_node(int i) : i(i), times(cnt[i]) {}
	sort_node() {}
	bool operator<(const sort_node& b)const
	{
		if (times != b.times)
			return b.times < times;
		else
			return i < b.i;
	}
};

void output()
{
	sort_node forsort[160];
	for (int i = 1; i <= n; ++i)
		forsort[i] = sort_node(i);
	sort(forsort + 1, forsort + n + 1);
	cout << forsort[1].times << endl;
	for (int i = 1; i <= n && forsort[i].times == forsort[1].times; ++i)
		cout << strs[forsort[i].i] << endl;
}

int main()
{
	while (cin >> n, n)
	{
		string s;
		init();
		for (int i = 1; i <= n; ++i)
		{
			cin >> strs[i];
			insert(strs[i]);
		}
		buildDFA();
		cin >> s;
		search(s);
		output();
	}
}
