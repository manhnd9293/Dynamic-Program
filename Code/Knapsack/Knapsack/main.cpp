#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Item {
    public:
        int w, v;
        Item(int a, int b){
            w = a;
            v = b;
        }
};

int Knapsack(Item* w [],int n, int W);
void find_Solution(Item* w[],int i, int W, int **M);

int Knapsack(Item* w [],int n, int W){
    int** M = new int* [n+1];
    if(M == nullptr) return -1;
    for(int i = 0; i <= n; i++){
        M[i] = new int[W+1];
        if(M[i] == nullptr) return -1;
    }

    for(int i = 0; i <= W; i++) M[0][i] = 0;

    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= W; j++){
            if(w[i]->w > j) {
                M[i][j] = M[i-1][j];
            } else {
                M[i][j] = max(w[i]->v + M[i-1][j - w[i]->w], M[i-1][j]);
            }
        }
    }
    int res = M[n][W];
    cout << "Max = " << res << endl;

    //cout << "Solution : ";
    //find_Solution(w,n,W,M);

    for(int i = 0; i <=n; i++) delete [] M[i];
    delete [] M;
    return res;
}

void find_Solution(Item* w[], int i, int W, int **M){
    if(i == 0 || W == 0) return;
    if(w[i]->w > W) find_Solution(w, i-1, W,M);
    else if (w[i]->v + M[i-1][W-w[i]->w] >=M[i-1][W]){
        cout << w[i]->v << '-' << w[i]->w << endl;
        find_Solution(w,i-1,W - w[i]->w,M);
    } else {
        find_Solution(w,i-1,W,M);
    }
}

int main()
{
    srand(time(NULL));
    int n = 100;
    Item **a = new Item* [n+1];
    for(int i = 1; i <= n; i++){
        a[i] = new Item (rand()%20+1, rand() %15 +1);
    }

    int W = 1500;
    Knapsack(a,n,W);

    for(int i =1; i <= n; i++)
        delete a[i];
    delete [] a;

    return 0;
}

