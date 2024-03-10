#include <iostream>
#include <algorithm>

int vec[101][101];
int sum[101][101];

int main() {
    int n, m;
    std::cin >> n >> m;
    for(int i=1; i<=n; ++i) {
        for(int j=1; j<=m; ++j) {
            std::cin >> vec[i][j];
        }
    }
    
    for(int i=0; i<m+1; ++i) sum[i][0]=0;
    for(int j=0; j<n+1; ++j) sum[0][j]=0;
    
    int total_max_len=1;
    for(int i=1; i<=n; ++i) {
        for(int j=1; j<=m; ++j) {
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+vec[i][j];
            int max_len=std::min(i, j);
            if(max_len<=1) continue;
            for(int k=2; k<=max_len; ++k) {
                if(sum[i][j]-sum[i-k][j]-sum[i][j-k]+sum[i-k][j-k]==k*k) {
                    total_max_len=std::max(total_max_len, k);            
                }
            }                    
        }
    }
    
    std::cout << total_max_len;
    return 0;
}