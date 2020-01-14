// 활주로 건설(시뮬레이션)
// 가로 방향과 세로 방향 모든 방향을 봐야한다.
// 경사로를 놓아서 제대로 된 활주로를 만들 수 있는지를 찾는 것. 
#include <iostream>
#include <memory.h>
#define MAX 21
using namespace std;
 
int tc;
int N;
int X;
 
int map[MAX][MAX];
int check[MAX];
bool cons[MAX] = { false, };
void printAll(int arr[][MAX]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
}
 
bool checkairstrip(int arr[MAX]) {
    memset(cons, false, MAX);
 
    for (int i = 0; i < N - 1; i++) {
        //1. 그대로 유지 될 경우. 6X6 배열이라면 5까지만 보면 된다.
        if (arr[i] == arr[i + 1]) {
            continue;
        }
        // 앞에 있는 것이랑 위치가 같을 경우.
        else if (arr[i] + 1 == arr[i + 1]) {
            // 올라가는 경우,
            int cnt = 1;

            for (int j = i; j > i - X + 1; j--) {
                if (!cons[j] && arr[j] == arr[j - 1] && j > 0 && !cons[j - 1]) {
                    cnt++;
                }
                else {
                    return false;
                }
            }
            for (int j = i; j > i - X; j--) {
                cons[j] = true; // 활주로 깐 것들
            }
        }
        else if (arr[i] - 1 == arr[i + 1]) {    ₩
            // 내려가는 경우
            int cnt = 1;
            for (int j = i + 1; j < i + X; j++) {
                if (!cons[j] && arr[j] == arr[j + 1] && j < N && !cons[j + 1]) {
                    cnt++;
                }
                else {
                    return false;
                }
            }
 
            for (int j = i + 1; j < i + X + 1; j++) {
                cons[j] = true; // 활주로 깐 것들
            }
        }
        else {
            // 두칸 이상 차이 날
            return false;
        }
 
    }
    return true;
}
 
int main() {
    cin >> tc;
    for (int k = 1; k <= tc; k++) {
        cin >> N >> X;
 
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> map[i][j];
            }
        }
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                check[j] = map[i][j];
            }
            if (checkairstrip(check)) {
                cnt++;
            }
        }
        for (int j = 0; j < N; j++) {
            for (int i = 0; i < N; i++) {
                check[i] = map[i][j];
            }
            if (checkairstrip(check)) {
                cnt++;
            }
        }
        cout << "#" << k << " " << cnt << "\n";
    }
    return 0;
}