//https://acmp.ru/index.asp?main=task&id_task=396

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int Partition(vector<int>& arr, int l, int r){
    swap(arr[l], arr[(l + r) / 2]);
    int x = arr[l];
    int i = l;
    int j = r;
    while (i <= j){
        while(arr[i] < x){
            i++;
        }
        while (arr[j] > x){
            j--;
        }
        if (i >= j){
            break;
        }
        swap(arr[i++], arr[j--]);
    }
    return j;
}


void QuickSort(vector<int>& arr, int l, int r){
    if (l < r){
        int m = Partition(arr, l ,r);
        QuickSort(arr, l, m);
        QuickSort(arr, m + 1, r);
    }
}


int lefts(const vector<int>& arr, int k){
    if (arr.back() <= k){
        return arr.size();
    }
    if (arr.front() > k){
        return 0;
    }
    int l = 0, r = arr.size() - 1;  
    while (l <= r) {
        int m = (l + r) / 2;
        if (k >= arr[m] && k < arr[m+1])
            return m + 1;
        else if (arr[m] > k)
            r = m - 1;
        else 
            l = m + 1;  
    }
    return 0;
}


int rights(const vector<int>& arr, int k){
    if (arr.back() < k){
        return arr.size();
    }
    if (arr.front() > k){
        return 0;
    }
    int l = 0, r = arr.size() - 1;  
    while (l <= r) {
        int m = (l + r) / 2;
        if (arr[m] < k && arr[m+1] >= k)
            return m + 1;
        else if (arr[m] >= k)
            r = m - 1;
        else 
            l = m + 1;  
    }
    return 0;
}



int main(int argc, char* argv[]) { 
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin>>n>>m;

    vector<int>begins;
    vector<int>ends;
    begins.reserve(n);
    ends.reserve(n);

    for(int i = 0; i < n; ++i){
        int a, b;
        cin>>a>>b;
        if (a > b){
            swap(a,b);
        }
        begins.emplace_back(a);
        ends.emplace_back(b);
    }

    QuickSort(begins, 0, n - 1);
    QuickSort(ends, 0, n - 1);
 
    for(int i = 0; i < m; ++i){
        int p;
        cin>>p;
        cout<<lefts(begins, p) - rights(ends,p) <<' ';
    }
    
    return 0;
}
