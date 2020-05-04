#include <bits/stdc++.h>

using namespace std;

int main() {
    int num_cases;
    cin >> num_cases;
    cin.ignore();
    while(num_cases--) {
        string str;
        getline(cin, str);
        bool possible  = true;
        if(str.length() <= 2) {
            cout << "YES\n";
            continue;
        }
        for(int i = 0; i < str.length() - 2; i++) {
            if(str[i] != str[i + 2]) {
                possible = false;
                break;
            }
        }
        if(possible) {
            if(str[str.length() - 2] != str[0] || str[str.length() - 1] != str[1] )  {
                possible = false;
            }
        }
        cout << (possible ? "YES\n" : "NO\n");
    }
}