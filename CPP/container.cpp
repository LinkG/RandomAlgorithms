#include <bits/stdc++.h>

using namespace std;

// Complete the organizingContainers function below.
string organizingContainers(vector<vector<int>> container) {
    int n = container.size();
    long long balls[n];
    long long balls_in_container[n];
    long long sum;
    fill_n(balls, n, 0);
    fill_n(balls_in_container, n, 0);
    for(int i = 0; i < n; i++) {
        sum = 0;
        for(int j = 0; j < n; j++) {
            balls[j] += container[i][j];
            sum += container[i][j];
        }
        balls_in_container[i] = sum;
    }
    bool flag = true;
    for(int i = 0; i < n; i++) {
        bool flag1 = false;
        for(int j = 0; j < n; j++) {
            if(balls[i] == balls_in_container[j]) {
                balls_in_container[j] = -1;
                flag1 = true;
                break;
            }
        }
        if(!flag1) {
            flag = false;
            break;
        }
    }
    if(flag) {
        return "Possible";
    } else {
        return "Impossible";
    }
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<vector<int>> container(n);
        for (int i = 0; i < n; i++) {
            container[i].resize(n);

            for (int j = 0; j < n; j++) {
                cin >> container[i][j];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        string result = organizingContainers(container);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
