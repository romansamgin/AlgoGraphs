#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;




int TreeHeight(const vector<vector<int>>& tr, int v){
    int height = 1;
    for(int child : tr[v]){
        height = max(height, 1 + TreeHeight(tr, child));
    }
    return height;
}

int main(int argc, char* argv[]) {  
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n = 0;
    cin>>n;
    vector<int>v;
    int x = 0;
    v.reserve(n);
    for(int i = 0;  i < n; ++i){
        cin>>x;
        v.emplace_back(x);
    }
    vector<vector<int>> tr(v.size());
    int root = 0;
    for(size_t i = 0; i < v.size(); ++i){
        if (v[i] == -1){
            root = i;
        }
        else {
            tr[v[i]].push_back(i);
        }      
    }
    cout<< TreeHeight(tr, root)<<'\n';
    
    return 0;
}