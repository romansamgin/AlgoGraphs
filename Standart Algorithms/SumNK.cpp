#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


int main(int argc, char* argv[]){
    int n;
    cin >> n;
    vector<int>v;
    v.reserve(int(sqrt(2.*n+0.25)-0.5));
    int i = 1;
    while(2 * i < n) {
        n -= i;
        v.emplace_back(i);
        i++;
    }
    v.emplace_back(n);
    cout<<v.size()<<'\n';
    for(auto i : v){
        cout<<i<<' ';
    }
    cout<<endl;
    return 0;
}
