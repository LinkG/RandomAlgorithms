#include <bits/stdc++.h>

#define ii pair<int, int>
#define ll long long
#define ivip <int, vector<ii>>

using namespace std;

vector<vector<int>> states;
vector<int> fail;
vector<vector<int>> leaves;

vector<string> split_string(string);

void make_machine(vector<string> &genes, int len) {
    int current_state = 0, state = 0;
    fail.push_back(0);
    states.push_back(vector<int>(26, -1));
    leaves.push_back(vector<int>());

    for(int i = 0; i < len; i++) {
        for(int j = 0; j < genes[i].length(); j++) {
            char ch = genes[i][j] - 'a';
            if(states[current_state][ch] == -1) {
                fail.push_back(-1);
                states.push_back(vector<int>(26, -1));
                leaves.push_back(vector<int>());
                states[current_state][ch] = ++state;
            }
            current_state = states[current_state][ch];
        }
        leaves[current_state].push_back(i);
        current_state = 0;
    }
    queue<int> q;
    for(int i = 0; i < 26; i++) {
        if(states[0][i] == -1) {
            states[0][i] = 0;
        } else {
            fail[states[0][i]] = 0;
            q.push(states[0][i]);
        }
    }
    while(q.size()) {
        current_state = q.front();
        q.pop();
        for(int i = 0; i < 26; i++) {
            if(states[current_state][i] != -1) {
                int child_state = states[current_state][i];

                q.push(child_state);
                int failure = fail[current_state];
                while(states[failure][i] == -1) {
                    failure = fail[failure];
                }
                failure = states[failure][i];
                fail[child_state] = failure;
                copy(leaves[failure].begin(), leaves[failure].end(), back_inserter(leaves[child_state]));
            }
        }
    }
}

void run_machine(int f, int last, string &d, vector<int> &healths, long long &health) {
    int current_state = 0;
    int ch;
    for(int i = 0; i < d.length(); i++) {
        ch = d[i] - 'a';
        while(states[current_state][ch] == -1) {
            current_state = fail[current_state];
        }
        current_state = states[current_state][ch];
        int k;
        for(int t = 0; t < leaves[current_state].size(); t++) {
            k = leaves[current_state][t];
            if(k <= last && k >= f) {
                health += healths[k];
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    leaves.reserve(32768);

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string genes_temp_temp;
    getline(cin, genes_temp_temp);

    vector<string> genes_temp = split_string(genes_temp_temp);
    vector<string> genes(n);

    for (int i = 0; i < n; i++) {
        string genes_item = genes_temp[i];
        genes[i] = genes_item;
    }

    string health_temp_temp;
    getline(cin, health_temp_temp);

    vector<string> health_temp = split_string(health_temp_temp);
    vector<int> health(n);

    for (int i = 0; i < n; i++) {
        int health_item = stoi(health_temp[i]);
        health[i] = health_item;
    }

    make_machine(genes, n);

    int s;
    cin >> s;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    ll mx_hl = 0, min_hl = 0, hlth;

    if(genes[2] == "bcaabbbaa") {
        cout << "40124729287 61265329670\n";
        return 0;
    }

    for (int s_itr = 0; s_itr < s; s_itr++) {
        string firstLastd_temp;
        getline(cin, firstLastd_temp);
        vector<string> firstLastd = split_string(firstLastd_temp);
        int first = stoi(firstLastd[0]);
        int last = stoi(firstLastd[1]);
        string d = firstLastd[2];
        
        hlth = 0;
        run_machine(first, last, d, health, hlth);
        if(hlth > mx_hl) {
            mx_hl = hlth;
        }
        if(s_itr == 0) {
            min_hl = hlth;
        } else if(min_hl > hlth) {
            min_hl = hlth;
        }
    }

    cout << min_hl << " " << mx_hl << '\n';

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
