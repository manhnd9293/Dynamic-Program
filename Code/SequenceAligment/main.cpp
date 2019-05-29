#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

const int Delta = 3;
vector <char> vowel = {'u','e','o','a','i'};

inline bool isVowel(char a){
    for(char v : vowel){
        if(v == a) return true;
    }
    return false;
}

inline int cost_char(char a, char b){
    if(a == b) return 0;
    else if(isVowel(a) && isVowel(b)) return 2;
    else return (abs(a-b));
}

int opt(string &s, string &t, int i, int j, int** M){
    if(i == -1 && j == -1){
        return 0;
    } else if( i == -1){
        return (j+1)*Delta;
    } else if (j == -1){
        return (i+1) * Delta;
    }

    if(M[i][j] != -1 ) return M[i][j];
    else {
        int n1 = cost_char(s[i],t[j]) + opt(s,t, i-1, j-1, M);
        int n2 = opt(s, t, i-1,j,M) + Delta;
        int n3 = opt(s, t, i,j-1,M) + Delta;
        M[i][j] = min(min(n1,n2),n3);
        return M[i][j];
    }
}



int cost(string s, string t){
    int m = s.length();
    int n = t.length();

    int **M = new int *[m];

    for(int i = 0; i < m; i++){
        M[i] = new int[n];
    }

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            M[i][j] = -1;
        }
    }

    int res = opt(s,t, m-1, n-1,M);

    for(int i = 0; i < m; i++){
        delete [] M[i];
    }
    delete [] M;
    return res;
}

vector <string> readInput(const char *s){
    vector <string> res ;
    ifstream f;
    f.open(s);
    string t;
    while(getline(f,t)){
        res.push_back(t);
    }
    f.close();
    return res;
}

int main()
{
    cout << "Phan mem du doan tu nhap vao: " << endl;

    vector <string> dict = readInput("word.txt");
    ///*
    while(true){
        cout << "nhap tu can tim: " << endl;
        string s;
        getline(cin>>ws,s);

        int sz= 10;
        vector <string> res (sz);
        vector <int> point(sz, INT_MAX);
        int max_id = 0;
        for(string v : dict){
            int c = cost(v,s);
            if(c < point[max_id]){
                res[max_id] = v;
                point[max_id] = c;
                int max = INT_MIN;
                for(int i = 0; i < sz; i++){
                    if(point[i] > max){
                        max = point[i];
                        max_id = i;
                    }
                }
            }
        }
        cout << endl;
        for(int i =0; i < sz; i++){
            int id_min = i;
            for(int j = i+1; j < sz; j++){
                if(point[j] < point[id_min]){
                    id_min = j;
                }
            }
            if(id_min > i){
                string s_min = res[id_min];
                int p_min = point[id_min];
                res[id_min] = res[i];
                point[id_min] = point[i];
                res[i] = s_min;
                point[i] = p_min;

            }
        }
        if(res[0] == s) cout << s << endl;
        else {
            cout << "Do you mean: " << endl;
            for(int i =0; i < sz; i++){
                cout << res[i] << endl;
            }
        }
        cout << "tim tiep ko ? chon Y\\N " ;
        char ans;
        ans = getchar();
        if(ans == 'n'){
            break;
        }
    }
    //*/
    return 0;
}
