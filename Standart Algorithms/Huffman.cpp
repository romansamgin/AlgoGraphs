#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <unordered_map>
#include <algorithm>


using namespace std;


string Huffman(const string& s){
    deque<pair<string, int>> pqueue;
    unordered_map<char, int> counter;
    unordered_map<char, string> scodes;
    for(char ch : s){
        counter[ch]++;
    } 
    if (counter.size() == 1){
        cout<<1<<" "<<s.size()<<endl;
        cout<<s[0]<<": "<<0<<endl;
        for(char ch : s){
            cout<<0;
        }
        return "";
    }

    for(auto p:counter){    
        char ch = p.first;
        int count = p.second;
        pqueue.push_back({string(1, ch), count});
    }
    auto comp = [] (const pair<string, int>& p1, const pair<string, int>& p2) {
        return p1.second < p2.second;
    };

    vector<pair<string,char>> l;
    while (pqueue.size() > 1){
        sort(pqueue.begin(), pqueue.end(), comp);  
        string sun1_s = pqueue.front().first;
        int sun1_w = pqueue.front().second;
        l.push_back({sun1_s,'0'});
        pqueue.pop_front();

        string sun2_s = pqueue.front().first;
        int sun2_w = pqueue.front().second;
        l.push_back({sun2_s,'1'});
        pqueue.pop_front();
        

        pair<string, int> parent = {sun2_s + sun1_s, sun1_w + sun2_w};
        pqueue.push_back(parent);
    }


    reverse(l.begin(), l.end());

    for(auto p : l){
        string str = p.first;
        char bit = p.second;
        for(auto symbol : str){
            scodes[symbol] += bit;
        }
    }
    string result;
    for(auto ch : s){
        result += scodes[ch];
    }
    cout<<scodes.size()<<" "<<result.size()<<endl;
    for(auto p : scodes){        
        cout<<p.first<<": "<<p.second<<endl;
    }

    return result;
}


int main(int argc, char* argv[]) {  
    string input;
    getline(cin, input);
    cout<< Huffman(input)<<'\n';


    return 0;
}
