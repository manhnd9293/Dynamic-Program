#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

const int s1 = 1000;
const int s2 = 10000;
const int s3 = 100000;
const int s4 = 1000000;

int a1[s1];
int a2[s2];
int a3[s3];
int a4[s4];

int maxSub_bruteForce(int a [], int n){
    int maxSum = a[0];
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            int sum = 0;
            for(int k = i; k <= j; k++){
                sum += a[k];
                if(sum > maxSum){
                    maxSum = sum;
                }
            }
        }
    }
    return maxSum;
}

int maxSub_bruteForce_better(int a [], int n){
    int maxSum = a[0];
    for(int i = 0; i < n; i++){
        int sum = 0;
        for(int j = i; j < n; j++){
            sum += a[j];
            if(sum > maxSum){
                maxSum = sum;
            }
        }
    }
    return maxSum;
}

int maxCrossSum(int a[], int l, int r, int mid){
    int max_lef = INT_MIN;
    int max_right = INT_MIN;
    int sum_lelf = 0;
    int sum_right = 0;

    for(int i = mid; i >= l; i--){
        sum_lelf += a[i];
        if(sum_lelf > max_lef) max_lef = sum_lelf;
    }

    for(int i = mid+1; i <= r; i++){
        sum_right += a[i];
        if(sum_right > max_right) max_right = sum_right;
    }

    return (max_lef + max_right);

}

int maxSub_Recursive(int a[], int l, int r){
    if(l == r) return a[l];
    else {
    int mid = (l+r)/2;
    int wL = maxSub_Recursive(a,l, mid);
    int wR = maxSub_Recursive(a,mid+1, r);
    int wM = maxCrossSum(a,l,r, mid);
    int result = max(max(wL, wR), wM);
    return result;
    }
}

int maxSub_DP(int a[], int n){
    int ei = a[0];
    int smax= a[0];
    for(int i = 1; i < n; i++){
        ei = max(a[i], a[i] + ei);
        smax = max(ei, smax);
    }
    return smax;
}

void readData(const char *s, int a [], int n){
    ifstream f;
    f.open(s);
    for(int i = 0; i < n; i++){
        f >> a[i];
    }
    f.close();

}

int main()
{
    int res = 0;
    /* chay cac thuat toan voi mau gom 1 000 so */
    //readData("mau1000so.txt",a1,s1);
    //res = maxSub_bruteForce(a1,s1);
    //res = maxSub_bruteForce_better(a1,s1);
    //res = maxSub_Recursive(a1,0,s1-1);
    //res = maxSub_DP(a1,s1);

    /* chay cac thuat toan voi mau gom 10 000 so */
    //readData("mau10000so.txt",a2,s2);
    //res  = maxSub_bruteForce(a2,s2);
    //res = maxSub_bruteForce_better(a2,s2);
    //res = maxSub_Recursive(a2,0,s2-1);
    //res = maxSub_DP(a2,s2);

    /* chay cac thuat toan voi mau gom 100 000 so */
    readData("mau100000so.txt",a3,s3);
    //res  = maxSub_bruteForce(a3,s3);
    //res = maxSub_bruteForce_better(a3,s3);
    //res = maxSub_Recursive(a3,0,s3-1);
    res = maxSub_DP(a3,s3);

    /* chay cac thuat toan voi mau gom 1 000 000 so */
    //readData("mau1000000so.txt",a4,s4);
    //res  = maxSub_bruteForce(a4,s4);
    //res = maxSub_bruteForce_better(a4,s4);
    //res = maxSub_Recursive(a4,0,s4-1);
    //res = maxSub_DP(a4,s4);

    cout << res << endl;
    return 0;
}
