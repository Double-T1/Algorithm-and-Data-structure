//assuming the given graph is represented by adjList

#include <iostream>
#include <vector>
using namespace std;

//assuming the given graph is represented by adjList
typedef vector<vector<int>> vvi;
static int i= 0;

void dfs(vvi& edges, vvi& adj, int cur, int id[], int low[]);

vector<vector<int>> criticalEdges(vvi& adj) {
    int n = (int)adj.size(); //number of nodes
    vvi edges;
    int low[n], id[n];
    memset(low,-1,sizeof(low));
    for (int i=0; i<n; i++) {
        if (low[i] == -1)
            dfs(edges,adj,i,id,low);
    }
    return edges;
}

void dfs(vvi& edges, vvi& adj, int cur, int id[], int low[]) {
    id[cur] = low[cur] = i++;
    
    for (auto next : adj[cur]) {
        if (id[next] == id[cur]-1) continue;
        if (low[next] > -1) {
            low[cur] = min(low[cur],id[next]); //or low[next] will also work
        } else {
            dfs(edges,adj,next,id,low);
            low[cur] = min(low[cur],low[next]);
            if (id[cur]<low[next]) {
                edges.push_back({cur,next});
            }
        }
    }
}
