#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;
const int MAXN = 1000;
const int INF = numeric_limits<int>::max();

template <typename T>
void print(const vector<T>& v) {
	for (size_t i = 0; i < v.size(); ++i)
		cout << v[i] << " ";
	cout << '\n';
}

vector<int> ans{};
vector<int> visited{};

void dfs(int u, const vector<vector<int>>& g) {
	visited[u] = true;
	for (int v = 0; v < g.size(); v++)
		if (g[u][v] != -INF) {
			if (!visited[v])
				dfs(v, g);
		}
	ans.push_back(u);
}

void topologicalSort(const vector< vector<int> >& g) {
	visited.resize(g.size());
	for (size_t i = 0; i < visited.size(); ++i)
		visited[i] = false;
	for (int v = 0; v < g.size(); ++v)
		if (!visited[v])
			dfs(v, g);
	reverse(ans.begin(), ans.end());
}

int main() {
	int n;
	cin >> n;
	vector< vector<int> > g(n, vector<int>(n));
	vector<int>cost(n);

	for (int i = 0; i < n; ++i)
		cin >> cost[i];

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			cin >> g[i][j];
			g[i][j] == 0 ? g[i][j] = -INF : g[i][j] = cost[i];
		}

	topologicalSort(g);

	//solve
	for (int i = 0; i < n; ++i)
		for (int k = i + 1; k < n; ++k)
			if (g[ans[i]][ans[k]] != -INF)
				for (int j = k + 1; j < n; ++j)
					if (g[ans[k]][ans[j]] != -INF)
						g[ans[i]][ans[j]] = max(g[ans[i]][ans[j]],
							g[ans[i]][ans[k]] + g[ans[k]][ans[j]]);

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			g[i][j] != -INF ? g[i][j] += cost[j] : g[i][j] = 0;

	for (auto& v : g)
		print(v);

	return 0;
}
