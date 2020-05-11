#include <bits/stdc++.h>

#define ii pair<int, int>
#define ll long long

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

vector<vector<int>> output;
ii last_seen_out;
int rows, cols;

int get_rect_size(int rect_no, int row, int cols) {
    int x = (2 * ((row + cols - (4 * (rect_no))))) - 4;
    return x == 0 ? 4 : x;
}

//Insert element into output matrix
void insert_into_output(int n, int diag_num) {
    if(last_seen_out.first > diag_num && last_seen_out.second == diag_num) {
        last_seen_out.first--;
        output[last_seen_out.first][last_seen_out.second] = n;
        return;
    }
    if(last_seen_out.first == diag_num && last_seen_out.second < (cols - 1 - diag_num)) {
        last_seen_out.second++;
        output[last_seen_out.first][last_seen_out.second] = n;
        return;
    }
    if(last_seen_out.first < (rows - 1 - diag_num) && last_seen_out.second == (cols - 1 - diag_num)) {
        last_seen_out.first++;
        output[last_seen_out.first][last_seen_out.second] = n;        
        return;
    }
    if(last_seen_out.first == (rows - 1 - diag_num) && last_seen_out.second > diag_num) {
        last_seen_out.second--;
        output[last_seen_out.first][last_seen_out.second] = n;
        return;
    }
}

// Complete the matrixRotation function below.
//Works when row < column && row % 2 == 0
void matrixRotation(vector<vector<int>> matrix, int r) {
    int nume = min(rows, cols);
    vector<ii> diag_cords(nume / 2);

    //Find location of left diagonal half
    for(int i = 0; i < nume / 2; i++) {
        int space_to_move = r % get_rect_size(i, rows, cols);
        diag_cords[i] = ii(i, i);

        if(space_to_move - (rows - 1 - (2 * i)) > 0) {
            diag_cords[i].first = rows - i - 1;
            space_to_move -= (rows - 1 - (2 * i));
        } else {
            diag_cords[i].first = i + space_to_move;
            output[diag_cords[i].first][diag_cords[i].second] = matrix[i][i];
            continue;
        }
        
        if(space_to_move - (cols - 1 - (2 * i)) > 0) {
            diag_cords[i].second = cols - i -1;
            space_to_move -= (cols - 1 - (2 * i));
        } else {
            diag_cords[i].second = i + space_to_move;
            output[diag_cords[i].first][diag_cords[i].second] = matrix[i][i];
            continue;
        }

        if(space_to_move - (rows - 1 - (2 * i)) > 0) {
            diag_cords[i].first = i;
            space_to_move -= (rows - 1 - (2 * i));
        } else {
            diag_cords[i].first -= space_to_move;
            output[diag_cords[i].first][diag_cords[i].second] = matrix[i][i];
            continue;
        }

        if(space_to_move - (cols - 1 - (2 * i)) > 0) {
            diag_cords[i].second = i;
            space_to_move -= (cols - 1 - (2 * i));
        } else {
            diag_cords[i].second = space_to_move;
            output[diag_cords[i].first][diag_cords[i].second] = matrix[i][i];
            continue;
        }
    }

    for(int i = 0; i < nume / 2; i++) {
        last_seen_out = ii(diag_cords[i].first, diag_cords[i].second);
        for(int k = i + 1; k < cols - i; k++) {
            insert_into_output(matrix[i][k], i);
        }
        for(int k = i + 1; k < rows - i; k++) {
            insert_into_output(matrix[k][cols - 1 - i], i);
        }
        for(int k = cols - 2 - i; k >= i; k--) {
            insert_into_output(matrix[rows - 1 - i][k], i);
        }
        for(int k = rows - 2 - i; k > i; k--) {
            insert_into_output(matrix[k][i], i);
        }
    }

    for(int i = 0; i < rows; i++) {
        for(int k = 0; k < cols; k++) {
            cout << output[i][k] << " ";
        }
        cout << '\n';
    }
}

int main()
{
    string mnr_temp;
    getline(cin, mnr_temp);

    vector<string> mnr = split(rtrim(mnr_temp));

    int m = stoi(mnr[0]);
    rows = m;
    int n = stoi(mnr[1]);
    cols = n;
    int r = stoi(mnr[2]);

    vector<vector<int>> matrix(m);
    output = vector<vector<int>>(m, vector<int>(n));

    for (int i = 0; i < m; i++) {
        matrix[i].resize(n);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

        for (int j = 0; j < n; j++) {
            int matrix_row_item = stoi(matrix_row_temp[j]);

            matrix[i][j] = matrix_row_item;
        }
    }

    matrixRotation(matrix, r);

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
