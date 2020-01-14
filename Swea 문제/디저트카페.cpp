// 디저트 카페
// dfs를 돌 때 대각선으로만 움직이는 것이 가능하다
// 다시 원래 자리로 돌아오는 사각형을 만들어야 한다.
// 같은 숫자의 디저트를 팔고 있는 카페를 방문하면 안된다.
// 왔던 길을 다시 돌아가면 안된다.
#include <iostream>
#include <memory.h>
 
#define MAX 21
using namespace std;
 
int tc;
int N; // 도시의 크기
int map[MAX][MAX]; // 도시에 디저트 종류
bool visit[MAX][MAX] = { false, }; // 방문 횟수 찾기
bool check[101] = { false, }; // 디저트 수 겹치지 않게 하기 
 
int dx[4] = { 1,1,-1,-1 };
int dy[4] = { 1,-1,-1,1 };
// 0 -> 우하단 , 1 -> 좌하단 , 2 -> 좌상단, 3 -> 우상단  
 
int Sol = -1;
 
int endX;
int endY;
 
void printAll(int arr[][MAX]) {
    cout << "=====================================" << "\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
}
 
void printAll(bool arr[][MAX]) {
    cout << "=====================================" << "\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (arr[i][j]) {
                cout << "1 ";
            }
            else {
                cout << "0 ";
            }
        }
        cout << "\n";
    }
}
 
void dfs(int startX, int startY, int dir, int cnt) {
    // 위치하고, 그 숫자를 true
    visit[startX][startY] = true;
    check[map[startX][startY]] = true;
    // 방문했던 카페하고, 디저트수를 겹치지 않게 하기 위해 사용.
    for (int i = dir; i < dir+2; i++) {
	//한 방향으로만 dfs움직이게 하기위해 사용.
        int nx = startX + dx[i];
        int ny = startY + dy[i];
        if (nx >= 0 && nx < N && ny >= 0 && ny < N && !visit[nx][ny] && !check[map[nx][ny]]) {
            dfs(nx, ny, i, cnt+1);
        }
        else if (nx == endX && ny == endY) {
			// 원래 자리로 돌아오면 종료.
            if (cnt > Sol) {
                Sol = cnt;
                return;
            }
        }
    }
 
    visit[startX][startY] = false;
    check[map[startX][startY]] = false;
}
 
void init() {
    for (int i = 0; i < MAX; i++) {
        memset(visit[i],false, MAX);
    }
    memset(check, false, 101);
}
// 초기화 시켜주는 부분
 
int main() {
    cin >> tc;
    for (int k = 1; k <= tc; k++) {
        cin >> N;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> map[i][j];
            }
        }
        //printAll(map);
        Sol = -1;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                init();
                endX = i;
                endY = j;
                dfs(i, j, 0, 1);
            }
        }   
        cout << "#" << k << " " << Sol << "\n";
    }
    return 0;
}