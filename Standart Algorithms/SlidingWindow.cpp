#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main(int argc, char* argv[]) {  
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin>>n;
    int x;
    vector<int>a;
    a.reserve(n);
    for(int i = 0; i < n; ++i){ 
        cin>>x;
        a.emplace_back(x);
    }
    cin>>m;
    deque<int> q;
    for(int i = 0; i < m; ++i){ 
        int added = a[i];
        while (!q.empty() && q.back() < added){
            q.pop_back();
        }
        q.push_back (added);
    }
    cout<<q.front()<<' ';
    for(int i = m; i < n; ++i){ 
        int remove = -1;
        if (a[i - m] == q.front()){
            remove = q.front();
        }
        if (!q.empty() && q.front() == remove){
            q.pop_front();
        }
        int added = a[i];
        while (!q.empty() && q.back() < added){
            q.pop_back();
        }
        q.push_back (added);
        cout<<q.front()<<' ';        
    }

    return 0;
}