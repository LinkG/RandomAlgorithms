#include <iostream>
#include <vector>

using namespace std;

void display(vector<vector<int>> &matrix) {
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[i].size(); j++) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

void rotateMatrix(vector<vector<int>> &matrix, int r) {
    int num_cols = matrix[0].size() - 1, num_rows = matrix.size() - 1;
    int lim =  (int)min(num_cols, num_rows) / 2;
    for(int n = 0; n <= lim; n++) {
        int length = (2 * (num_cols - (2 * n))) + (2 * (num_rows - (2 * n)));
        int holder = matrix[n][n];
        int row = n, col = n;
        int move = r % length;
        for(int i = 0; i < length; i++) {
            int moves = move;
            while(moves > 0) {
                if(col == n) {
                    row + moves <= (num_rows - n) ? (row = row + moves, moves = 0) : (moves -= num_rows - n - row, row = num_rows - n);
                }
                if(row  == num_rows - n) {
                    col + moves <= (num_cols - n) ? (col = col + moves, moves = 0) : (moves -= num_cols - n - col, col = num_cols - n);
                }
                if(col == num_cols - n) {
                    row - moves >= n ? (row = row - moves, moves = 0) : (moves -= row - n, row = n);
                }
                if(row == n) {
                    col - moves >= n ? (col = col - moves, moves = 0) : (moves -= col - n, col = n);
                }
            }
            int swap = matrix[row][col];
            matrix[row][col] = holder;
            holder = swap;            
        }
    }
    display(matrix);
}

int main() {
    vector<vector<int>> matrix;
    int m, n, r;
    cin >> m >> n >> r;
    matrix.resize(m);
    for(int i = 0; i < m; i++) {
        matrix.at(i).resize(n);
        for(int j = 0; j < n; j++) {
            cin >> matrix.at(i).at(j);
        }
    }
    rotateMatrix(matrix, r);
    return 0;
}