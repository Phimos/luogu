#include<iostream>
#include<string>
#include<cstdio>
using namespace std;

#define maxn 1000010

int wa[maxn], wb[maxn];
int wv[maxn], Ws[maxn];
int sa[maxn];
char str[maxn];

void buildSA(const char* s, int sa[], int n, int m)
{
	int i, j, p, *rank = wa, *k2sa = wb, *t;
	for (i = 0; i < m; ++i)
		Ws[i] = 0;
	for (i = 0; i < n; ++i)
		Ws[rank[i] = s[i]]++;
	for (i = 1; i < m; ++i)
		Ws[i] += Ws[i - 1];
	for (i = n - 1; i >= 0; --i)
		sa[--Ws[rank[i]]] = i;
	for (j = p = 1; p < n; j <<= 1, m = p)
	{
		for (p = 0, i = n - j; i < n; ++i)
			k2sa[p++] = i;
		for (i = 0; i < n; ++i)
			if (sa[i] >= j)
				k2sa[p++] = sa[i] - j;
		for (i = 0; i < m; ++i)
			Ws[i] = 0;
		for (i = 0; i < n; ++i)
			Ws[wv[i] = rank[k2sa[i]]]++;
		for (i = 1; i < m; ++i)
			Ws[i] += Ws[i - 1];
		for (i = n - 1; i >= 0; --i)
			sa[--Ws[wv[i]]] = k2sa[i];
		for (t = rank, rank = k2sa, k2sa = t, rank[sa[0]] = 0, p = i = 1; i < n; ++i)
		{
			int a = sa[i - 1], b = sa[i];
			if (k2sa[a] == k2sa[b] && k2sa[a + j] == k2sa[b + j])
				rank[sa[i]] = p - 1;
			else
				rank[sa[i]] = p++;
		}
	}
	return;
}


int main()
{
	scanf("%s", str);
	int n;
	for (n = 0; str[n]; ++n)
		;
	buildSA(str, sa, n, 128);
	printf("%d", sa[0] + 1);
	for (int i = 1; i < n; ++i)
		printf(" %d", sa[i] + 1);
	printf("\n");
}