#include <iostream>
#include <vector>
#include <string>

using namespace std;

const long long p = 1'000'000'007;
const long long x = 263;

long long hash_str(const string& s){
    long long hash = 0;  
    size_t m = s.size();
    vector<long long>x_pow(m);
    int xi = 1;
	
    for(size_t i = 0; i < m; ++i){
        x_pow[i] = xi;
        xi = (xi * x) % p;
    } 
	
    for(size_t i = 0; i < s.size(); ++i){
        int ascii = static_cast<int>(s[i]);
        hash += (ascii * x_pow[m - 1 - i]) % p;
    }
	
    return hash % p;
}

vector<size_t> RabinKarp(const string& text, const string& pattern){
    vector<size_t> indxs;
    size_t n = text.size();
    size_t m = pattern.size();
    vector<long long>x_pow(m);
    int xi = 1;
	
    for(size_t i = 0; i < m; ++i){
        x_pow[i] = xi;
        xi = (xi * x) % p;
    }
	
    long long hash_w = hash_str(pattern);
    long long hash_s = hash_str(text.substr(0, pattern.size()));
	
    for(size_t i = 0; i < n - m + 1; ++i){
        if (hash_s == hash_w){
            indxs.push_back(i);
        }
        hash_s = ((hash_s - (int)text[i] * x_pow[m - 1]) * x + (int)text[i + m]) % p;
        hash_s = (hash_s + p) % p;
    }
	
    return indxs;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string pattern, text;
    getline(cin, pattern);
    getline(cin, text);
    auto t = RabinKarp(text, pattern);
    for(int i : t){
        cout<<i<<" ";
    }
    cout<<'\n';
	
    return 0;
}
