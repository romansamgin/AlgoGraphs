#include <iostream>
#include <vector>
#include <deque>


using namespace std;


struct Edge {
    unsigned short x, y;

    Edge() { this->x = -1;   this->y = -1; }
        
    Edge(const int& x, const int& y){
        this->x = x;
        this->y = y;
    }

    ~Edge() {}

    bool operator == (const Edge& edge) {
        return ((this->x == edge.x) && (this->y == edge.y))
            || ((this->x == edge.y) && (this->y == edge.x));
    }
};


void pushEdges(vector<Edge>& maps, Edge edge, int* ri, int i, int k)   {
    for (size_t i = 0; (i < maps.size()) && (edge == maps[i]); ++i)
        return;
    maps.push_back(edge);
    ri[edge.x * (k + 1) + (i + 1) % (k + 1)]++;
    ri[edge.y * (k + 1) + (i + 1) % (k + 1)]++;
}


void matrixFilling(vector <vector < Edge >>& maps, int k, int& m, int* ri)   {
    for (int i = 0; i < k; ++i) {
        int j;                     
        cin >> j;
        if (j == 0)
            maps[i].clear();
        for (int j0 = 0; j0 < j; ++j0)  {
            int x, y;
            cin >> x >> y;   
            Edge edge(--x, --y);
            pushEdges(maps[i], edge, ri, i, k);   
            m++;
        }
    }
}



deque <int> deq{};

int bfs(int** g, int* rv, int source, int destination,
    int nkPlusM, int k)   {

    vector <unsigned short> d(nkPlusM);
    //distance from source to i
    for (size_t i = 0; i < d.size(); ++i)
        d[i] = 65535;
    d[source] = 0;
    deq.clear();
    deq.push_front(source);
    bool flag = false;
    while (!deq.empty() && (flag == false))    {
        int u = deq.at(0);
        deq.pop_front();
        for (int i = 0; i < rv[u]; ++i) {
            int v = g[u][i];
            //weight edge 1
            if ((v - u > 0) && (v - u < k + 1)) {
                int d0 = d[u] + 1;
                if (d0 < d[v])  {
                    d[v] = d0;
                    deq.push_back(v);
                }
            }
            //weight edge 0
            else    {
                int d0 = d[u];
                if (d0 < d[v])  {
                    d[v] = d0;
                    deq.push_front(v);
                }
            }
            if (g[u][i] == destination) {
                break;
                flag = true;
            }        
        }  
    }
  
    if (d[destination] == 65535)
        return -1;
    else
        return d[destination];
}


int main()
{
    int n, k;
    cin >> n >> k;

    vector <vector <Edge>> maps(k);

    //count of all roads 
    int m = 0;

    //how many numbers in each line (for new[])
    int* ri = new int[n * k + n];
    for (int i = 0; i < n * k + n; ++i)
        ri[i] = 1;

    //how many numbers in each line at the moment
    int* rv = new int[n * k + n];
    for (int i = 0; i < n * k + n; ++i)
        rv[i] = 0;

    matrixFilling(maps, k, m, ri);

    //adjacency list
    int** g = new int*[n * k + n];

    //all edges of weight 1
    for (int i = 0; i < n * k + n; i += k + 1)  {
        g[i] = new int[k];
        ri[i] = k;     
        for (int j = 0; j < k; ++j)
            g[i][j] =i + 1 + j;
        rv[i] = k;

        //some edges of weight 0
        for (int j = i + 1; ((j < i + 1 + k) && (j < n * k + n)); ++j) {
            g[j] = new int[ri[j]];
            g[j][rv[j]] = i;
            rv[j]++;
        }
    }

    delete[] ri;

    //remaining edges of weight 0
    for (size_t i = 0; i < maps.size(); ++i)    {
        for (size_t j = 0; j < maps[i].size(); ++j) {
            int valueVert = maps[i][j].x * (k + 1) + (i + 1);
            int valueHor = maps[i][j].y * (k + 1) + (i + 1);
            g[valueVert][rv[valueVert]] = valueHor;
            rv[valueVert]++;
            g[valueHor][rv[valueHor]] = valueVert;
            rv[valueHor]++;
        }    
    }
 
    cout << bfs(g, rv, 0, (n * k + n) - (k + 1), n * k + m, k) << endl;
    return 0;
}
