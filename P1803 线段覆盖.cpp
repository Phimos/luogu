#include<cstdio>
#include<algorithm>
using namespace std;
#define maxn 1000010
struct Line
{
	int s, t;
	Line(int s, int t) : s(s), t(t) {}
	Line() {}
	bool operator<(const Line& other)const
	{
		if (t != other.t)
			return t < other.t;
		else
			return s < other.s;
	}
} lines[maxn];
int n;
int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d%d", &lines[i].s, &lines[i].t);
	sort(lines, lines + n);
	int sum = 0;
	int rmax = 0x80000000;
	for (int i = 0; i < n; ++i)
	{
		if (lines[i].s >= rmax)
		{
			++sum;
			rmax = lines[i].t;
		}
	}
	printf("%d\n", sum);
	return 0;
}