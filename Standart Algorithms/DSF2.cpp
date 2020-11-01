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
    vector<int>& parent)  {

    size_t src_id = Find(src, parent);
    size_t dest_id = Find(dest, parent);
    if (src_id == dest_id){
        return;
    }
    parent[dest_id] = src_id;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, e, d;
    cin >> n >> e >> d;

    vector<int>parent(n + 1);
    
    for(int i = 1; i <= n; ++i){
        parent[i] = i;
    }

    int i, j;
    for(int z = 0; z < e; ++z){
        cin>>i>>j;
        Union(i, j, parent);
    }


    for(int z = 0; z < d; ++z){
        cin>>i>>j;
        if (Find(i, parent) == Find(j, parent)){
            cout<<0<<'\n';
            return 0;
        }
    }
    cout<<1<<'\n';
	
	return 0;
}