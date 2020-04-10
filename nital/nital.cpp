#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;


struct Edge
{
    char begin;
    char end;

    Edge() { this->begin = ' '; this->end = ' '; }

    Edge(const char& begin,const char& end) {
        this->begin = begin;
        this->end = end;
    }

    void operator = (const Edge& edge) {
        this->begin = edge.begin;
        this->end = edge.end;
    }

    bool operator == (const Edge& edge) {
        return ((this->begin == edge.begin) && (this->end == edge.end));
    }
};

void vectorReverse(vector <int>& v) {
    for (size_t i = 0; i < (v.size() / 2); ++i)
        swap(v[i], v[v.size() - 1 - i]);
}

void pushChar(vector<char>& vector, string word)    {
    for (size_t k = 0; k < word.length(); ++k)  {
        char ch = word[k];
        bool flag = false;
        for (size_t j = 0; j < vector.size(); ++j)
            if (ch == vector[j])    {
                flag = true;
                break;
            }
        if (!flag)
            vector.push_back(ch);
    }
}

void pushEdges(vector<Edge>& edges, const vector<string>& words)   {
    for (size_t i = 1; i < words.size() - 1; ++i)   {
        string w1 = words[i];
        string w2 = words[i + 1];
        int length = min(words[i].size(), words[i + 1].size());
        int j = 0;
        while (w1[j] == w2[j])
            j++;
        if (((w1[j] >= 'A') && (w1[j] <= 'Z'))
            && ((w2[j] >= 'A') && (w2[j] <= 'Z')))  {
            Edge edge(w1[j], w2[j]);
            bool flag = false;
            for (size_t k = 0; k < edges.size(); k++)
                if (edge == edges[k])   {
                    flag = true;
                    break;
                }
            if (!flag)
                edges.push_back(edge);
        }
    }
}

void matrixFilling(vector <vector <int> >& g, const vector<char>& alph,
    const vector<Edge>& edges)  {
    for (size_t i = 0; i < edges.size(); ++i)   {
        Edge edge = edges[i];
        char begin = edge.begin;
        char end = edge.end;
        int istart(0), iend(0);
        for (size_t j = 0; j < alph.size(); ++j)    {
            if (begin == alph[j])
                istart = j;
            if (end == alph[j])
                iend = j;
        }
        g[istart][iend] = 1;
    }
}

vector<string> color;

bool dfsCycle(int v, const vector <vector <int> >& g)  {
    color[v] = "grey";
    for (size_t u = 0; u < g.size(); ++u)   {
        if ((g[v][u] == 1)) {
            if (color[u] == "white")
                dfsCycle(u, g);
            if (color[u] == "grey")
                return false;
        }
    }
    color[v] = "black";
}

vector<int> ans{};    
vector<int> visited{};

void dfs(int u, const vector <vector <int> >& g) {
    visited[u] = true;
    for (size_t v = 0; v < g.size(); ++v)   {
        if (g[u][v] == 1)   {
            if (!visited[v])   
                dfs(v, g);
        }
    }
    ans.push_back(u);
}


void topologicalSort(const vector <vector <int> >& g)   {
    for (size_t i = 0; i < visited.size(); ++i)
        visited[i] = false;
    for (size_t v = 0; v < g[0].size(); ++v)    {
        if (!visited[v])
            dfs(v, g);
    }
    vectorReverse(ans);
}


int main()  {
    int count;
    cin >> count;
    vector<char> alph{};
    vector<string> words{};
    vector<int> vertex{};
    for (int i = -1; i < count; ++i)    {
        string word;
        getline(cin, word);
        pushChar(alph, word);
        words.push_back(word);
    }

    for (size_t i = 0; i < alph.size(); ++i)
        vertex.push_back(i);

    vector<Edge> edges{};
    pushEdges(edges, words);

    vector < vector<int> > g(vertex.size(), vector<int>(vertex.size()));
    matrixFilling(g, alph, edges);

    color.resize(vertex.size());
    for (size_t i = 0; i < color.size(); i++)
        color[i] = "white";

    visited.resize(vertex.size());
    for (size_t i = 0; i < visited.size(); i++)
        visited[i] = false;

    topologicalSort(g);

    string output = "";
    if (dfsCycle(0, g) == false)
        output += '-';
    else
        for (size_t i = 0; i < ans.size(); ++i)
            output += alph[ans[i]];

    cout << output << endl;
    return 0;
}
