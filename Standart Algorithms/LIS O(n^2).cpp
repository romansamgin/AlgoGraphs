#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int LIS(const vector<int>& v){
    vector<int>d(v.size());
    for(int i = 0; i < v.size(); ++i){
        d[i] = 1;
        for(int j = 0; j <= i - 1; ++j){
            if (v[j] < v[i]){
                d[i] = max(d[i], d[j] + 1);
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < v.size(); ++i){
        ans = max(ans, d[i]);
    }

    return ans;
}

int main(int argc, char* argv[]) {  
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin>>n;
    vector<int>v;
    v.reserve(n);
    int a;
    for(int i = 0; i < n; ++i){
        cin>>a;
        v.emplace_back(a);
    }
    cout<<LIS(v)<<'\n';

    return 0;
}