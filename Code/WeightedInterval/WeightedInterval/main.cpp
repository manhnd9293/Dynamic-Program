#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Request {
    public:
    /*s = ngay bat dau, f = ngay ket thuc, v= gia tri cua yeu cau */
    int s, f, v;
    Request(int a, int b,int c){
        s = a;
        f = b;
        v = c;
    }
};

int previous(int j , Request* list []);
int compute_Opt(int j, Request* jobList []);
int M_compute_Opt(Request* jobList [], int n, int *p);
int M_compute_Opt_aux(int j, Request* jobList [], int *M, int *p);
void sortRequest(Request * r [], int n);
void find_Solution(Request* jobList[], int *M, int j, int *p);
int iterate_Compute_opt(Request* jobList [], int n, int *p);


/* Sap xep cac yeu cau theo ngay ket thuc tang dan */
void sortRequest(Request * r [], int n){
    for(int i = 1; i <=n; i++){
        int k = i;
        for(int j = i; j <= n; j++){
            if(r[k]->f > r[j]->f) k = j;
        }
        if(k > i){
            Request* t = r[i];
            r[i] = r[k];
            r[k] = t;
        }
    }
}

/*tim yeu cau gan nhat khong giao voi yeu cau thu j trong mang */
int previous(int j , Request* list []){
    int k = j-1;
    while(k != 0 && (list[k]->f > list[j]->s)) {
        k--;
    }
    return k;
}

/*thuat toan de quy khong nho */
int compute_Opt(int j, Request* jobList [], int *p){
    if(j == 0) return 0;
    else {
        return max(jobList[j]->v + compute_Opt(p[j],jobList,p),
                   compute_Opt(j-1,jobList,p));
    }
}

/* ham tra ve tong gia tri lon nhat cac yeu cau khong giao nhau
 * voi tap yeu cau la {1,2,...n} su dung phuong phap de quy co nho
 * dung bang M de luu tru va tham chieu ket qua cac bai toan con */

int M_compute_Opt(Request* jobList [], int n, int *p){
    int *M = new int [n+1];
    for(int i = 0; i <= n; i++) M[i] = -1;

    int res = M_compute_Opt_aux(n, jobList, M, p);

    cout << "Solution: " << endl;
    find_Solution(jobList,M,n,p);
    delete [] M;
    return res;
}
/* ham tra ve tong gia tri lon nhat cac yeu cau khong giao nhau
 * voi tap yeu cau la {1,2,...j} su dung phuong phap de quy co nho
 * dung bang M de luu tru va tham chieu ket qua cac bai toan con */

int M_compute_Opt_aux(int j, Request* jobList [], int *M, int *p){
    if (j == 0) return 0;
    if (M[j] != -1) return M[j];
    else {
     M[j] = max(jobList[j]->v + M_compute_Opt_aux(p[j],jobList,M,p),
                M_compute_Opt_aux(j-1,jobList,M,p));
     return M[j];
    }
}

/*Ham dua ra man hinh 1 bo toi uu cho bai toan voi  voi tap yeu cau la {1,2,...j} */
void find_Solution(Request* jobList[], int *M, int j, int *p){
    if(j == 0) return;
    else {
        if (jobList[j]->v + M[p[j]] >= M[j-1]){
            cout << "request " << j << ": "<< "v = " << jobList[j]->v << endl;
            find_Solution(jobList,M, p[j],p);
        } else {
            find_Solution(jobList, M, j-1,p);
        }
    }
}

/*thuat toan su dung vong lap de giai bai toan ban dau */
int iterate_Compute_Opt(Request* jobList [], int n, int *p){
    int *M = new int [n+1];
    M[0] = 0;
    for(int i = 1; i <= n; i++){
        M[i] = max(jobList[i]->v + M[p[i]], M[i-1]);
    }
    int res = M[n];
    delete [] M;
    return res;
}

const int RANDOM_REQUEST_START = 10000;
const int RANDOM_REQUEST_LENGTH = 200;
const int RANDOM_REQUEST_VALUE = 1000;

int main()
{
    /* tao du lieu dau vao de test thuat toan */
    srand(time(nullptr));
    int n = 40000;
    Request **list = new Request* [n+1];
    for(int i = 1; i <= n; i++){
        int a = rand() % RANDOM_REQUEST_START +1;
        int b = a + rand() % RANDOM_REQUEST_LENGTH + 1;
        int c = rand() % RANDOM_REQUEST_VALUE  + 1;
        list[i] = new Request(a,b,c);
    }

    sortRequest(list,n);

    /*tao mang p voi p[i] la yeu cau khong giao gan nhat truoc yeu cau thu i */
    int* p = new int [n+1];
    for(int i = 1; i <= n; i++){
        p[i] = previous(i,list);
    }

    cout <<"ket qua thuat toan dung de quy co nho = " << M_compute_Opt(list,n,p) << endl;

    cout << "ket qua thuat toan dung vong lap = " << iterate_Compute_Opt(list,n,p) << endl;

    for(int i = 1; i <= n; i++){
        delete list[i];
    }
    delete [] list;
    delete [] p;

    return 0;
}
