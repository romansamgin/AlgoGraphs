#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int EditDistBU(const string& s1, const string& s2){
    size_t n = s1.size();
    size_t m = s2.size();
    vector<vector<int>>d(n + 1, vector<int>(m + 1));
    for(size_t i = 0; i < n + 1; ++i){
        d[i][0] = i;
    }
    for(size_t j = 0; j < m + 1; ++j){
        d[0][j] = j;
    }
    for(size_t i = 1; i < n + 1; ++i){
        for(size_t j = 1; j < m + 1; ++j){
            int c = (s1[i-1] == s2[j-1]) ? 0 : 1;
            d[i][j] = min(d[i - 1][j] + 1,
                        min(d[i][j - 1] + 1,
                        d[i - 1][j - 1] + c)
                        );
        }
    }
    return d[n][m];

}

int main(int argc, char* argv[]) {  
    string s1;
    string s2;
    cin>>s1;
    cin>>s2;
    cout<<EditDistBU(s1,s2)<<'\n';

    return 0;
}