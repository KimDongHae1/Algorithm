#include <iostream>
#include <memory.h>
#include <string.h>
#include <algorithm>
#include <set>
#include <vector>
#include <math.h>
 
#define MAX 28
using namespace std;
 
int tc; // 테스트 케이스의 갯수.
char str[MAX];
int map[MAX];
int N; //보물상자 비밀번호의 길이
int K; //몇 번째 큰수를 구하냐 
int len; // 길이.
 
vector<long long int> v1; // 값들을 넣기위해 사용
set <long long int> s1;
 
void cycle() {
    int temp = map[N - 1];
    for (int i = N - 2; i >= 0; i--) {
        map[i + 1] = map[i];
    }
    map[0] = temp;
}
 
void Calculator(int a[7]) {
    // 계산해주는 함수.
    long long int sum = 0;
    for (int i = len - 1; i >= 0; i--) {
        sum += pow(16, len - 1 - i) * a[i];
    }
    s1.insert(sum);
}
 
void check() {
    int A[7]; // 1분면
    int B[7]; // 2분면
    int C[7]; // 3분면
    int D[7]; // 4분면
 
    for (int i = 0; i < len; i++) {
        A[i] = map[i];
        B[i] = map[len + i];
        C[i] = map[2*len + i];
        D[i] = map[3*len + i];
    }
 
    Calculator(A);
    Calculator(B);
    Calculator(C);
    Calculator(D);
    // 계산.
}
 
void init() {
    v1.clear();
    s1.clear();
    memset(map, 0, 28);
}
 
int main() {
    cin >> tc;
    for (int k = 1; k <= tc; k++) {
        cin >> N >> K >> str;
        len = N / 4;
        init();
        for (int i = 0; i < N; i++) {
            int temp = str[i];
            if (temp >= 48 && temp <= 57) {
                map[i] = str[i] - 48;
            }
            else if (temp >= 65 && temp <= 70) {
                map[i] = str[i] - 55;
            }
        }
     
        for (int i = 0; i < len; i++) {
            check();
            cycle(); // 돌려주는 함수.
        }
 
        set<long long int>::iterator iter;
        for (iter = s1.begin(); iter != s1.end(); iter++) {
            v1.push_back(*iter);
        }
 
        sort(v1.begin(), v1.end());
         cout << "#" << k << " " << v1[v1.size()- K] << "\n";
    }
    return 0;
}