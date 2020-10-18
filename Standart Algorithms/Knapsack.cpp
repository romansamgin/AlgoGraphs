#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Content{
    int value, weight;

    Content(int x, int y) : value(x), weight(y)
    {}
};


double Knapsack(vector<Content>& ps, int W){
    sort(ps.begin(), ps.end(), 
        [](const Content& lhs, const Content& rhs) {
            return  static_cast<int64_t>(lhs.weight) * rhs.value <
                    static_cast<int64_t>(rhs.weight) * lhs.value;
        }
    );

    double res = 0;
    int w_cur = 0;

    for(size_t i = 0; i < ps.size() && w_cur < W; ++i){
        auto& item = ps[i];
        if (w_cur + item.weight > W){
            double d = w_cur + item.weight - W;
            double prop = d / item.weight;
            res += item.value * (1 - prop);
            break;
        }       
        res += item.value;
        w_cur += item.weight;
    }  
    return res;
}

int main(int argc, char* argv[]){
    int n;
    int W;
    cin >> n >> W;
    vector<Content> ps;
    ps.reserve(n);
    for(int i = 0; i < n; ++i){
        int x,y;
        cin>>x>>y;
        ps.emplace_back(Content(x,y));
    }

    cout << fixed << setprecision(3) << 
        Knapsack(ps, W) << endl; 
    return 0;
}