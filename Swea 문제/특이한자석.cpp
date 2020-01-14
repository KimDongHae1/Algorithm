// 특이한 자석 및 톱니바퀴
// 반대방향에 맞게 돌려주는 것이 포인트이다.
#include <iostream>
#include <memory.h>
 
using namespace std;
 
int tc; // 테스트 케이스의 갯수.
int K;
int map[4][8];
bool visit[4] = { false, };
 
void transfer(int a[8],int dir) {
    if (dir == 1) {
        int temp = a[7];
        for (int i = 6; i >= 0; i--) {
            a[i + 1] = a[i];
        }
        a[0] = temp;
    }
    else if (dir == -1) {
        int temp = a[0];
        for (int i = 1; i <= 7; i++) {
            a[i - 1] = a[i];
        }
        a[7] = temp;
    }
	// 1일 경우 시계방향, -1일 경우 반시계 방향으로 돌아간다.
}
 
 
void dfs(int num,int dir) {
    visit[num] = true;
 
    if (!visit[num + 1] && num + 1 < 4) {
        if (map[num][2] != map[num + 1][6]) {
            // 오른쪽에 마주보는 것과 다르다.
            dfs(num + 1, dir*-1);
        }
    }
    if (!visit[num - 1] && num - 1 >= 0) {
        if (map[num - 1][2] != map[num][6]) {
            dfs(num - 1, dir*-1);
        }
    }
	// 왼쪽 다보고 오른쪽 다봐서 돌린다.   
    transfer(map[num], dir);
}
 
 
int main() {
    cin >> tc;
    for (int k = 1; k <= tc; k++) {
        cin >> K;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 8; j++) {
                cin >> map[i][j];
            }
        }
        // 4개의 톱니바퀴에 수가 다 들어갔다.
        for (int i = 0; i < K; i++) {
            int number;
            int dir;
            cin >> number >> dir;
            memset(visit, false, 4);
            dfs(number-1, dir);
        }
 
        int sum = 0;
     
        if (map[0][0] == 1) {
            sum += 1;
        }
        if (map[1][0] == 1) {
            sum += 2;
        }
        if (map[2][0] == 1) {
            sum += 4;
        }
        if (map[3][0] == 1) {
            sum += 8;
        }
        cout << "#" << k << " " << sum << "\n";
    }
    return 0;
}