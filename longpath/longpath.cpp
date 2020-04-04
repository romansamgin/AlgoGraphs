#include <iostream>
#include <vector>
#include <algorithm> 

//NOT FULL

#define INF 2147483647  
#define MAXN 1000

int g[MAXN][MAXN];
int cost[MAXN];
int n;

using namespace std;


template <typename T>
void print(vector<T> v) {

	for (size_t i = 0; i < v.size(); ++i)
		cout << v[i] << " ";
	cout << endl;
}

void printG(int g[MAXN][MAXN], const int& n) {

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			cout << g[i][j] << " ";
		cout << endl;
	}
}

void vectorReverse(vector <int>& v)	{

	for (size_t i = 0; i < (v.size() / 2); i++)
		swap(v[i], v[v.size() - 1 - i]);
}

vector<int> ans{};    
vector<int> visited{};

void dfs(const int& u, int g[MAXN][MAXN], const int& n) {

	visited[u] = true;
	for (int v = 0; v < n; v++)
		if (g[u][v] > 0)	{
			if (!visited[v])
				dfs(v, g, n);
		}
	ans.push_back(u);
}

void topologicalSort(int g[MAXN][MAXN], int n){

	for (size_t i = 0; i < visited.size(); ++i)
		visited[i] = false;
	for (int v = 0; v < n; ++v)
		if (!visited[v])
			dfs(v, g, n);
	vectorReverse(ans);
}

//int d0[MAXN];
//vector<int> q{};
//
//void bfs(int g[MAXN][MAXN], const int& n, const int& s, int cost[MAXN]) {
//
//	for (int i = 0; i < n; ++i)
//		d0[i] = INF;
//	d0[s] = -cost[s];
//	q.clear();
//	q.push_back(s);
//	while (!q.empty()) {
//		int u = q.at(0);
//		q.pop_back();
//		for (int v = 0; v < n; ++v)
//			if (g[u][v] > 0) {
//				if (d0[v] == INF) {
//					d0[v] = d0[u] - cost[v];
//					q.push_back(v);
//				}
//			}
//	}
//	for (int i = 0; i < n; ++i)
//		cout << d0[i] << " ";
//}



int main() {

	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> cost[i];
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> g[i][j];
			if ((g[i][j] == 0) && (i != j))
				g[i][j] = -INF;
			else
				g[i][j] *= cost[j];
		}
	}

	visited.resize(n);
	topologicalSort(g, n);
	
	//solve
	for (int i0 = 0; i0 < n; ++i0)	{
		int i = ans[i0];
		for (int k0 = i0 + 1; k0 < n; ++k0)	{
			int k = ans[k0];
			if ((g[i][k] > -INF))	{
				for (int j0 = k0 + 1; j0 < n; ++j0)	{
					int j = ans[j0];
					if (g[k][j] > -INF)
						g[i][j] = max(g[i][j], g[i][k] + g[k][j]);
				}
			}
		}
	}
		
	
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (g[i][j] == -INF || i == j)
				g[i][j] = 0;
			else
				g[i][j] += cost[i];
		
	printG(g, n);
	
	return 0;
}