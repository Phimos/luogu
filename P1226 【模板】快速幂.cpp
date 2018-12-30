#include<iostream>
#include<cstdio>
using namespace std;

long long b, p, k;
long long ans;

int main()
{
	scanf("%lld%lld%lld", &b, &p, &k);
	printf("%lld^%lld mod %lld=", b, p, k);
	ans = 1;
	for (; p; p >>= 1)
	{
		if (p & 1)
			ans = (ans * b) % k;
		b = (b * b) % k;
	}
	printf("%lld\n", ans % k);
}