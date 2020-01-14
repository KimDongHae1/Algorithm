// 벌꿀채취 (dfs + 시뮬레이션)
// 두 명의 일꾼이 선택한 벌꿀에서 최대한 많은 벌꿀을 뽑는 것이 문제이다.
// 2중 BT를 사용해서 푸는 문제로 A 사람 일꾼의 위치를 찾은 후 B일꾼의 위치를 계속 비교해준다.
#include <iostream>
#include <algorithm>
#include <memory.h>
 
#define MAX 11
 
using namespace std;
 
int map[MAX][MAX];
bool visited[MAX][MAX];
int n, m, c, res;
 
int t;
 
int max(int a, int b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}
 
//비용 구하기
void Price(int x, int y, int a, int sum, int price) {
    if (sum > c) return;
    res = max(res, price);
    if (a == m) return;
 
    Price(x, y + 1, a + 1, sum + map[x][y], price + map[x][y] * map[x][y]);
    Price(x, y + 1, a + 1, sum, price);
}
 
int solve(int x, int y) {
    //먼저 고른 m개의 벌통에 대해 비용 구하기
    for (int i = 0; i < m; i++) {
        visited[x][y + i] = true;
    }
    res = 0;
    Price(x, y, 0, 0, 0);
    int priceA = res;
 
    //나중에 고른 m개의 벌통에 대해 비용 구하며 비교하기
    int priceB = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - m + 1; j++) {
            if (!visited[i][j]) {
                res = 0;
                Price(i, j, 0, 0, 0);
                priceB = max(priceB, res);
            }
        }
    }
 
    return priceA + priceB;
    // 모든 경우의 수를 다 본다.
}
 
void init() {
    memset(visited, 0, sizeof(visited));
}
 
int main() {
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        init();
        cin >> n >> m >> c;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> map[i][j];
            }
        }
 
        int mm = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - m + 1; j++) {
                mm = max(mm, solve(i, j));
            }
        }
        // 모든 경우의수를 다본다. 
        cout << "#" << tc << " " << mm << "\n";
    }
}