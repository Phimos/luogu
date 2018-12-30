#include<iostream>
#include<string>
#include<queue>
#include<cstring>
using namespace std;
#define maxn 100010
struct Node
{
	Node *children[2];
	Node *fail;
	bool bad, vis;
};

Node tree[maxn];
int nodecnt = 2;

void insert(string& virus)
{
	Node* pnode = tree + 1;
	for (int i = 0; i < virus.length(); ++i)
	{
		if (pnode->children[virus[i] - '0'] == NULL)
			pnode->children[virus[i] - '0'] = tree + (nodecnt++);
		pnode = pnode->children[virus[i] - '0'];
	}
	pnode->bad = true;
}

void buildDFA()
{
	tree->children[0] = tree->children[1] = tree + 1;
	tree[1].fail = tree;
	queue<Node*> qnodes;
	qnodes.push(tree + 1);
	while (!qnodes.empty())
	{
		Node* proot = qnodes.front();
		qnodes.pop();
		for (int i = 0; i < 2; ++i)
		{
			Node* pchild = proot->children[i];
			if (pchild)
			{
				pchild->fail = proot->fail->children[i];
				if (pchild->fail->bad)
					pchild->bad = true;
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

bool dfs(Node* root)
{
	if (root->vis)
		return true;
	root->vis = true;
	for (int i = 0; i < 2; ++i)
		if (!(root->children[i]->bad) && dfs(root->children[i]))
			return true;
	root->vis = false;
	return false;
}

int main()
{
	int n;
	string s;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> s;
		insert(s);
	}
	buildDFA();
	if (dfs(tree + 1))
		cout << "TAK" << endl;
	else
		cout << "NIE" << endl;
}