#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
	int n;
    cin>>n;
    string query;
    string name;
    int number;

    vector<string> names(10000000, "-");
    for(int i = 0; i < n; ++i){
        cin>>query;
        cin>>number;
        if (query == "add"){
            cin>>name;
            names[number] = name;
        }
        else if (query == "del"){
            names[number] = "-";
        }
        else if (query == "find"){
            if (names[number] == "-"){
                cout<<"not found"<<'\n';
            }
            else {
                cout<<names[number]<<'\n';
            }
        }
    }
	
	return 0;
}