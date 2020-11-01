#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Heap {
public:
    Heap(size_t n){
        A.reserve(n);
    }

    void push_back(int x){
        A.emplace_back(x);
    }

    void BuildHeap(){
        vector<pair<int,int>> d;
        for(int i = A.size() / 2; i >= 0; --i){
            int z = i;
            while (2 * z + 1 < A.size()) {
                size_t l = 2 * z + 1;
                size_t r = 2 * z + 2;
                size_t j;
                j = r < A.size() && A[r] < A[l] ? r : l;
                if (A[z] <= A[j]){
                     break;
                }             
                swap(A[z], A[j]);
                d.push_back({z, j});
                z = j;
            }
        }
        cout<<d.size()<<'\n';
        for(auto p: d){
            cout<<p.first<<" "<<p.second<<'\n';
        }
    }

private:
    vector<int> A;
};

int main(int argc, char* argv[]) {  
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin>>n;
    Heap heap(n);
    int x;
    for(int i = 0; i < n; ++i){
       cin>>x;
       heap.push_back(move(x));
    }
    heap.BuildHeap();

    return 0;
}