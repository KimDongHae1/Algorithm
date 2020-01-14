// 크루스칼 알고리즘 : 간선을 거리가 짧은 순서대로 그래프에 포함시키면 어떨까?
// 노드와 간선의 차이를 알고 있어야 한다.
// 모든 간선 정보를 오름차순으로 넣고.
// cycle이 형성되지 않도록 해야한다.
// union find 알고리즘 사용 해서 사이클을 확인해야한다.
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;



// 부모 노드를 찾는 함수.
int getParent(int parent[],int x) {
	if (parent[x] == x) return x;
	return parent[x] = getParent(parent, parent[x]);
}
// 두 부모 노드를 합치는 함수.
void unionParent(int parent[], int a, int b) {
	a = getParent(parent, a);
	b = getParent(parent, b);
	if (a < b) parent[b] = a;
	else parent[a] = b;
}
// 같은 부모를 가지는 확인한다.
int findParent(int parent[], int a, int b) {
	a = getParent(parent, a);
	b = getParent(parent, b);
	if (a == b) return 1;
	return 0;
}

// 간선 클래스 선언
class Edge {
	public:
		int node[2];
		int distance;
		Edge(int a, int b, int distance) {
			this->node[0] = a;
			this->node[1] = b;
			this->distance = distance;
		}
		bool operator < (Edge &edge) {
			return this->distance < edge.distance;
		}
};
// 이 부분이 비교를 할 때 길이로만 하겠다는 의미이다.

int main() {
	int n = 7;
	int m = 11;
	vector<Edge> v;
	v.push_back(Edge(1, 7, 12));
	v.push_back(Edge(1, 4, 28));
	v.push_back(Edge(1, 2, 67));
	v.push_back(Edge(2, 4, 24));
	v.push_back(Edge(2, 5, 62));
	v.push_back(Edge(3, 5, 20));
	v.push_back(Edge(3, 6, 37));
	v.push_back(Edge(4, 7, 13));
	v.push_back(Edge(5, 6, 45));
	v.push_back(Edge(5, 7, 73));
	v.push_back(Edge(1, 5, 17));
	sort(v.begin(), v.end());
	// 간선의 비용으로 정점을 비교해준다.
	int parent[7];
	for (int i = 0; i < n; i++) {
		parent[i] = i;
	}
	int sum = 0;
	for (int i = 0; i < v.size(); i++) {
		// cycle이 발생하지 않는 경우 그래프에 포함시켜준다.
		if (!findParent(parent, v[i].node[0] - 1, v[i].node[1] - 1)) {
			sum += v[i].distance;
			unionParent(parent, v[i].node[0] - 1, v[i].node[1] - 1);
		}
	}
	cout << sum;

	 
	return 0;
}