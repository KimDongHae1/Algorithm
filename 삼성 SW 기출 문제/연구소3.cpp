// 연구소3(BFS+시뮬레이션)
// 모든 경우의 수를 다보고 최소 시간을 찾아야하는 문제.
// check해줘야 하는 부분이 많다.
#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#define MAX 51

using namespace std;

int map[MAX][MAX];
int temp[MAX][MAX];
bool check[MAX][MAX];
int N;
int M;

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

int minn = 987987987;

struct point {
    int x;
    int y;
};
// 위치 구조체

struct birus {
    int x;
    int y;
    int size;
};
// 바이러스 구조체

vector<point> v; // 바이러스가 갈 수 있는 모든 위치 정보를 가지고 있다.
vector<point> v2; // 바이러스가 직접 들어갔다.
queue<birus> q; // 퍼뜨리기 위해 있는 q;

int empty_size = 0;

void init() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            map[i][j] = temp[i][j];
        }
    }
    // map의 값을 다시 원상복구 시킨다.
    memset(check, false, sizeof(check));
    // bool visit 배열 초기화한다. 
}

void printAll(int a[][MAX]) {
    cout << "=================================================" << "\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
}
// 출력에 사용되는 배열, 디버깅에 사용되는 배열.

void bfs() {
    int full_size = 0;
    queue<birus> q; // 퍼뜨리기 위해 있는 q;
    for (int i = 0; i < v2.size(); i++) {
        map[v2[i].x][v2[i].y] = 2;
        q.push({ v2[i].x,v2[i].y,0 });
        check[v2[i].x][v2[i].y] = true;
    }

    int maxx = -987;
    while (!q.empty()) {
        int currentX = q.front().x;
        int currentY = q.front().y;
        int curSize = q.front().size;

        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = currentX + dx[i];
            int ny = currentY + dy[i];
            int nSize = curSize + 1;
            if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                if (!check[nx][ny] && map[nx][ny] == 0) {
                    check[nx][ny] = true;
                    map[nx][ny] = 2;
                    q.push({ nx,ny,nSize });
                    full_size++;
                    // 바이러스를 확산시켰는데 모든 칸에 바이러스가 있는경우. 종료 
                    if (full_size == empty_size) {
                        maxx = nSize;
                        break;
                    }
                }
                else if (!check[nx][ny] && map[nx][ny] == -1) {
                    check[nx][ny] = true;
                    map[nx][ny] = 2;
                    q.push({ nx,ny,nSize });
                    // 바이러스를 확산시켰는데 모든 칸에 바이러스가 있는경우. 종료 
                }
            }
        }
        if (maxx < minn && empty_size == full_size) {
            minn = maxx;
            break;
        }
    }
}

void BT(int cnt) {
    if (cnt == M) {
        // M개가 뽑혔을 경우 활성화 시켜주는 부분.
        bfs();
        // 활성화 시킨 바이러스들을 퍼뜨린다.
        init();
        // 초기화
    }
    else {
        for (int i = 0; i < v.size(); i++) {
            if (cnt == 0) {
                v2.push_back({ v[i].x,v[i].y });
                BT(cnt + 1);
                v2.pop_back();
            }
            else {
                int x = v2[cnt - 1].x;
                int y = v2[cnt - 1].y;
                int xx = v[i].x;
                int yy = v[i].y;
                if (x*N + y < xx*N + yy) {
                    v2.push_back({v[i].x, v[i].y });
                    BT(cnt + 1);
                    v2.pop_back();
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            if (map[i][j] == 0) {
                empty_size++;
            }
            else if (map[i][j] == 2) {
                v.push_back({ i,j });
                map[i][j] = -1;
                // 바이러스가 있을 수 있는 곳은 -1로 바꾼다. 
                // 그리고 vector에 넣어 바이러스의 모든 위치를 넣어준다.
            }
            temp[i][j] = map[i][j];
            // 저장용 위치를 만든다.
        }
    }
    //cout << empty_size << "\n";

    if (checks()) {
        cout << 0;
        return 0;
    }

    BT(0);

    if (minn > 987987) {
        cout << -1;
    }
    // 모든 경우에도 값이 바뀌지 않는 경우.
    else {
        cout << minn;
    }
    // 값 출력
    return 0;
}
