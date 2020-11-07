#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

//Невозр
vector<int> LIS(const vector<int>& a){
    size_t n = a.size();
    vector<int>d(n + 1, -INF);
    vector<int>pos(n + 1);
    vector<int>prev(n);
    size_t length = 0;
    pos[0] = -1;
    d[0] = INF;
    for(size_t i = 0; i < n; ++i){
        auto it = upper_bound(d.begin(), d.end(), a[i], 
            [](int i, int j) {
                return i > j;
            }
        );
        size_t j = static_cast<size_t>(it - d.begin());
        if (d[j - 1] >= a[i] && d[j] < a[i]){
            d[j] = a[i];
            pos[j] = i;
            prev[i] = pos[j - 1];
            length = max(length, j);
        }
    }

    vector<int>answer{};
    answer.reserve(length);
    int p = pos[length];
    while (p != -1){
        answer.emplace_back(p + 1);
        p = prev[p];
    }
    reverse(answer.begin(), answer.end());
    return answer;
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
    auto res = LIS(v);
    cout<<res.size()<<'\n';
    for(int i : res ){
        cout<<i<<" ";
    }
    cout<<'\n';

    return 0;
}
