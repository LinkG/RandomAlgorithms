#include <bits/stdc++.h>

using namespace std;

int main() {
    int num_cases;
    cin >> num_cases;

    int index;
    int size, t, max_val, max_num;
    bool swich;
    for(int i = 0; i < num_cases; i++) {
        max_num = 0;
        swich = false;
        index = 0;
        vector<int> list;
        map<int, int> freq;
        cin >> size;
        for(int j = 0; j < size; j++) {
            cin >> t;
            if(j == 0) {
                list.push_back(t);
                index++;
                swich = true;
                continue;
            } else if(t != list[index - 1]) {
                list.push_back(t);
                index++;
                swich = true;
                continue;
            }
            if(!swich) {
                list.push_back(t);
                index++;
            }
            swich = !swich;
        }

        for(auto i = list.begin(); i != list.end(); i++) {
            auto pos = freq.find(*i);
            if(pos == freq.end()) {
                freq.insert(pair<int, int>(*i, 1));
            } else {
                pos->second = pos->second + 1;
            }
        }

        for(auto i = freq.begin(); i != freq.end(); i++) {
            if(i -> second > max_num) {
                max_val = i -> first;
                max_num = i -> second;
                continue;
            }
            if(i -> second == max_num && i -> first < max_val) {
                max_val = i -> first;
            }
        }

        cout << max_val << '\n';
    }
}