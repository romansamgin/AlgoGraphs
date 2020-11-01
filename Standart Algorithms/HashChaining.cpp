#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

int hash_str(const string& s, int m){
    const int p = 1'000'000'007;
    const long long x = 263;
    long long hash = 0;
    long long xi = 1;   
    for(size_t i = 0; i < s.size(); ++i){
        int ascii = static_cast<int>(s[i]);
        hash += (ascii * xi) % p;
        xi = (xi * x) % p;
    }
    return (hash % p) % m;
}


int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int m, n;
    cin>>m;
    cin>>n;
    vector<deque<string>> table(m);
    string query;
    string s;
    for(int i = 0; i < n; ++i){
        cin>>query;
        if (query == "check"){
            int j;
            cin>>j;
            deque<string>& chain = table[j]; 
            if (chain.empty()){
                cout<<""<<'\n';
            }
            else {
                for(const string& s : chain){
                    cout<<s<<" ";
                }
                cout<<'\n';
            }
        }
        else {
            cin>>s;
            int id = hash_str(s, m);
            deque<string>& chain = table[id]; 
            auto it = find(chain.begin(), chain.end(), s);
            if (query == "add"){
                if (it == chain.end()) {
                    chain.push_front(s);
                }
            }
            else if(query == "del"){
                if (it != chain.end()){
                    chain.erase(it);
                }
            }
            else if (query == "find"){
                if (it != chain.end()){
                    cout<<"yes\n";
                }
                else {
                    cout<<"no\n";
                }
            }
        }
    }
    
	return 0;
}