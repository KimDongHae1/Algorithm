// 플로이드 와샬 알고리즘
// 모든 정점에서 모든 정점으로의 최단 거리를 찾는 것이다.
#include<iostream>

using namespace std;

int number;
int INF = 987987987;

// 자료 배열 초기화
int a[4][4] = {
	{0,5,INF,8},
	{7,0,9,INF},
	{2,INF,0,4},
	{INF,INF,3,0}
};

void floydWarshall() {
	int d[4][4];

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			d[i][j] = a[i][j];
		}
	}
	// 3 중포문을 사용해 플로이드 와샬 알고리즘을 구할 수 있다.
	// k는 거쳐가는 노드.
	for (int k = 0; k < 4; k++) {
		// i = 출발 노드
		for (int i = 0; i < 4; i++) {
			// j = 도착 노드
			for (int j = 0; j < 4; j++) {
				if (d[i][k] + d[k][j] < d[i][j]) {
					d[i][j] = d[i][k] + d[k][j];
				}
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << d[i][j] << " ";
		}
		cout << "\n";
	}

}

int main() {
	floydWarshall();
	return 0;
}