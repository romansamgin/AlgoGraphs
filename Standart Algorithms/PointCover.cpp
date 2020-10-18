#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Segment{
    int x_, y_;

    Segment(int x, int y) : x_(x), y_(y)
    {}
};


vector<int> PointCover(vector<Segment>& ps){
    sort(ps.begin(), ps.end(), 
        [](const Segment& lhs, const Segment& rhs) {
                return lhs.y_ <= rhs.y_;
        }
    );

    vector<int> points ;
    int i = 0;
    size_t n = ps.size();
    while (i < n){
        int point = ps[i].y_;
        points.push_back(point);
        i++;
        while (i < n && ps[i].x_ <= point && point <= ps[i].y_) {
            i++;
        }
    }    
    return points;
}

int main(int argc, char* argv[]){
    int n;
    cin>>n;
    vector<Segment> ps;
    ps.reserve(n);
    for(int i = 0; i < n; ++i){
        int x,y;
        cin>>x>>y;
        ps.emplace_back(Segment(x,y));
    }

    const auto result = PointCover(ps);
    cout<<result.size()<<'\n';

    for(auto i : result){
        cout<<i<<" ";
    }

    cout<<'\n';
    return 0;
}