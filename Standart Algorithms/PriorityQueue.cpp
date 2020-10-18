#include <iostream>
#include <string>
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


private:
    vector<T> A;
};

int main(int argc, char* argv[]) {  
    Heap<int, HeapType::MAX> heap;
    int n;
    cin >> n;
    string q;
    for(int i = 0; i < n; ++i){
        cin>>q;
        if (q[0] == 'I'){
            int x;
            cin >> x;
            heap.insert(move(x));
        }
        else {
            cout<<heap.extractMax()<<'\n';
        }
    }
    return 0;
}