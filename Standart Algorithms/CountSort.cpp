#include <iostream>
#include <vector>

using namespace std;

void CountSort(vector<int>& arr, int M){
    vector<int> v(M + 1, 0);
    //v[i] = кол-во раз, когда i встречается в arr
    for(int j = 0; j < arr.size(); ++j){
        v[arr[j]]++;            
    }
    //v[i] - кол-во раз в arr встречаются числа <=i
    for(int i = 1; i < M + 1; ++i){
        v[i] = v[i] + v[i - 1];     
    }
    
    vector<int>res(arr.size());
    for(int j = arr.size() - 1; j >= 0; --j){
        res[v[arr[j]] - 1] = arr[j];
        v[arr[j]] = v[arr[j]] - 1;
    }
    arr.assign(res.begin(), res.end());
}

int main(int argc, char* argv[]) {  
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin>>n;
    vector<int>arr;
    arr.reserve(n);
    for(int i = 0; i < n; ++i){
        int t;
        cin>>t;
        arr.emplace_back(t);
    }

    CountSort(arr, 10);

    for(int i : arr){
        cout<<i<<' ';
    }
    cout<<'\n';
    
    return 0;
}