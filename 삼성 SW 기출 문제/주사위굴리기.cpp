// 주사위 굴리기(시뮬레이션)
// 못푼문제, 3차원적으로 주사위를 돌렸을 때 바뀌는 위치를 정확히 파악해야한다.
#include <iostream>

#define MAX 21

using namespace std;

int m, n; // 맵의 크기
int x, y; // 주사위의 첫위치
int k; // 움직이는 횟수.
int map[MAX][MAX];
int cmd[1000]; // 움직임

int dx[4] = { 0, 0, -1, 1 };//동서북남
int dy[4] = { 1, -1, 0, 0 };
int dice[6] = { 0, };

void dice_move(int d) {
	switch (d) {
	case 0://동
		swap(dice[2], dice[0]);
		swap(dice[0], dice[3]);
		swap(dice[3], dice[5]);
		break;
	case 1://서
		swap(dice[3], dice[0]);
		swap(dice[0], dice[2]);
		swap(dice[2], dice[5]);
		break;
	case 2://북
		swap(dice[4], dice[5]);
		swap(dice[0], dice[4]);
		swap(dice[1], dice[0]);
		break;
	case 3://남
		swap(dice[1], dice[0]);
		swap(dice[0], dice[4]);
		swap(dice[4], dice[5]);
		break;
	}

}

void solve() {
	int xx = x;
	int yy = y;

	for (int i = 0; i < k; i++) {

		int nx = xx + dx[cmd[i]];
		int ny = yy + dy[cmd[i]];

		if (nx < 0 || ny < 0 || nx >= m || ny >= n) continue;

		dice_move(cmd[i]);//아래는 5번인덱스; 위는 0

		if (map[nx][ny] == 0) {
			map[nx][ny] = dice[5];
		}
		else {
			dice[5] = map[nx][ny];
			map[nx][ny] = 0;
		}
		cout << dice[0] << "\n";
		xx = nx;
		yy = ny;
	}
}

int main() {
	cin >> m >> n >> x >> y >> k;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < k; i++) {
		int d;
		cin >> d;
		cmd[i] = d - 1;
	}

	solve();
	return 0;
}