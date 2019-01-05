#include<cstdio>
#include<iostream>
using namespace std;

char temp[10];
int l[30], r[30];
bool vis[30];

void ldr(int k)
{
	if (k + 'a' == '*')
		return;
	printf("%c", k + 'a');
	ldr(l[k]);
	ldr(r[k]);
}

int main()
{
	int n, root;
	scanf("%d", &n);
	fill(l, l + 30, -1);
	fill(r, r + 30, -1);
	for (int i = 0; i < n; ++i)
	{
		scanf("%s", temp);
		l[temp[0] - 'a'] = temp[1] - 'a';
		if (temp[1] != '*')
			vis[temp[1] - 'a'] = true;
		r[temp[0] - 'a'] = temp[2] - 'a';
		if (temp[2] != '*')
			vis[temp[2] - 'a'] = true;
	}
	for (int i = 0; i < 30; ++i)
		if (l[i] != -1 && !vis[i])
			root = i;
	ldr(root);
	printf("\n");
}