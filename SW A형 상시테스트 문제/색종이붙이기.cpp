#include<iostream>
# define MAX 10
using namespace std;

int map[MAX][MAX];

int paper[6] = { 0,5,5,5,5,5 };

int minn = 987987987;

void printAll(int a[][MAX]) {
	cout << "\n\n";
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << a[i][j] << " ";
		}
		cout << "\n";
	}
}

void dfs(int sum,int x, int y) {

	// printAll(map);
	if (y == MAX)
	{
		dfs(sum,x + 1, 0);
		return;
	}

	// 마지막 줄까지 다 확인했으므로 현재 색종이 개수 확인
	if (x == MAX)
	{
		if (minn > sum) {
			minn = sum;
		}
		return;
	}
	// 덮을 필요 없으므로 다음 칸 확인
	if (map[x][y] == 0)
	{
		dfs(sum,x, y + 1);
		return;
	}

	for (int len = 5; len >= 1; len--) {
		if (paper[len] == 0 || x + len > MAX || y + len > MAX)
		{
			continue;
		}
		bool flag = true;
		for (int j = 0; j < len; j++)
		{
			for (int k = 0; k < len; k++)
			{
				if (map[x + j][y + k] == 0)
				{
					flag = false;
					break;
				}
			}

			if (!flag)
			{
				break;
			}
		}
		// 존재하지 않으면 확인할 필요 없음
		if (!flag)
		{
			continue;
		}

		for (int j = 0; j < len; j++)
		{
			for (int k = 0; k < len; k++)
			{
				map[x + j][y + k] = 0;
			}
		}

		paper[len]--;

		// 다음 칸 확인
		dfs(sum + 1, x, y+len);
		for (int j = 0; j < len; j++)
		{
			for (int k = 0; k < len; k++)
			{
				map[x + j][y + k] = 1;
			}
		}

		paper[len]++;
	}

}

int main() {
	
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cin >> map[i][j];
		}
	}
	// printAll(map);
	
	dfs(0,0,0);

	if (minn == 987987987) {
		cout << -1;
		return 0;
	}
	cout << minn;
	return 0;
}