#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
	int x, y, w;

	Edge() = default;

	Edge(int _x, int _y, int _w) : x(x_), y(y_), w(w_)	
	{ 
	}

	void print() {	
		cout << x << "-" << y << "[" << w << "]"<<"\t ";
	}

	bool operator<(const Edge& other) { return w <= other.w; }
};

struct gsort {
	bool operator() (const Edge& i, const Edge& j) { return (i.w <= j.w); }
} e_sort;


int main() {
	int n, m;
	cin >> n >> m;

	vector<Edge>g{};

	for (int i = 0; i < m; ++i) {
		int x, y, w;
		cin >> x >> y >> w;
		g.push_back(Edge(--x, --y, w));
	}

	sort(g.begin(),g.end(), e_sort);

	vector <int> comp(n);
	for (int i = 0; i < n; ++i)
		comp[i] = i;


	//solve ans min

	int ans = 0;
	vector<Edge>g0{};
	for (auto& edge : g)
	{
		int weight = edge.w;
		int start = edge.x;
		int end = edge.y;
		if (comp[start] != comp[end])
		{
			ans += weight;
			int a = comp[start];
			int b = comp[end];
			g0.push_back(Edge(start, end, weight));
			for (int i = 0; i < n; ++i)
				if (comp[i] == b)
					comp[i] = a;		
		}
	}

	//solve
	
	vector<int>mins{};
	mins.resize(0);

	for (size_t i = 0; i < g.size(); ++i) {
		vector<Edge>v{};
		for (auto u : g)
			v.push_back(u);
		v.erase(v.begin() + i);

		int ans2 = 0;
		for (int i = 0; i < n; ++i)
			comp[i] = i;

		for (auto& edge : v)	{
			int weight = edge.w;
			int start = edge.x;
			int end = edge.y;
			if (comp[start] != comp[end])	{
				ans2 += weight;
				int a = comp[start];
				int b = comp[end];
				for (int i = 0; i < n; ++i)
					if (comp[i] == b)
						comp[i] = a;
			}
		}

		if (ans2 > ans)	{
			bool f = false;
			for (auto i : mins)
				if (ans2 == i)
					f = true;
			if (!f)
				mins.push_back(ans2);
		}				
	}
	sort(mins.begin(), mins.end());
	cout << mins[0] << endl;
	return 0;
}
