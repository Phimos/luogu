#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
#define maxn 5000


struct Edge
{
    int u, v, capacity, flow, cost;
    Edge(int u, int v, int capacity, int flow, int cost) :
        u(u), v(v), capacity(capacity), flow(flow), cost(cost) {}
};

vector<Edge> edges;
vector<int> graph[maxn];
int pre[maxn];
int dist[maxn];
bool vis[maxn];
int s, t;
int n, m;

void addEdge(int u, int v, int cap, int cost)
{
    graph[u].push_back(edges.size());
    edges.push_back(Edge(u, v, cap, 0, cost));
    graph[v].push_back(edges.size());
    edges.push_back(Edge(v, u, 0, 0, -cost));
}

struct Node
{
    int id, w;
    Node(int id, int w) : id(id), w(w) {}
    bool operator<(const Node& other)const
    {
        return w > other.w;
    }
};

bool Dijkstra(int s, int t)
{
    priority_queue<Node> Q;
    fill(dist, dist + maxn, 0x7fffffff);
    fill(pre, pre + maxn, -1);
    dist[s] = 0;
    pre[s] = -1;
    Q.push(Node(s, dist[s]));
    while (!Q.empty())
    {
        Node temp = Q.top();
        Q.pop();
        if (dist[temp.id] != temp.w)    //过时了
            continue;
        int u = temp.id;
        for (int i = 0; i < graph[u].size(); ++i)
        {
            Edge temp = edges[graph[u][i]];
            if (dist[temp.v] > dist[u] + edges[graph[u][i]].cost && temp.capacity > temp.flow)
            {
                dist[temp.v] = dist[u] + edges[graph[u][i]].cost;
                pre[temp.v] = graph[u][i];
                Q.push(Node(temp.v, dist[temp.v]));
            }
        }
    }
    return pre[t] != -1;
}


void MCMF(int s, int t, int& flow, int& cost)
{
    flow = 0;
    cost = 0;
    while (Dijkstra(s, t))
    {
        int f = 0x7fffffff;
        for (int i = pre[t]; i != -1; i = pre[edges[i].u])
        {
            Edge temp = edges[i];
            f = min(f, temp.capacity - temp.flow);
        }
        for (int i = pre[t]; i != -1; i = pre[edges[i].u])
        {
            edges[i].flow += f;
            edges[i ^ 1].flow -= f;
            cost += edges[i].cost * f;
        }
        flow += f;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; ++i)
    {
        int u, v, cap, cost;
        cin >> u >> v >> cap >> cost;
        addEdge(u, v, cap, cost);
    }
    int flow, cost;
    MCMF(s, t, flow, cost);
    cout << flow << ' ' << cost << endl;
}