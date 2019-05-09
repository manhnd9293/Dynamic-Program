#include <iostream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

int subset_Sum(int n, int W, int w []);
void find_Solution(int w[],int i, int W, int **M);

int subset_Sum(int w [],int n, int W){
    int** M = new int* [n+1];
    if(M == nullptr) return -1;
    for(int i = 0; i <= n; i++){
        M[i] = new int[W+1];
        if(M[i] == nullptr) return -1;
    }

    for(int i = 0; i <= W; i++) M[0][i] = 0;

    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= W; j++){
            if(w[i] > j) {
                M[i][j] = M[i-1][j];
            } else {
                M[i][j] = max(w[i] + M[i-1][j - w[i]], M[i-1][j]);
            }
        }
    }
    int res = M[n][W];

    cout << "Solution : ";
    find_Solution(w,n,W,M);
    cout << endl;

    for(int i = 0; i <=n; i++) delete [] M[i];
    delete [] M;
    return res;
}

void find_Solution(int w[],int i, int W, int **M){
    if(i == 0 || W == 0) return;
    if(w[i] > W) find_Solution(w, i-1, W,M);
    else if (w[i] + M[i-1][W-w[i]] >= M[i-1][W]) {
        cout << w[i] << ' ';
        find_Solution(w,i-1,W - w[i],M);
    } else {
        find_Solution(w,i-1,W,M);
    }
}

int main()
{
    srand(time(NULL));
    int n = 20000;
    int W = 500;
    int *w = new int [n+1];
    for(int i = 1; i <= n; i++){
        w[i] = rand() % 100 +1;
    }

    cout << subset_Sum(w,n,W) << endl;
    return 0;
}
