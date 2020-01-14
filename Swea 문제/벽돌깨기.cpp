// 구슬을 3개 쏴서 최대한 많은 벽돌을 깨는 경우의 수를 구해라
// 최소로 남은 벽돌의 갯수를 구해라.
// 시뮬레이션
#include <iostream>
#include <queue>
#define MAX 15
 
struct point {
    int x;
    int y;
    int size;
};
// 벽돌의 위치와 크기를 나타내는 구조체
 
using namespace std;
 
int map[MAX][MAX];
int Memo[MAX][MAX];
 
int a[4];
int tc; // 테스트 케이스의 갯수.
int N; // 쏘는 공의 갯수.
int W; // 가로의 길이
int H; // 세로의 길이
 
int Sol = 987987;
 
queue<point> q;
 
void printAll(int a[][MAX]) {
    cout << "====================================================" << "\n";
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
}
 
void init() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            map[i][j] = Memo[i][j];
        }
    }
}
// 다시 벽돌들을 원상복구 시켜주는 코드.
 
void check() {
    //FIFO que에 넣어두고 맨 밑에서부터 재할당
    queue <int> s;
    for (int j = 0; j < W; j++) {
        int a = H - 1;
        for (int i = H-1; i >= 0; i--) {
            if (map[i][j] != 0) {
                s.push(map[i][j]);
                map[i][j] = 0;
            }
             
        }
        while (!s.empty()) {
            map[a][j] = s.front();
            a--;
            s.pop();
        }
    }
    // printAll(map);
}
// 떠 있는 벽돌들을 밑으로 내려주는 코드.
 
void cal2(int x,int y, int size) {
    map[x][y] = 0;
    point p;
    p.x = x;
    p.y = y;
    p.size = size;
    q.push(p);
    // size가 1이상만 들어올 수 있다.
    while (!q.empty()) {
        //cout << "sdadasdasdasdasd" << "\n";
        int currentX = q.front().x;
        int currentY = q.front().y;
        int curSize = q.front().size;
 
        q.pop();
 
        for (int i = 1; i < curSize; i++) {
            int nx = currentX;
            int ny = currentY + i;
            if (nx >= 0 && nx < H && ny >= 0 && ny < W) {
                if (map[nx][ny] >= 2) {
                    point p1;
                    p1.x = nx;
                    p1.y = ny;
                    p1.size = map[nx][ny];
                    q.push(p1);
                    map[nx][ny] = 0;
                }
                else {
                    map[nx][ny] = 0;
                }
            }
            else {
                break;
            }
        }
		// 오른쪽 부분
 
        for (int i = 1; i < curSize; i++) {
            int nx = currentX + i;
            int ny = currentY;
            if (nx >= 0 && nx < H && ny >= 0 && ny < W) {
                if (map[nx][ny] >= 2) {
                    point p1;
                    p1.x = nx;
                    p1.y = ny;
                    p1.size = map[nx][ny];
                    q.push(p1);
                    map[nx][ny] = 0;
                }
                else {
                    map[nx][ny] = 0;
                }
            }
            else {
                break;
            }       
        }
        // 아래 부분.

        for (int i = 1; i < curSize; i++) {
            int nx = currentX;
            int ny = currentY - i;
            if (nx >= 0 && nx < H && ny >= 0 && ny < W) {
                if (map[nx][ny] >= 2) {
                    point p1;
                    p1.x = nx;
                    p1.y = ny;
                    p1.size = map[nx][ny];
                    q.push(p1);
                    map[nx][ny] = 0;
                }
                else {
                    map[nx][ny] = 0;
                }
            }
            else {
                break;
            }   
        }
        // 왼쪽 부분.

        for (int i = 1; i < curSize; i++) {
            int nx = currentX - i;
            int ny = currentY;
            if (nx >= 0 && nx < H && ny >= 0 && ny < W) {
                if (map[nx][ny] >= 2) {
                    point p1;
                    p1.x = nx;
                    p1.y = ny;
                    p1.size = map[nx][ny];
                    q.push(p1);
                    map[nx][ny] = 0;
                }
                else {
                    map[nx][ny] = 0;
                }
            }
            else {
                break;
            }
        }
		// 위 부분.
    }
    check();
}
 
void Cal() {
    for (int i = 0; i < N; i++) {
        int cho = a[i];
     
        for (int j = 0; j < H; j++) {
            if (map[j][cho] == 0) {
                continue;
            } // 0이면 넘어간다.
            else if (map[j][cho] == 1) {
                map[j][cho] = 0;
                break;
            }
            else {
                 
                cal2(j,cho,map[j][cho]);
                break;
            }
        }
    }
}
 
void che() {
    int cnt = 0;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (map[i][j] != 0) {
                cnt++;
            }
        }
    }
    if (Sol > cnt) {
        Sol = cnt;
    }
}
// 남은 벽돌의 갯수가 몇개가 있는지 알려주는 함수.
 
void BT(int cnt) {
    if (cnt == N) {
        // 모든 경우의 수가 들어온다.
        Cal();
        che();
        init();
        // printAll(map);
    }
    else {
        for (int i = 0; i < W; i++) {
            a[cnt] = i;
            BT(cnt + 1);
            a[cnt] = -1;
        }
    }
}
 
int main() {
    cin >> tc;
    for (int k = 1; k <= tc; k++) {
        cin >> N >> W >> H;
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                cin >> map[i][j];
                Memo[i][j] = map[i][j];
            }
        }
        // printAll(map);
        Sol = 987987;
        BT(0);
        cout << "#" << k << " " << Sol << "\n";
    }
    return 0;
}