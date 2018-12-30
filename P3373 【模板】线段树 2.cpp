#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 100010


struct Node
{
	int l, r;
	long long val, addtag, multag;
	Node(int l, int r) :
		l(l), r(r), addtag(0), multag(1) {}
	Node() {}
} tree[maxn << 2];
long long nums[maxn];
int n, m, p;

long long buildTree(int root, int l, int r)
{
	tree[root] = Node(l, r);
	if (l == r)
		tree[root].val = nums[l] % p;
	else
	{
		int mid = (l + r) >> 1;
		buildTree(root << 1, l, mid);
		buildTree(root << 1 | 1, mid + 1, r);
		tree[root].val = (tree[root << 1].val + tree[root << 1 | 1].val) % p;
	}
	return tree[root].val;
}

void pushDown(int root)
{
	if (tree[root].addtag == 0 && tree[root].multag == 1)
		return;
	if (tree[root].l != tree[root].r)
	{
		tree[root << 1].val = (tree[root << 1].val * tree[root].multag + (tree[root << 1].r + 1 - tree[root << 1].l) * tree[root].addtag) % p;
		tree[root << 1 | 1].val = (tree[root << 1 | 1].val * tree[root].multag + (tree[root << 1 | 1].r + 1 - tree[root << 1 | 1].l) * tree[root].addtag) % p;

		tree[root << 1].multag = (tree[root << 1].multag * tree[root].multag) % p;
		tree[root << 1 | 1].multag = (tree[root << 1 | 1].multag * tree[root].multag) % p;

		tree[root << 1].addtag = (tree[root << 1].addtag * tree[root].multag + tree[root].addtag) % p;
		tree[root << 1 | 1].addtag = (tree[root << 1 | 1].addtag * tree[root].multag + tree[root].addtag) % p;
	}
	tree[root].addtag = 0;
	tree[root].multag = 1;
	return;
}

void update(int root, int l, int r, int k, int op)
{
	pushDown(root);
	if (tree[root].l == l && tree[root].r == r)
	{
		if (op == 1)	//mul
		{
			tree[root].val = (tree[root].val * k) % p;
			tree[root].multag = k;
		}
		else
		{
			tree[root].val = (tree[root].val + ((long long)(r + 1 - l)) * k) % p;
			tree[root].addtag = k;
		}
		return;
	}
	else
	{
		if (tree[root << 1].r >= r)
			update(root << 1, l, r, k, op);
		else if (tree[root << 1 | 1].l <= l)
			update(root << 1 | 1, l, r, k, op);
		else
		{
			update(root << 1, l, tree[root << 1].r, k, op);
			update(root << 1 | 1, tree[root << 1 | 1].l, r, k, op);
		}
		tree[root].val = (tree[root << 1].val + tree[root << 1 | 1].val) % p;
	}
}

long long query(int root, int l, int r)
{
	pushDown(root);
	if (tree[root].l == l && tree[root].r == r)
		return tree[root].val;
	else
	{
		if (tree[root << 1].r >= r)
			return query(root << 1, l, r);
		else if (tree[root << 1 | 1].l <= l)
			return query(root << 1 | 1, l, r);
		else
			return (query(root << 1, l, tree[root << 1].r) + query(root << 1 | 1, tree[root << 1 | 1].l, r)) % p;
	}
}

int main()
{
	cin >> n >> m >> p;
	for (int i = 1; i <= n; ++i)
		cin >> nums[i];
	buildTree(1, 1, n);
	int op, x, y, k;
	for (int i = 0; i < m; ++i)
	{
		cin >> op >> x >> y;
		if (op == 3)
		{
			cout << query(1, x, y) << endl;
		}
		else
		{
			cin >> k;
			update(1, x, y, k % p, op);
		}
	}
}