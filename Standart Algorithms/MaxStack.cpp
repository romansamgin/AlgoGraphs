#include <iostream>
#include <stack>


using namespace std;

struct Node {
    int max;
    int value;
};

int main(int argc, char* argv[]) {  
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q;
    cin>>q;
    string query;
    stack<int> st;
    stack<int> maxs;
    int max = -1;

    for(int i = 0; i < q; ++i){
        cin>>query;
        if (query[1] == 'u'){
            int n;
            cin>>n;
            st.push(n);
            if (n >= max){
                st.push(n);
                max = n;
            }
            else {
                maxs.push(maxs.top());
            }
        }
        else if (query == "pop"){
            st.pop();
            maxs.pop();
            max = maxs.top();
        }
        else if (query == "max"){
            cout<<maxs.top()<<'\n';
        }
    }
    return 0;
}