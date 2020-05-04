#include<bits/stdc++.h>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> minpath(n);
    for(int i = 0; i < n; i++) {
        cin >> minpath[i];
    }
    
    for(int i = 1; i < n; i++) {
        int nodes_to_search = i > k ? k : i;
        int min_prev_path = minpath[i - 1];
        for(int j = i - 1; j >= (i) - nodes_to_search; j--) {
            if(minpath[j] < min_prev_path) {
                min_prev_path = minpath[j];
            }
        }
        minpath[i] *= min_prev_path;
        minpath[i] = minpath[i] % 1000000007;
    }
    cout << minpath[n - 1] % 1000000007 << "\n";
}