#include <bits/stdc++.h>

using namespace std;

// Complete the encryption function below.
string encryption(string &s) {
    string X;
    int len = s.length();
    int row = floor(sqrt(len)), col = ceil(sqrt(len));
    vector<string> words(col, "");
    for(int i = 0; i < len - 1; i++) {
        words[i % col].push_back(s[i]);
    }
    for(int i = 0; i < col - 1; i++) {
        X.append(words[i]);
        X.push_back(' ');
    }
    X.append(words[col - 1]);
    return X;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    char ch = ' ';
    while(ch != '\n') {
        cin.get(ch);
        if(ch != ' ') {
            s.push_back(ch);
        }
    }
    string result = encryption(s);

    cout << result << "\n";

    fout.close();

    return 0;
}
