// 탈주범 검거(BFS)
// 움직일 수 있는 위치, 못가는 위치를 찾아 BFS돌리면 된다.
#include <iostream>
#include <queue>
#include <memory.h>
#define MAX 52
using namespace std;
 
struct point {
    int x;
    int y;
    int size;
};
 
int map[MAX][MAX];
bool check[MAX][MAX] = { false, };
 
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };
 
int tc; // 테스트 케이스
int N;// 지도의 세로 크기
int M;//지도의 가로 크기
 
int R; // 맨홀 뚜껑의 세로 위치
int C; // 맨홀 뚜껑의 가로 위치
 
int L; // 탈출 후 소요되는 시간
 
int Sol = 0;
 
queue<point> q1;
 
void printAll(int a[][MAX]) {
    cout << "===================================" << "\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
}
 
void printAll(bool a[][MAX]) {
    cout << "===================================" << "\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (a[i][j]) {
                cout << "1 ";
            }
            else {
                cout << "0 ";
            }
        }
        cout << "\n";
    }
}
 
void init() {
    while (!q1.empty())
    {
        q1.pop();
    }
    for (int i = 0; i < MAX; i++) {
        memset(check[i], false, MAX);
        memset(map[i], 0, MAX);
    }
 
}
 
void Calculate() {
    Sol = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (check[i][j]) {
                Sol++;
            }
        }
    }
}
// 계산해준다. 
void bfs(int x, int y) {
    point p;
    p.x = x;
    p.y = y;
    p.size = 0;
    q1.push(p);
    // q1에 처음위치를 넣어준다.
    while (!q1.empty()) {
        int currentX = q1.front().x;
        int currentY = q1.front().y;
        int curSize = q1.front().size;
        int curT = map[currentX][currentY];
 
        q1.pop();
 
        if (curSize >= L) {
            // cout << curSize << "\n";
            break;
        }
 
        check[currentX][currentY] = true;
 
        for (int i = 0; i < 4; i++) {
            int nx = currentX + dx[i];
            int ny = currentY + dy[i];
            int nT = map[nx][ny];
            if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
                if (!check[nx][ny]) {
                //  cout << "curT : " << curT << "\n";
                    if (curT == 2) {
                        if (i == 2 || i == 3) {
                            continue;
                        }
                    }
                    else if (curT == 3) {
                        if (i == 0 || i == 1) {
                            continue;
                        }
                    }
                    else if (curT == 4) {
                        if (i == 1 || i == 2) {
                            continue;
                        }
                    }
                    else if (curT == 5) {
                        if (i == 0 || i == 2) {
                            continue;
                        }
                    }
                    else if (curT == 6) {
                        if (i == 0 || i == 3) {
                            continue;
                        }
                    }
                    else if (curT == 7) {
                        if (i == 1 || i == 3) {
                            continue;
                        }
                    }
                    if (i == 0) {
                        if (nT == 1 || nT == 2 || nT == 5 || nT == 6) {
                            point p1;
                            p1.x = nx;
                            p1.y = ny;
                            p1.size = curSize + 1;
                            q1.push(p1);
                        }
                    }
                    else if (i == 1) {
                        if (nT == 1 || nT == 2 || nT == 4 || nT == 7) {
                            point p1;
                            p1.x = nx;
                            p1.y = ny;
                            p1.size = curSize + 1;
                            q1.push(p1);
                        }
                    }
                    else if (i == 2) {
                        if (nT == 1 || nT == 3 || nT == 4 || nT == 5) {
                            point p1;
                            p1.x = nx;
                            p1.y = ny;
                            p1.size = curSize + 1;
                            q1.push(p1);
                        }
                    }
                    else if (i == 3) {
                        if (nT == 1 || nT == 3 || nT == 6 || nT == 7) {
                            point p1;
                            p1.x = nx;
                            p1.y = ny;
                            p1.size = curSize + 1;
                            q1.push(p1);
                        }
                    }
                }
            }
        }
    }
}
 
int main() {
    cin >> tc;
    for (int k = 1; k <= tc; k++) {
        init();
        cin >> N >> M >> R >> C >> L;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cin >> map[i][j];
            }
        }
         
         
        bfs(R,C);
        // printAll(check);
        Calculate(); // 계산해주는 함수.
        cout << "#" << k << " " << Sol << "\n";
    }
    return 0;
}