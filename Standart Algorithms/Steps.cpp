#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int SumSteps(const vector<int>& s){
    size_t n = s.size();
    vector<int>d(n);
    d[0] = s[0];
    d[1] = max(d[0] + s[1], s[1]);    
    for(size_t i = 2; i < n; ++i){
        d[i] = max(d[i - 1] + s[i], d[i - 2] + s[i]);
    }

    return d[n - 1];
}


int main(int argc, char* argv[]) {  
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin>>n;
    int x;
    vector<int>s;
    s.reserve(n);
    for(int i = 0; i < n; ++i){
        cin>>x;
        s.emplace_back(x);
    }

    cout<<SumSteps(s)<<'\n';


    return 0;
}