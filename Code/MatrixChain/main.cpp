#include <iostream>

using namespace std;

int matrixChain(vector <int>p){
    int m = p.size()-1;
    int a[m+1][m+1];
    for(int i =1; i <=m; i++) a[i][i] = 0;
    for(int l = 2; l <= m; l++){
        for(int i = 1; i <=m-l+1; i++){
            int j = i+l-1;
            int a[i][j] = INT_MAX;
            for(int k = i; k <= j-1; k++){
                int r = a[i][k] + a[k+1][j] + p[i-1]*p[k]*p[j];
                if(r < a[i][j]) a[i][j] = r;
            }
        }
    }
    return a[1][m];
}

int rodCuting_bottonUp(vector <int> l){
    int n = l.size();
    int a[n+1];
    a[0] = 0;
    int s[n+1];
    for(int i = 1; i <= n; i++){
        a[i] = -1;
        for(j=1; j <= i; j++){
            int q = l[j-1] + a[i-j];
            if(q > a[i]){
                a[i] = q;
                s[i] = j;
            }
        }
    }
    return a[n];
}

int rodCuting_aux(int k, vector <int> &p, vector <int> &m){
    if(k==0) return 0;
    if(m[k] != -1) return m[k];
    else {
        m[k] = -1;
        for(int i = 1; i <= k; i++){
            int q = p[i-1] + rodCuting_aux(k-i,p,m);
            if(q > m[k]) m[k] = q;
        }
    }
    return m[k];
}

int rodCuting(vector <int> p){
    int max = -1;
    int m = p.size();
    vector <int> v (-1,m+1);
    v[1] = p[0];
    return rodCuting_aux(m,p,v);
}


int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
