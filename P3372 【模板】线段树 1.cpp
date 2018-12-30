#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 100010

int n, m, nums[maxn];
struct node
{
	int l, r;
	long long val, lazy;
	node(int l, int r) : l(l), r(r), val(nums[r] - nums[l - 1]), lazy(0) {}
	node() {}
} tree[maxn << 2];

void buildTree(int root, int l, int r)
{
	tree[root] = node(l, r);
	if (l == r)
		return;
	int mid = (l + r) >> 1;
	buildTree(root << 1, l, mid);
	buildTree(root << 1 | 1, mid + 1, r);
}
void pushdown(int root)
{
	if (!tree[root].lazy)
		return;
	tree[root].val += tree[root].lazy * (tree[root].r + 1 - tree[root].l);
	if (tree[root].l != tree[root].r)
	{
		tree[root << 1].lazy += tree[root].lazy;
		tree[root << 1 | 1].lazy += tree[root].lazy;
	}
	tree[root].lazy = 0;
}
void update(int root, int l, int r, long long k)
{
	if (tree[root].l == l && tree[root].r == r)
	{
		tree[root].lazy += k;
		return;
	}
	else
	{
		tree[root].val += (r + 1 - l) * k;
		if (tree[root << 1 | 1].l > r)
			update(root << 1, l, r, k);
		else if (tree[root << 1].r < l)
			update(root << 1 | 1, l, r, k);
		else
		{
			update(root << 1, l, tree[root << 1].r, k);
			update(root << 1 | 1, tree[root << 1 | 1].l, r, k);
		}
	}
}
long long query(int root, int l, int r)
{
	pushdown(root);
	if (tree[root].l == l && tree[root].r == r)
	{
		return tree[root].val;
	}
	else
	{
		if (tree[root << 1 | 1].l > r)
			return query(root << 1, l, r);
		else if (tree[root << 1].r < l)
			return query(root << 1 | 1, l, r);
		else
			return query(root << 1, l, tree[root << 1].r) + query(root << 1 | 1, tree[root << 1 | 1].l, r);
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m;
	int op, x, y, k;
	nums[0] = 0;
	for (int i = 1; i <= n; ++i)
	{
		cin >> nums[i];
		nums[i] += nums[i - 1];
	}
	buildTree(1, 1, n);
	for (int i = 0; i < m; ++i)
	{
		cin >> op;
		if (op == 1)
		{
			cin >> x >> y >> k;
			update(1, x, y, k);
		}
		else
		{
			cin >> x >> y;
			cout << query(1, x, y) << endl;
		}
	}
}