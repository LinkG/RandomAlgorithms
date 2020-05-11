#include<bits/stdc++.h>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<double> arr_vals(n);
    vector<double> minpath(n);
    minpath[0] = arr_vals[0];
    for(int i = 0; i < n; i++) {
        cin >> arr_vals[i];
        arr_vals[i] = log10(arr_vals[i]);
    }
    
    for(int i = 0; i < n; i++) {
        int nodes_to_search = i >= k ? k : i;
        int min_prev_path = arr_vals[i - 1];
        for(int j = i - 1; j >= i - nodes_to_search; j--) {
            if(arr_vals[j] < min_prev_path) {
                min_prev_path = arr_vals[j];
            }
        }
        arr_vals[i] += min_prev_path;
    }
    cout << arr_vals[n] << "\n";
}