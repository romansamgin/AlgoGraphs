#include <iostream>
#include <string>
#include <stack>
#include <set>

using namespace std;


struct CharInfo {
    char ch;
    size_t indx;
};


//индексация с единицы 0 -> 1
int CheckBrackets(const string& s, 
                const set<char>& begins, 
                const set<char>& ends)  {
    stack<CharInfo> st;
    for(size_t i = 0; i < s.size(); ++i){
        char ch = s[i];
        size_t indx = i + 1;
        if (begins.count(ch) > 0){
            st.push({ch, indx});
        }
        else if (ends.count(ch) > 0){
            if (st.empty()){
                return indx;
            }
            char top = st.top().ch;
            st.pop();
            if ((top == '[' && ch != ']') ||
                (top == '(' && ch != ')') ||
                (top == '{' && ch != '}')) {
                    return indx;
                }

        }
    }

    if (st.empty()){
        return 0;
    }
    else {
        return st.top().indx;
    }
}


int main(int argc, char* argv[]) {  
    string s;
    cin>>s;
    set<char>begins = {'(', '[', '{'};
    set<char>ends = {')', ']', '}'};
    int res = CheckBrackets(s, begins, ends);
    if (res == 0){
        cout<<"Success"<<'\n';
    }
    else {
        cout<<res<<'\n';
    }

    return 0;
}