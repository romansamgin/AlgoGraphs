#include <iostream>
#include <vector>

using namespace std;

enum class HeapType {
    MAX,
    MIN
};

template<typename T, HeapType type>
class Heap {
public:
    void siftDown(int i) {
        while(2 * i + 1 < A.size()){
            size_t l = 2 * i + 1;
            size_t r = 2 * i + 2;
            size_t j;
            bool valid_tree = false;
            switch(type)    {
                case HeapType::MAX : {
                    j = r < A.size() && A[r] > A[l] ? r : l;
                    if (A[i] >= A[j]){
                        valid_tree = true;
                    }
                    break;
                }
                case HeapType::MIN : {
                    j = r < A.size() && A[r] < A[l] ? r : l;
                    if (A[i] <= A[j]){
                        valid_tree = true;
                    }
                    break;
                }
                default:
                    break;                   
            } 
            if (valid_tree){
                break;
            }          
            swap(A[i], A[j]);
            i = j;
        }
    }


    void siftUp(int i) {
        switch(type) {
            case HeapType::MAX: {
                while (A[i] > A[(i - 1)/2]) {
                    swap(A[i], A[(i-1)/2]);
                    i = (i - 1) / 2;
                } 
                break;
            }
            case HeapType::MIN: {
                while (A[i] < A[(i-1)/2]) {
                    swap(A[i], A[(i-1)/2]);
                    i = (i - 1) / 2;
                }  
                break;
            }
            default:
                break;
        }                  
    }

    void insert(T&& value) {
        A.push_back(move(value));
        siftUp(A.size() - 1);        
    }

    //for HeapType::MAX
    T extractMax() {
        T max = move(A.front());
        A.front() = A.back();
        A.pop_back();
        siftDown(0);
        return move(max);
    }

    //for HeapType::MIN
    T extractMin() {
        return extractMax();
    }

    T top() const {
        return A.front();
    }   

    size_t size() const {
        return A.size();
    }

private:
    vector<T> A;
};

int main(int argc, char* argv[]) {  
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    Heap<int, HeapType::MIN>pq;
    size_t size, n;
    cin>>size>>n;
    if (n == 0) {
        return 0;
    }
    int arrival, duration;
    cin>>arrival>>duration;
    int prev_start = arrival;
    int prev_end = arrival + duration;
    cout<<prev_start<<'\n';
    pq.insert(move(prev_end));    
    for(size_t i = 1; i < n; ++i){
        cin>>arrival>>duration;
        if (arrival < pq.top() && pq.size() == size){
            cout<<-1<<'\n';
        }
        else {
            int cur_start;
            int cur_end;
            if (arrival <= prev_end){
                cur_start = prev_end;
            }
            else {
                cur_start = arrival;
            }
            cur_end = cur_start + duration;
            cout<<cur_start<<'\n';
            if (pq.size() == size) {
                pq.extractMin();
            }            
            pq.insert(move(cur_end));
            prev_start = cur_start;
            prev_end = cur_end;
        }
    }

    return 0;
}