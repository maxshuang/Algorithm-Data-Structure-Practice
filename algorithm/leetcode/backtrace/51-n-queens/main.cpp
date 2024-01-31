/*
 The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.
Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.

Constraints:
1 <= n <= 9
 */

class Solution {
    vector<vector<string>> res;
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<string> chessboard(n, std::string(n, '.'));
        backtrace(n, 0, chessboard);
        return res;
    }

    void backtrace(int n, int row, vector<string>& chessboard) {
        // end condition
        if(row==n) {
            res.push_back(chessboard);
            return;
        }

        // for each layer, we test all columns
        for(int j=0; j<n; ++j) {
            if(!isValid(n, chessboard, row, j)) {
                continue;
            }
            // make selection
            chessboard[row][j]='Q';
            backtrace(n, row+1, chessboard);
            // revert selection
            chessboard[row][j]='.';
        }
    }

    bool isValid(int n, vector<string>& chessboard, int row, int col) {
        // check whether columns conflict with pre-selection
        for(int i=0; i<row;++i) {
            if(chessboard[i][col]=='Q') {
                return false;
            }
        }

        // check left upside conflict with pre-selection
        for(int i=row-1, j=col-1; i>=0 && j>=0; --i, --j) {
            if(chessboard[i][j]=='Q'){
                return false;
            }
        }

        // check right upside conflict with pre-selction
        for(int i=row-1, j=col+1; i>=0 && j<n; --i, ++j) {
            if(chessboard[i][j]=='Q'){
                return false;
            }
        }

        return true;
    }
};
