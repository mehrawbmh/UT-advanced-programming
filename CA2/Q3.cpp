#include <iostream>
#include <vector>

using namespace std;

void inputNumbers(vector<int> &vec, int x) {
    for (int i = 0; i < x; i++) {
        int num;
        cin >> num;
        vec.push_back(num);
    }
}

bool isValid(int row, int col, char ch, vector<int> rowX, vector<int> colX, vector<int> rowZ, vector<int> colZ) {
    switch (ch) {
        case 'X': return (rowX[row] == -1 || rowX[row] > 0) && (colX[col] == -1 || colX[col] > 0);
        case 'Z': return (rowZ[row] == -1 || rowZ[row] > 0) && (colX[col] == -1 || colZ[col] > 0);
        default: return false;
    }
}

bool hasSolution(int row, int col, const int n, const int m, vector<vector<char>>& rooms, vector<int>& rowX, vector<int>& rowZ, vector<int>& colX, vector<int>& colZ)
{
    if (row == n && col == m) {
        return true;
    }

    for (char ch: {'L', 'R', 'T', 'B'}) {
        int nextRow = (col == n - 1) ? row + 1 : row;
        int nextColumn = (col == n - 1) ? 0 : col + 1;

        if (rooms[row][col] == 'L') {
            if (isValid(row, col, 'X', rowX, colX, rowZ, colZ)) {
                rowX[row]--;
                colX[col]--;
                rooms[row][col] = 'X';

                if (hasSolution(nextRow, nextColumn, n, m, rooms, rowX, rowZ, colX, colZ)) {
                    return true;
                }

                rowX[row]++;
                colX[col]++;
                rooms[row][col] = ch;
            }

            if (isValid(row, col, 'Z', rowX, colX, rowZ, colZ)) {
                rowZ[row]--;
                colZ[col]--;
                rooms[row][col] = 'Z';

                if (hasSolution(row, col + 1, n, m, rooms, rowX, rowZ, colX, colZ)) {
                    return true;
                }

                rowZ[row]++;
                colZ[col]++;
                rooms[row][col] = ch;
            }
        }
    }
    return false;
}

int main() {
    int m, n;
    cin >> m >> n;

    vector<vector<char>> rooms(m);

    for (int i = 0; i < m; i++) {
        rooms[i].resize(n);
        for (int j = 0; j < n; j++) {
            cin >> rooms[i][j];
        }
    }

    vector<int> colX, rowX, colZ, rowZ;
    inputNumbers(colX, n);
    inputNumbers(colZ, n);
    inputNumbers(rowX, m);
    inputNumbers(rowZ, m);

    if (hasSolution(0, 0, n, m, rooms, rowX, rowZ, colX, colZ)) {
        cout << "has sol:" << endl;
        for (auto room: rooms) {
            for (char x: room) {
                cout << x << " ";
            }
            cout << endl;
        }
    } else {
        cout << "No Solution!";
    }

    return 0;
}
