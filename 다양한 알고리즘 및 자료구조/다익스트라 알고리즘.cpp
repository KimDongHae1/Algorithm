// 다리만들기 처럼 구조가 나오고 A 집에서 모든 마을을 가는데 걸리는 최단 거리를 구하시오
#include <iostream>
#include <vector>
#include <queue>


using namespace std;

int INF = 1000000;

int n;
vector < pair<int, int>> a[7];
int d[7];

void dij(int start) {
	d[start] = 0;
	priority_queue<pair<int, int>> pq; // 힙구조를 사용하기 위해
	pq.push({ start,0 });
	while (!pq.empty()) {
		int current = pq.top().first; // 가장 적은 비용을 가지는 노드의 정보
		// 더 큰 값을 기준으로 만든다. 최대 힙이다.
		// 짧은 것이 먼저 오도록 음수화 해준다.
		int distance = -pq.top().second;
		pq.pop();
		// 최단거리가 아닌 경우 스킵합니다.
		if (d[current] < distance) continue;
		for (int i = 0; i < a[current].size(); i++) {
			// 선택된 노드의 인접 노드
			int next = a[current][i].first;
			int nextDistance = distance + a[current][i].second;

			if (nextDistance < d[next]) {
				d[next] = nextDistance;
				pq.push({ next,-nextDistance });
			}
		}
	}
}


int main() {
	cin >> n;
	// 기본적으로 연결되지 않는 경우 무한.

	for (int i = 1; i <= n; i++) {
		d[i] = INF;
	}
	a[1].push_back({ 2,2 });
	a[1].push_back({ 3,5 });
	a[1].push_back({ 4,1 });

	a[2].push_back({ 1,2 });
	a[2].push_back({ 3,3 });
	a[2].push_back({ 4,2 });

	a[3].push_back({ 1,5 });
	a[3].push_back({ 2,3 });
	a[3].push_back({ 4,3 });
	a[3].push_back({ 5,1 });
	a[3].push_back({ 6,5 });

	a[4].push_back({ 1,1 });
	a[4].push_back({ 2,2 });
	a[4].push_back({ 3,3 });
	a[4].push_back({ 5,1 });
	a[4].push_back({ 6,5 });

	a[5].push_back({ 3,1 });
	a[5].push_back({ 4,1 });
	a[5].push_back({ 6,2 });
	
	a[6].push_back({ 3,5 });
	a[6].push_back({ 5,2 });

	dij(1);

	for (int i = 1; i <= n; i++) {
		cout << d[i] << " ";
	}
	return 0;
}