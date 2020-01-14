//2048(EASY)
//처음에 문제를 제대로 안읽어 힘들어했던 문제.
//queue를 이용해 순서 맞추는 것을 배웠던 문제.
#include <iostream>
#include <queue>
#define MAX 21

using namespace std;
int N;
int map[MAX][MAX];
int temp[MAX][MAX];
int memo[5];

int maxx = -987987987;

void printAll() {
	cout << "============================================" << "\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << " ";
		}
		cout << "\n";
	}
}

void counter() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (maxx <= map[i][j]) {
				maxx = map[i][j];
			}
		}
	}
}
//최고 숫자 세어주는 것.

void init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j] = temp[i][j];
		}
	}
}

void transfer(int x, int dir) {
	queue<int> q;
	if (dir == 1) {
		int cnt = 0;
		for (int i = 0; i < N; i++) {
			if (map[x][i] != 0) {
				q.push(map[x][i]);
				map[x][i] = 0;
			}
		}
		while (!q.empty()) {
			map[x][cnt] = q.front();
			q.pop();
			cnt++;
		}
	}
	else if (dir == 2) {
		int cnt = N - 1;
		for (int i = N-1; i >= 0; i--){
			if (map[x][i] != 0) {
				q.push(map[x][i]);
				map[x][i] = 0;
			}
		}
		while (!q.empty()) {
			map[x][cnt] = q.front();
			q.pop();
			cnt--;
		}
	}
	else if (dir == 3) {
		int cnt = 0;
		for (int i = 0; i < N; i++) {
			if (map[i][x] != 0) {
				q.push(map[i][x]);
				map[i][x] = 0;
			}
		}
		while (!q.empty()) {
			map[cnt][x] = q.front();
			q.pop();
			cnt++;
		}
	}
	else {
		int cnt = N - 1;
		for (int i = N - 1; i >= 0; i--) {
			if (map[i][x] != 0) {
				q.push(map[i][x]);
				map[i][x] = 0;
			}
		}
		while (!q.empty()) {
			map[cnt][x] = q.front();
			q.pop();
			cnt--;
		}
	}
}
// 상 하 좌 우 한쪽으로 몰아주는 것.
void checking(int x) {
	for (int i = 0; i < x; i++) {
		if (memo[i] == 1)
		{ // 왼쪽으로 기울였을 경우.
			for (int x = 0; x < N; x++) {
				transfer(x, 1);
				for (int y = 0; y < N-1; y++) {
					if (map[x][y] == 0) continue;
					if (map[x][y] == map[x][y + 1]) {
						map[x][y] *= 2;
						map[x][y + 1] = 0;
					}
				}
				transfer(x, 1);
			}
		}
		else if(memo[i] == 2){
			// 오른쪽으로 기울였을 경우.
			for (int x = 0; x < N; x++) {
				transfer(x, 2);
				for (int y = N-1; y >= 1; y--) {
					if (map[x][y] == 0) continue;
					if (map[x][y-1] == map[x][y]) {
						map[x][y] *= 2;
						map[x][y - 1] = 0;
						// 이동
					}
				}
				transfer(x, 2);
			}
		}
		else if (memo[i] == 3) {
			// 위로 기울였을 경우.
			for (int y = 0; y < N; y++) {
				transfer(y, 3);
				for (int x = 0; x < N-1; x++) {
					if (map[x][y] == 0) continue;
					if (map[x][y] == map[x+1][y]) {
						map[x][y] *= 2;
						map[x + 1][y] = 0;
					}
				}
				transfer(y, 3);
			}
		}
		else {
			// 아래로 기울였을 경우.
			for (int y = 0; y < N; y++) {
				transfer(y, 4);
				for (int x = N-1; x >= 1; x--) {
					if (map[x][y] == 0) continue;
					if (map[x-1][y] == map[x][y]) {
						map[x][y] *= 2;
						map[x - 1][y] = 0;
					}
				}
				transfer(y, 4);
			}
		}
	}
}

void BT(int cnt,int level) {
	if (cnt == level) {
		// 순서에 맞게 계산.
		checking(level);
		counter();
		init();
	}
	else {
		for (int i = 1; i <= 4; i++) {
			memo[cnt] = i;
			BT(cnt + 1,level);
		}
	}
}
// 모든 경우의 수 생각한다.

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			temp[i][j] = map[i][j];
		}
	}
	for (int i = 1; i <= 5; i++) {
		BT(0,i);
	}
	cout << maxx;
	return 0;
}