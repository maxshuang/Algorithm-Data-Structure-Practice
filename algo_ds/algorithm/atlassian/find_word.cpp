vector<vector<int>> res;
bool end=false;

void dfs(const vector<vector<int>>& grid, const string& word, int i, int j, 
    string& resStr, vector<vector<int>>& path) {
    if(resStr==word) {
        res=path;
        end=true;
        return;
    }
    if(resStr.size()>=word.size()) 
        return;

    resStr.push_back(grid[i+1][j]);
    dfs(grid, word, i+1, j, resStr);
    resStr.pop_back();

    resStr.push_back(grid[i][j+1]);
    dfs(grid, word, i, j+1, resStr);
    resStr.pop_back();
}

vector<vector<int>> findWords(const vector<vector<int>>& grid, const string& word) {
    int m=grid.size(), n=grid[0].size();
    for(int i=0; i<m && !end; ++i) {
        for(int j=0; j<m && !end; ++j) {
            string resStr(grid[i][j]);
            vector<vector<int>> path;
            dfs(grid, word, i, j, resStr);
        }
    }

    return res;
}