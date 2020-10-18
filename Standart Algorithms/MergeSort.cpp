#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;


long long Merge(vector<int>& arr, 
                const vector<int>& left, 
                const vector<int>& right)
{
    int i = 0, j = 0; 
    long long count = 0;
    while (i < left.size() || j < right.size()){
        if (i == left.size()){
            arr[i + j] = right[j];
            j++;
        } 
        else if (j == right.size()){
            arr[i + j] = left[i];
            i++;
        }
        else if (left[i] <= right[j]){
            arr[i + j] = left[i];
            i++;
        }
        else{
            arr[i + j] = right[j];
            count += left.size() - i;
            j++;
        }
    }
    return count;
}



long long MergeSort(vector<int>& arr){
    if (arr.size() < 2){
        return 0;
    }
    int mid = (arr.size() + 1) / 2;
    vector<int> left(arr.begin(), arr.begin() + mid);
    vector<int> right(arr.begin() + mid, arr.end());
    return MergeSort(left) + MergeSort(right) + Merge(arr, left, right);
}

int main(int argc, char* argv[]) {  
    std::ios::sync_with_stdio(false);
    int n;
    cin>>n;
    vector<int> arr;
    arr.reserve(n);

    int x;
    for(int i = 0; i < n; ++i){ 
        cin>>x;
        arr.emplace_back(x);
    }  
    
    cout<<MergeSort(arr)<<'\n';
    return 0;
}