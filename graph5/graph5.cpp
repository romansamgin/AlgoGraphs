#include <iostream>
#include <vector>
#include <queue>


#define INF 1000000

using namespace std;


void get_data(vector<vector<pair<int, int >>> &graph,
	vector<int>& destinations, int m) {
	for (int i = 0; i < destinations.size(); ++i) {
		cin >> destinations[i];
	}
	for (int i = 0; i < m; ++i) {
		int x, y, w;
		cin >> x >> y >> w;
		graph[x].push_back(make_pair(y, w));
		graph[y].push_back(make_pair(x, w));
	}
}

vector<int> dijkstra(const vector<vector<pair<int, int>>>& graph, const int source) {

	vector<int>d(graph.size(), INF);
	vector<bool>used(graph.size(), false);
	d[source] = 0;
	for (int i = 0; i < graph.size(); ++i) {
		int v = -1;
		for (int j = 0; j < graph.size(); ++j) {
			if (!used[j] && (v == -1 || d[j] < d[v])) {
				v = j;
			}
		}
		if (d[v] == INF) {
			break;
		}
		used[v] = true;
		for (auto e : graph[v]) {
			if (d[v] + e.second < d[e.first]) {
				d[e.first] = d[v] + e.second;
			}
		}
	}
	return d;
}

vector<vector<int>> get_parents_graph(const vector<vector<pair<int, int>>>& graph, 
	const vector<int>& shortest) {

	vector<vector<int>>parents_graph(graph.size());
	for (int u = 0; u < graph.size(); ++u) {
		for (auto v : graph[u]) {
			if (shortest[u] == shortest[v.first] + v.second) {
				parents_graph[u].push_back(v.first);
			}
		}
	}
	return parents_graph;
}

void bfs(const vector<vector<int>>& parents_graph, int src, int point,
	vector<int>& checkpoints) {
	if (checkpoints[src] == point - 1) {
		checkpoints[src] = point;
	}	
	queue<int>q{};
	q.push(src);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v : parents_graph[u]) {
			if (checkpoints[v] == point - 1) {
				checkpoints[v] = point;
			}
			if (v != 0) {
				q.push(v);
			}			
		}
	}
}

int find_max_parent(const vector<int>& checkpoints, const vector<int>& shortest, int k) {
	int max = 0;
	for (int i = 0; i < checkpoints.size(); i++)
		if (checkpoints[i] == k - 1) {
			if (max < shortest[i]) {
				max = shortest[i];
			}
		}
	return max;
}

int main()
{
	int n, m, k;
	cin >> n >> m >> k;
	vector<vector<pair<int, int >>>graph(n);
	vector<int> destinations(k);
	get_data(graph, destinations, m);

	vector<int>shortest(n);
	shortest = dijkstra(graph, 0);

	vector<vector<int>>parents_graph(n); 
	parents_graph = get_parents_graph(graph,  shortest);

	vector<int> checkpoints(parents_graph.size(), -1);

	for (int i = 0; i < destinations.size(); ++i) {
		bfs(parents_graph, destinations[i], i, checkpoints);
	}

	cout << find_max_parent(checkpoints, shortest, k) << endl;
	return 0;
}