//아기상어(BFS+시뮬레이션)
//BFS문제인데 별로 어렵지 않다.
#include <iostream>
#include <vector>
#include <memory.h>
#include <queue>
#define MAX 21

using namespace std;

int N;
int map[MAX][MAX];
bool visit[MAX][MAX];

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };

struct shark {
    int x;
    int y;
    int time;
};


queue<shark> q;

int shark_size = 2;
int cnt = 0;
int sum = 0;

int current = 99999;

bool finish = false; 

void printAll(int a[][MAX]) {
    cout << "\n\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
}

bool checks() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] != 0) {
                if (shark_size > map[i][j]) {
                    return true;
                }

            }
        }
    }
    return false;
}

void init() {
    while (!q.empty()) {
        q.pop();
    }
}

void bfs() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] == 9) {
                map[i][j] = 0;
                q.push({ i,j,0 });
                visit[i][j] = true;
            }
        }
    }
    finish = false;
    current = 99999;
    int endX = 987987;
    int endY = 987987;
    while (!q.empty()) {
        /*cout << "sadasdsad" << "\n";*/
        int cx = q.front().x;
        int cy = q.front().y;
        int cSize = q.front().time;
        q.pop();
        // 종료되었을 시점!!
        if (current < cSize) {
            break;
        }
        // 아니면 먹잇감 중에서 최소거리에 있는 것을 찾는다.
        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            int nSize = cSize + 1;

            if (nx >= 0 && nx < N &&ny >= 0 && ny < N) {
                if ((map[nx][ny] == 0 || map[nx][ny] == shark_size) && !visit[nx][ny]) {
                    visit[nx][ny] = true;
                    q.push({ nx,ny,nSize });
                }
                else if (shark_size > map[nx][ny] && !visit[nx][ny]) {
                    visit[nx][ny] = true;
                    q.push({ nx,ny,nSize });
                    if (!finish) {
                        current = cSize;
                        finish = true;
                    }
                    // 가장 왼쪽에 있고 위쪽에 있는 것
                    if (endX >= nx) {
                        if (endX == nx) {
                            if (endY > ny) {
                                endX = nx;
                                endY = ny;
                            }
                        }
                        else {
                            endX = nx;
                            endY = ny;
                        }
                    }
                }
            }
        }
    }

    init();

    if (finish) {
        cnt++;
        if (shark_size == cnt) {
            shark_size++;
            cnt = 0;
        }
        map[endX][endY] = 9;
        sum += current+1;
    }
}


int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }
    while (1) {
        memset(visit, false, sizeof(visit));
        bfs();
        if (!finish) {
            break;
        }
    }
    cout << sum;
    return 0;
}