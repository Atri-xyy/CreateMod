#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;
/*typedef int (*func)(int, int);
int foo(int m, int n) {
    cout<<m<<" "<<n<<endl;
    return m + n;
}
func t = foo;
std::cout<<(*t)(1,2);*/

string Trim(string & str) {
    string temp;
    for (auto & i : str) {
        if (i == ' ') {
            continue;
        } else {
            temp += i;
        }
    }
    return temp;
}

int main(void) {
    fstream fs;
    unordered_map<string, string> ump;
    fs.open("config.ini", ios::in | ios::out);
    if(!fs.is_open()) {
        return -1;
    }
    char buf[255];
    while (fs.getline(buf, 255)) {
        string line = string(buf);
        if (!line.empty() && line[0] == '#') {
            continue;
        } else if(!line.empty()) {
            auto str = Trim(line);
            cout<<str.size()<<endl;
            auto idx = str.find('=');
            if (idx == string::npos) { //不符合要求
                continue;
            }
            auto key = str.substr(0, idx);
            auto val = str.substr(idx + 1);
            ump[key] = val;
        }
    }
    for(auto &i : ump) {
        cout << i.first <<" "<<i.second <<endl;
    }
    return 0;
}