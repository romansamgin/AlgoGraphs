#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct CPU {
    int id;
    long release_time;
};

int main(int argc, char* argv[]) {  
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    auto comp = [](const CPU& lhs, const CPU& rhs) {
        if (lhs.release_time == rhs.release_time){
            return lhs.id > rhs.id;
        }
        return lhs.release_time > rhs.release_time;
    };
    priority_queue<CPU, vector<CPU>, decltype(comp)>q(comp);
    for(int i = 0; i < n; ++i){
        q.push({i, 0});
    }

    long t; 
    for(int i = 0; i < m; ++i){
        cin>>t;
        CPU p = q.top();
        q.pop();
        cout<<p.id<<' '<<p.release_time<<'\n';
        p.release_time += t;
        q.push(p);
    }
    

    return 0;
}