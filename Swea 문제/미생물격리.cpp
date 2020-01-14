// 미생물 격리(시뮬레이션)
// 모든 미생물들을 벡터에 넣은 후 계속 움직여준다.
// 그후에 합쳐질지 범위를 벗어나 반으로 줄어들지 등을 확인한다.
// 일정시간이 지난 후 남은 수를 계산하면 된다.
#include <iostream>
#include <vector>
 
#define MAX 101
 
using namespace std;
 
typedef struct Microbe {
    int x;
    int y;
    int size;
    int dire;
}microbe;
 
int tc;
int N; // map의 크기.
int M; // 격리 시간.
int K; // 미생물의 개수
 
int map[MAX][MAX];
 
microbe m[MAX][MAX];
vector<microbe> v;
 
microbe transfer(microbe microbe1) {
    int x = microbe1.x;
    int y = microbe1.y;
    int size = microbe1.size;
    int dire = microbe1.dire;
 
    if (dire == 1) {
        x = x - 1;
        if (x == 0) {
            dire = 2;
            size = size / 2;
        }
    }
    else if (dire == 2) {
        x = x + 1;
        if (x == N - 1) {
            dire = 1;
            size = size / 2;
        }
    }
    else if (dire == 3) {
        y = y - 1;
        if (y == 0) {
            dire = 4;
            size = size / 2;
        }
    }
    else if (dire == 4) {
        y = y + 1;
        if (y == N - 1) {
            dire = 3;
            size = size / 2;
        }
    }
 
    microbe microbe2;
    microbe2.x = x;
    microbe2.y = y;
    microbe2.size = size;
    microbe2.dire = dire;
    return microbe2;
}
// 이동시켜준 후 이동시킨 미생물들을 반환해준다.
 
int main() {
    cin >> tc;
    for (int k = 1; k <= tc; k++) {
        cin >> N >> M >> K;
 
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                m[i][j].size = 0;
                map[i][j] = 0;
            }
        }
        for (int i = 0; i < K; i++) {
            int x, y, size, dire;
            cin >> x >> y >> size >> dire;
            microbe microbe1;
 
            microbe1.x = x;
            microbe1.y = y;
            microbe1.size = size;
            microbe1.dire = dire;
 
            m[x][y] = microbe1;
        }
        // 처음 정보들을 넣어준다.
        for (int a = 0; a < M; a++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    map[i][j] = 0;
                    if (m[i][j].size != 0) {
                        v.push_back(m[i][j]);
                        m[i][j].size = 0;
                    }
 
                }
            }
            // 배열에 있는 미생물들을 벡터에 넣어준다.
 
            for (int i = 0; i < v.size(); i++) {
                microbe microbe1 = transfer(v[i]);
                if (m[microbe1.x][microbe1.y].size == 0) {
                    m[microbe1.x][microbe1.y] = microbe1;
                    map[microbe1.x][microbe1.y] = microbe1.size;
                }
                else if (m[microbe1.x][microbe1.y].size > microbe1.size) {
                    map[microbe1.x][microbe1.y] += microbe1.size;
                }
                else if (m[microbe1.x][microbe1.y].size < microbe1.size) {
                    map[microbe1.x][microbe1.y] += microbe1.size;
                    m[microbe1.x][microbe1.y] = microbe1;
                }
            }
            // 미생물들을 map에 넣어주면서 합쳐지는 것을 계산한다.
 
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    m[i][j].size = map[i][j];
                }
            }
            v.clear();
            // 백터에 넣어준 것을 이동.
        }
        int sum = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (m[i][j].size != 0) {
                    sum += m[i][j].size;
                }
            }
        }
        cout << "#" << k << " " << sum << "\n";
    }
    return 0;
}