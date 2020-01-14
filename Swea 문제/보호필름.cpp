// 보호필름
// dfs 방법으로 접근, 또한 2번의 백트래킹 방법으로 모든 경우의 수를 다 봐야한다.
// 최적화 시켜주는 부분은 최소 적은 수를 구하는 것이기 때문에 0~n까지 돌리면서 값이 성공하면 바로 종료.

#include <iostream>
#define MAX 21
using namespace std;
 
int tc;
int D;
int W;
int K; // 검사.

int map[MAX][MAX];
int tmp[MAX][MAX];

int memo[MAX];
int temp[MAX];
bool visit[MAX] = { false, };
 
int Sol = 0;
 
void printAll(int a[][MAX]) {
    cout << "====================================" << "\n";
    for (int i = 0; i < D; i++) {
        for (int j = 0; j < W; j++) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
}
 
bool check(int arr[][MAX]) {
    //성능검사
    //각 열에 대한 chk값이 K 이상 이면 통과이다.
    int chk;
    for (int i = 0; i < W; i++) {
        chk = 1;
        for (int j = 0; j < D - 1; j++) {
 
            if (chk >= K) break;
            if (arr[j][i] == arr[j + 1][i]) chk++;
            else chk = 1;
 
        }
        if (chk < K)
            return false;
    }
    return true;
}
 
void init() {
    for (int i = 0; i < D; i++) {
        for (int j = 0; j < W; j++) {
            map[i][j] = tmp[i][j];
        }
    }
}
 
void Backtracking(int level ,int cnt) {
    if (cnt == level) {
		// 약을 넣을 부분을 정한다음에 0을 넣을지 1을 넣을지 모든 경우의 수를 다 확인한다.
        for (int i = 0; i < level; i++) {
            for (int j = 0; j < W; j++) {
                map[memo[i]][j] = temp[i];
            }
        }
        if (check(map)) {
            Sol = level;
        }
 
 
    }
    else {
        for (int i = 0; i < 2; i++) {
            temp[cnt] = i;
            Backtracking(level, cnt + 1);
            temp[cnt] = -1;
        }
    }
}
 
void dfs(int d, int cnt) {
    if (d == cnt) {
        // 0과 1로 바꾸어주는 작업
        // memo에 모든 경우의 수가 들어간다. 
        // 모든 경우의 수에 0또는 1을 넣어줘야한다. 
        Backtracking(d,0);
 
        init();
    }
    else {
        for (int i = 0; i < D; i++) {
            if (!visit[i]) {
                if (cnt == 0) {
                    visit[i] = true;
                    memo[cnt] = i;
                    dfs(d, cnt + 1);
                    visit[i] = false;
                }
                else {
                    if (memo[cnt - 1] < i) {
                        visit[i] = true;
                        memo[cnt] = i;
                        dfs(d, cnt + 1);
                        visit[i] = false;
                    }
                }
            }
        }
    }
}
 
int main() {
    cin >> tc;
    for (int k = 1; k <= tc; k++) {
        cin >> D >> W >> K;
        for (int i = 0; i < D; i++) {
            for (int j = 0; j < W; j++) {
                cin >> map[i][j];
                tmp[i][j] = map[i][j];
            }
        }
 
        Sol = -1;
        if (check(map)) {
            Sol = 0;
        }
        else {
            for (int i = 1; i <= D; i++) {
                if (Sol == -1) {
                    dfs(i, 0);
                }
                else {
					// 값이 나오면 바로 종료한다.
                    break;
                }
            }
        }
        cout << "#" << k << ' ' << Sol << '\n';
    }
    return 0;
}