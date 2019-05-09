#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

using namespace std;

bool isMatch(char a, char b);
void find_solution(const char *s, int i, int j, int **M);
int opt(const char * s, int n);

int opt(const char * s, int n){
    int** M = new int* [n+1];
    if(M == nullptr) return -1;
    for(int i = 0; i <= n; i++){
        M[i] = new int[n+1];
        if(M[i] == nullptr) return -1;
    }

    for(int i = 1; i <= n; i++){
        for(int k = -1; k <= 4; k++){
            int j = i + k;
            if(j <= n) M[i][j]= 0;
        }
    }

    for(int l = 5; l <= n-1; l++){
        for(int i = 1; i <= n - l; i++){
            int j = i + l;
            int max_k = 0;
            for(int k = i; k <= j-5; k++){
                if(isMatch(s[k],s[j])){
                    int v = 1  + M[i][k-1] + M[k+1][j-1];
                    if(v > max_k) max_k = v;
                }
            }
            M[i][j] = max(M[i][j-1], max_k);
        }
    }

    int res = M[1][n];
    find_solution(s,1,n,M);
    for(int i = 0; i <=n; i++) delete [] M[i];
    delete [] M;
    return res;

}


inline bool isMatch(char a, char b){
    if((a == 'A' && b == 'U') || (a == 'U' && b == 'A')
      ||(a == 'G' && b == 'C') || (a == 'C' && b == 'G'))
        return true;
    return false;
}

void find_solution(const char * s, int i, int j, int **M){
    if(j <= i) return;
    if(M[i][j] == M[i][j-1]) find_solution(s,i,j-1,M);
    else{
        int f = i;
        for(int k = i; k <= j-5; k++){
            if(isMatch(s[k],s[j]) && M[i][j] == 1 + M[i][k-1] + M[k+1][j-1] ) {
                f = k;
                break;
            }
        }
        cout << '(' << f << ',' << j << ')' << ' ';
        find_solution(s,i,f-1,M);
        find_solution(s,f+1,j-1,M);
    }
}

int main()
{
    srand(time(NULL));
    int n = 1500;
    char base [] = {'A','U','G','C'};
    char *s = new char [n+1];
    for(int i = 1; i <= n; i++){
        s[i] = base[rand()%4];
    }
    for(int i =1; i <=n; i++){
        cout << s[i];
    }

    cout << endl;

    int res = opt(s,n);
    cout << res << endl;
    delete [] s;
    return 0;
}
