#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

string HuffmanDecode( 
    const unordered_map<string, string>& mp, 
    const string& code
    ){
    string cur_code = "";
    string result = "";
    for(char ch : code){
        cur_code += ch;
        if (mp.count(cur_code) == 1){
            result += mp.at(cur_code);
            cur_code = "";
        }
    }
    return result;
}

int main(int argc, char* argv[]) {  
    int k, l;
    cin>>k>>l;
    unordered_map<string, string> mp;
    cin.ignore();
    for(int i = 0; i < k; ++i){
        string str;
        getline(cin, str);
        size_t pos = str.find(':');
        string ch = str.substr(0, pos);
        string code = str.substr(pos + 2, str.size() - 1);
        mp[code] = ch;
    }
    string code;
    getline(cin, code);
    cout<<HuffmanDecode(mp, code)<<'\n';
    return 0;
}