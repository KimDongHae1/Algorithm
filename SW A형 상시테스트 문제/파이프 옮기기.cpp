//#include "pch.h"
#include <iostream>

#define MAX 20

using namespace std;

struct pipe {
	int x;
	int y;
	int dir;
};
// dir == 1 가로 ,  dir == 2 세로 , dir = 3 대각선  
int N;
int map[MAX][MAX];
int cnt = 0;

void printAll(int arr[][MAX]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << arr[i][j] << " ";
		}
		cout << "\n";
	}
}

void dfs(int x, int y, int dir) {
	if (x < 0 || x >= N || y < 0 || y >= N) {
		return;
	}
	if (x == N - 1 && y == N - 1) {
		cnt++;
	}
	else {
		if (dir == 1) {
			// 다음으로 갈 수 있는 dir이 1, 3이다.
			if (map[x][y + 1] != 1) {
				dfs(x, y + 1, 1);
			}
			if (map[x + 1][y] != 1 && map[x + 1][y + 1] != 1 && map[x][y + 1] != 1) {
				dfs(x+1, y + 1, 3);
			}
		}
		else if(dir == 2){
			if (map[x+1][y] != 1) {
				dfs(x+1, y, 2);
			}
			if (map[x + 1][y] != 1 && map[x + 1][y + 1] != 1 && map[x][y + 1] != 1) {
				dfs(x + 1, y + 1, 3);
			}
		}
		else if (dir == 3) {
			if (map[x][y + 1] != 1) {
				dfs(x, y + 1, 1);
			}
			if (map[x + 1][y] != 1) {
				dfs(x + 1, y, 2);
			}
			if (map[x + 1][y] != 1 && map[x + 1][y + 1] != 1 && map[x][y + 1] != 1) {
				dfs(x + 1, y + 1, 3);
			}
		}
	}
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
	cnt = 0;
	// printAll(map);

	dfs(0, 1, 1);
	cout << cnt;
}
