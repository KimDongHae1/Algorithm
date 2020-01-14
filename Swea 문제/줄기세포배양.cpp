// 줄기세포배양
// 번식을 무제한으로 할 수 있기 때문에 적당한 크기의 위치를 잡아줘야한다.
// 활성화된 세포와 비활성화된 세포를 나누는 기준이 있어야 한다.
// 크기가 큰 것부터 차례대로 움직여 주어야 한다.
#include<iostream>
#include<memory.h>
#include<queue>

#define MAX 400
 
using namespace std;
 
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };
 
int map[MAX][MAX];
 
int tc;
int N, M, K;
int ans;
 
struct Node {
    int x;
    int y;
    int time;
};
 
void printAll() {
    cout << "========================================================" << "\n";
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
}
 
void init() {
    memset(map, 0, sizeof(map));
}
// map을 초기화 시켜주는 부분. 
int main() {
    cin >> tc;
 
    for (int k = 1; k <= tc; k++) {
 
        init();
 
        ans = 0;
        cin >> N >> M >> K;
        queue<Node> q[11];
        // 줄기세포의 세기에 따라 사용하는 큐 10 -> 1까지 있다.
 
        for (int i = 200; i < N + 200; i++) {
            for (int j = 200; j < M + 200; j++) {
                cin >> map[i][j];
                if (map[i][j]) {
                    q[map[i][j]].push({i, j, map[i][j] * 2});
                }
            }
        }
 
        while (K--) {
            for (int i = 10; i >= 1; i--) {
                // 생명력이 높은 줄기세포를 넣기 위해 10 -> 1로 한다.
                int size = q[i].size();
                for (int j = 0; j < size; j++) {
                    int x = q[i].front().x;
                    int y = q[i].front().y;
                    int time = q[i].front().time;
                    q[i].pop();
                    // 큐에서 빼고 
                    time--;
                    // 시간을 빼준다.
                    if (map[x][y] > time) // 활성화 된 상태.
                    {
                        for (int a = 0; a < 4; a++) {
                            int nx = x + dx[a];
                            int ny = y + dy[a];
                            if (map[nx][ny] == 0) // 비어 있는 공간을 나타낸 것.
                            {
                                map[nx][ny] = map[x][y];
                                q[i].push({nx, ny, map[nx][ny] * 2});
                            }
                        } 
                        // 활성화가 되어 상하좌우에 번식시킨다.
                    } 
                    if (time > 0) {
                        q[i].push({x, y, time});
                    }
                    // 살아있으면 넣고, 살아있지 않으면 큐에 넣지 않는다.
                } 
            } 
        } 
        for (int i = 1; i < 11; i++) {
            ans += q[i].size();
        }
        cout << "#" << k << " " << ans << "\n";
    }
 
    return 0;
}