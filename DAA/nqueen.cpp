// Design N-Queens matrix having first Queen placed. Use backtracking to place remaining Queens to generate the final N-queen.
#include <bits/stdc++.h>
using namespace std;

class NQueen
{
    vector<vector<int>> board;
    int fixedCol = 0;
    bool isSafe(int row, int col, int n)
    {
        // check left side row
        for (int k = 0; k < n; k++)
            if (board[row][k] == 1)
                return false;
        // check upper side column
        for (int k = 0; k < n; k++)
            if (board[k][col] == 1)
                return false;

        // all four diagonals
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
            if (board[i][j] == 1)
                return false;
        for (int i = row + 1, j = col + 1; i < n && j < n; i++, j++)
            if (board[i][j] == 1)
                return false;
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
            if (board[i][j] == 1)
                return false;
        for (int i = row + 1, j = col - 1; i < n && j >= 0; i++, j--)
            if (board[i][j] == 1)
                return false;

        return true;
    }
    bool solve(int col, int n)
    {
        if (col >= n)
            return true;
        if (col == fixedCol)
            return solve(col + 1, n);
        for (int row = 0; row < n; row++)
        {
            if (isSafe(row, col, n))
            {
                board[row][col] = 1;
                if (solve(col + 1, n))
                    return true;
                board[row][col] = 0;
            }
        }
        return false;
    }

public:
    void generate(int n, int firstRow, int firstCol)
    {
        board.assign(n, vector<int>(n, 0));
        board[firstRow][firstCol] = 1;
        fixedCol = firstCol;
        if (!solve(0, n))
        {
            cout << "No solution exists" << endl;
            return;
        }
        else
        {
            for (auto &row : board)
            {
                for (int cell : row)
                    cout << cell << " ";
                cout << endl;
            }
        }
    }
};

int main()
{
    NQueen nq;
    nq.generate(6, 4, 3);
    return 0;
}