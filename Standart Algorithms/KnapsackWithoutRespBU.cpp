#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int KnapsackWithoutRespBU(int W, vector<int>& ws){
    size_t n = ws.size();
    vector<vector<int>>d(W + 1, vector<int>(n + 1, 0));
    for(int i = 1; i < n + 1; ++i){
        for(int w = 0; w < W + 1; ++w){
            d[w][i] = d[w][i - 1];
            if (ws[i - 1] <= w){
                d[w][i] = max(d[w][i], d[w - ws[i - 1]][i - 1] + ws[i - 1]);
            }
        }
    }
    return d[W][n];
}

int main(int argc, char* argv[]) {  
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int W, n;
    cin>>W>>n;
    vector<int>ws;
    ws.reserve(n);
    int wi;
    for(int i = 0; i < n; ++i){
        cin>>wi;
        ws.emplace_back(wi);
    }
    cout<<KnapsackWithoutRespBU(W, ws)<<'\n';
    

    return 0;
}