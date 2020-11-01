#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

size_t Find(size_t id, vector<int>& parent) {
    if (id != parent[id]){
        parent[id] = Find(parent[id], parent);
    }
    return parent[id];
}

void Union(size_t src, size_t dest, 
    vector<int>& parent, vector<int>& rank, int& maxr)  {

    size_t src_id = Find(src, parent);
    size_t dest_id = Find(dest, parent);
    if (src_id == dest_id){
        return;
    }
    parent[dest_id] = src_id;
    rank[src_id] += rank[dest_id];
    maxr = max(maxr, rank[src_id]);
    rank[dest_id] = 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;

    vector<int>parent(n);
    vector<int>rank(n);
    int maxr = 0;

    int ri;
    for(int i = 0; i < n; ++i){
        cin>>ri;
        parent[i] = i;
        rank[i] = ri;
        maxr = max(maxr, ri);
    }

    int dest, src;

    for(int i = 0; i < m; ++i){
        cin>>dest>>src;
        Union(--src, --dest, parent, rank, maxr);
        cout<<maxr<<'\n';
    }
    
	
	return 0;
}