#include <bits/stdc++.h>

using namespace std; 

#define int long long int 
#define MAX 1001 

int n, m; 
int dist[MAX]; 
vector<pair<int, int>> adj[MAX]; 
int par[MAX]; // Removed if path not needed
bool visited[MAX];


void dijkstra(int s) { // boolean dijkstra(int s, int d)
    for (int i = 1; i <= n; i++) {
        dist[i] = INFINITY; 
        visited[i] = false; 
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[s] = 0; 
    par[s] = -1; 

    pq.push({ dist[s], s}); 

    while (!pq.empty()) {
        int v = pq.top().second; 

        // if (v == d) return true;

        pq.pop(); 

        visited[v] = true; 

        for (auto const& a : adj[v]) {
            int u = a.first; 
            int w = a.second; 

            if (!visited[u] && dist[v] + w < dist[u] ) {
                dist[u] = dist[v] + w;
                pq.push({ dist[u], u} );
                par[u] = v; // Remove if path not needed
            }
        } 

    }

    // return false; 
}

vector<int> min_path(int d) {
    vector<int> path; 

    while (d != - 1) {
        path.push_back(d); 
        d = par[d]; 
    }

    reverse(path.begin(), path.end()); 
    return path; 
}

signed main() {
    cin >> n >> m; 
    
    for (int i = 0; i < m; i++) {
        int u, v, w; 
        cin >> u >> v >> w; 

        adj[u].push_back({ v, w }); 
        adj[v].push_back({ u, w }); 
    }
}