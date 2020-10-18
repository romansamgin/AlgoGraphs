#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Info {
    int counter;
    int prev;
};

vector<int> MinOperations(int n){
    vector<Info>d(n + 1);
    for(auto& i : d){
        i.counter = INF;
    }

    vector<int>p;
    d[0].counter = 0;
    d[1].counter = 0;

    for(int i = 1; i <= n; ++i){
        int add = i + 1;
        int mul2 = i * 2;
        int mul3 = i * 3;
        if (add <= n && d[add].counter > d[i].counter + 1){
            d[add].counter = d[i].counter + 1;
            d[add].prev = i;
        }
        if (mul2 <= n && d[mul2].counter > d[i].counter + 1){
            d[mul2].counter = d[i].counter + 1;
            d[mul2].prev = i;
        }
        if (mul3 <= n && d[mul3].counter > d[i].counter + 1){
            d[mul3].counter = d[i].counter + 1;
            d[mul3].prev = i;
        }      
    }

    p.push_back(n);
    int prev = d[n].prev;
    while (p.size() != d[n].counter + 1){
        p.push_back(prev);
        prev = d[prev].prev;
    }
    reverse(p.begin(), p.end());
    return p;
}

int main(int argc, char* argv[]) {  
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin>>n;
    vector<int> result = MinOperations(n);
    cout<<result.size() - 1<<'\n';
    for(auto& i : result){
        cout<<i<<' ';
    }
    cout<<'\n';

    return 0;
}