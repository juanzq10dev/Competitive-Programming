#include <bits/stdc++.h>

using namespace std;

#define int long long int
#define MAX 1001

/* 
* Get the min path from a vertex to other. 
* Run dijkstra(s) before running all methods. 
* Methods where done to put real values, no need to sum or substract anything. 
*/

int n, m; // n = num of vertex, m = num of paths.
vector<pair<int, int>> adj[MAX];
bool visited[MAX];
int dist[MAX];
vector<int> path[MAX]; // To get min path

void dijkstra(int s) { // s means src
    s--;

    for (int i = 0; i < n; i++) {
        visited[i] = false;
        dist[i] = INT_MAX;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    dist[s] = 0;
    q.push({ s, dist[s] });

    while (!q.empty()) {
        int v = q.top().first;
        q.pop();
        if (visited[v]) {
            continue;
        }

        visited[v] = true;
        for (auto const& a : adj[v]) {
            int u = a.first;
            int w = a.second;

            if (dist[u] > dist[v] + w) {
                dist[u] = dist[v] + w;

                path[u] = path[v]; // To get min path 
                path[u].push_back(v + 1); // To get min path 

                q.push({ u, dist[u] });
            }
        }
    }
}

int min_weight(int d) { // Returns min weight from src to d. 
    d--;
    return dist[d];
}

void print_all_min_weights() {
    for (int i = 0; i < n; i++) {
        cout << "Minimum weight from src to " << (i + 1) << ": " << dist[i] << '\n';
    }
}

vector<int> min_path(int d) { // Returns min weight from src to d. 
    d--; 

    return path[d];
}

void print_all_min_paths() {

    for (int i = 0; i < n; i++) {
        vector<int> min_path = path[i];

        cout << "Min path from src to " << i + 1 << ": ";
        for (int v : min_path) {
            cout << v << " ";
        }
        cout << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
        v1--; v2--;
        adj[v1].push_back({ v2, w });
        adj[v2].push_back({ v1, w });
    }
}