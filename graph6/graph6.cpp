#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int INF = 1000000000;

//МОЖНО БЫСТРЕЕ
void get_graph(
	vector<vector<pair<int, int>>>& graph, 
	vector<int>& a, int& sum_ei
	) {
	
	//n + 1 - ÿ  âåðøèíà - ýòî áàøíÿ, n - ôèêòèâíàÿ âåðøèíà, pair = ïðîïóñêíàÿ ñïîñîáíîñòü, ïîòîê
	for (size_t i = 0; i < graph.size(); ++i) {
		for (size_t j = 0; j < graph.size(); ++j) {
			graph[i][j] = make_pair(0, 0);
		}		
	}

	int e_i, to_tower, ai;				//Ãåíäàëüô
	cin >> e_i >> to_tower >> ai;
	a[0] = ai;
	for (size_t i = 1; i < graph.size() - 2; ++i) {		//Ìàãè
		cin >> e_i >> to_tower >> ai;
		sum_ei += e_i;
		graph[i][graph.size() - 2] = make_pair(e_i, 0);			//ïî ôèêòèâíîé âåðøèíå
		if (to_tower) {
			graph[i][graph.size() - 2 + 1] = make_pair(INF, 0);		//ïî áàøíå
		}
		a[i] = ai;
	}
	
	int to, bandwidth;
	for (size_t i = 0; i < graph.size() - 2; ++i) {
		for (int j = 0; j < a[i]; ++j) {
			cin >> to >> bandwidth;
			graph[i][to] = make_pair(bandwidth, 0);
		}
	}
}

int findPath(
	vector<vector<pair<int, int>>>& graph, 
	vector<bool>& visited, 
	int u, int t, int f) {
	if (u == t) {
	    	return f;
	}	
	visited[u] = true;
	for (size_t v = 0; v < visited.size(); v++) {
		if (!visited[v] && graph[u][v].first > 0) {
			int df = findPath(graph, visited, v, t, min(f, graph[u][v].first));
			if (df > 0) {
				graph[u][v].first -= df;
				graph[u][v].second += df;
				graph[v][u].first += df;
				return df;
			}
		}
	}
	
	return 0;
}


int maxFlow(vector<vector<pair<int, int>>>& graph, int s, int t) {

	for (int flow = 0; ;) {
		vector<bool>visited(graph.size(), false);
		int df = findPath(graph, visited, s, t, INF);
		if (df == 0) {
			return flow;
		}			
		flow += df;
	}
}


int main() {
	int n;
	cin >> n;
	vector<vector<pair<int, int>>>graph(n + 2,(vector<pair<int,int>>(n + 2)));	
	vector<int>a(n);
	int sum_ei = 0;
	get_graph(graph, a, sum_ei);
	
	if (maxFlow(graph, 0, n) != sum_ei) {
		cout << -1 << '\n';
	}
	else {	
		cout << maxFlow(graph, 0, n + 1) << '\n';
	}
	
	return 0;
}
