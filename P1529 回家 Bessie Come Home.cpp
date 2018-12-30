#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
#define maxn 80
int farm[maxn][maxn];
int dist[maxn];
int n;
int order(char k)
{
	if ('a' <= k && k <= 'z')
		return k - 'a';
	else
		return k - 'A' + 26;
}

void dijkstra()
{
	priority_queue<pair<int, int> > travel;
	memset(dist, 0x3f, sizeof(dist));
	travel.push(make_pair(0, 51));
	dist[51] = 0;
	while (!travel.empty())
	{
		pair<int, int> temp = travel.top();
		travel.pop();
		for (int i = 0; i < 52; ++i)
		{
			if (dist[i] > dist[temp.second] + farm[temp.second][i])
			{
				dist[i] = dist[temp.second] + farm[temp.second][i];
				travel.push(make_pair(dist[i], i));
			}
		}
	}
	return;
}


int main()
{
	cin >> n;
	char a, b;
	int ia, ib;
	int w;
	memset(farm, 0x3f, sizeof(farm));
	for (int i = 0; i < 52; ++i)
		farm[i][i] = 0;
	for (int i = 0; i < n; ++i)
	{
		cin >> a >> b >> w;
		ia = order(a), ib = order(b);
		farm[ia][ib] = farm[ib][ia] = min(farm[ia][ib], w);
	}
	dijkstra();
	int cownum, minlen = 0x7fffffff;
	for (int i = 26; i < 51; ++i)
	{
		if (dist[i] < minlen)
		{
			minlen = dist[i];
			cownum = i;
		}
	}
	cout << (char)('A' + cownum - 26) << ' ' << minlen << endl;
}