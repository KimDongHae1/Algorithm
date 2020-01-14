#include<iostream>
#include <queue>
#include <vector>

#define MAX 16

using namespace std;

struct point {
	int x;
	int y;
	int size = 0;
};

struct point2 {
	int x;
	int y;
};

int map[MAX][MAX];
int temp[MAX][MAX];
int memo[3];

bool visit[MAX];

int dx[4] = { 0,-1,0,1 };
int dy[4] = { -1,0,1,0 };

int n, m, d;

vector<point2> v;

int maxx = -98789789;
int sum = 0;

void printAll(int a[][MAX]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << a[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n\n";
}

void init() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			map[i][j] = temp[i][j];
		}
	}
}

void Attack() {
	v.clear();
	for (int i = 0; i < 3; i++) {
		queue<point> q;
		q.push({ n,memo[i],0 });

		while (!q.empty()) {
			int cx = q.front().x;
			int cy = q.front().y;
			int cSize = q.front().size;
			
			q.pop();

			if (cSize > d) {
				break;
			}
			if (map[cx][cy] == 1) {
				v.push_back({ cx,cy });
				map[cx][cy] = -1;
				break;
			}
			if (map[cx][cy] == -1) {
				break;
			}
			// 원하는 파트에 들어왔을 경우!!

			// 범위를 벗어났을 경우!
	

			for (int i = 0; i < 4; i++) {
				int nx = cx + dx[i];
				int ny = cy + dy[i];
				int nSize = cSize + 1;
				if (nx >= 0 && nx <= n && ny >= 0 && ny < m) {
					q.push({ nx,ny,nSize });
				}
			}
		}
	}
	sum += v.size();
	for (int i = 0; i < v.size(); i++) {
		map[v[i].x][v[i].y] = 0;
	}
}

bool checks() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++ ) {
			if (map[i][j] != 0) {
				return false;
			}
		}
	}
	return true;
}

void down() {
	for (int i = n-2; i >= 0; i--) {
		for (int j = 0; j < m; j++) {
			map[i + 1][j] = map[i][j];
		}
	}
	for (int i = 0; i < m; i++) {
		map[0][i] = 0;
	}
}

void BT(int cnt) {
	if (cnt == 3) {
		sum = 0;
		while(1){
			if (checks()) {
				break;
			}
			Attack();
			down();
		}
		if (maxx < sum) {
			maxx = sum;
		}
		init();
	}
	else {
		for (int i = 0; i < m; i++) {
			if (cnt == 0) {
				visit[i] = true;
				memo[cnt] = i;
				BT(cnt + 1);
				memo[cnt] = 0;
				visit[i] = false;
			}
			else if(!visit[i] && memo[cnt-1] < i ){
				visit[i] = true;
				memo[cnt] = i;
				BT(cnt + 1);
				memo[cnt] = 0;
				visit[i] = false;
			}
		}
	}
}

int main() {
	cin >> n >> m >> d;
	for (int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++){
			cin >> map[i][j];
			temp[i][j] = map[i][j];
		} 
	}	
	BT(0);
	cout << maxx;
	return 0;
}