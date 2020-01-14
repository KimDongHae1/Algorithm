// union find 합집합 알고리즘 
// 배열을 사용해서 표현한다.
// 모든 원소가 자기자신을 부모라고 생각하고 시작한다.
// 연결되어 있다고 가정하고 부모를 바꿀때는 node의 값이 더 작은 값을 부모라고 생각한다.
// 재귀함수를 사용해서 본다.
// find는 두개의 배열 값을 이용해서 너희 같은 부모를 가지고 있니를 보는 것이다.

#include <iostream>

using namespace std;
// 부모 노드를 찾는 함수라고 볼 수 있다.
int getParent(int parent[], int x) {
	if (parent[x] == x) return x; // 재귀함수의 종료부분이라고 보면 된다.
	return parent[x] = getParent(parent, parent[x]);
}

// 두 부모 노드를 합치는 함수.

void unionParent(int parent[], int a, int b) {
	a = getParent(parent, a);
	b = getParent(parent, b);
	if (a < b) parent[b] = a;
	else parent[a] = b;
}

// 같은 부모를 가지는 확인하는 함수, 같은 그래프에 있는지를 확인하는 함수.
int findParent(int parent[], int a, int b) {
	a = getParent(parent, a);
	b = getParent(parent, b);
	if (a == b) return 1;
	else return 0;
}

int main() {
	int parent[11];
	// 자기자신을 부모로 가리키는 경우.
	for (int i = 1; i < 11; i++) {
		parent[i] = i;
	}
	unionParent(parent, 1, 2);
	unionParent(parent, 2, 3);
	unionParent(parent, 3, 4);
	
	unionParent(parent, 5, 6);
	unionParent(parent, 6, 7);
	unionParent(parent, 7, 8);
	unionParent(parent, 4, 5);

	cout << findParent(parent, 1, 5);

	return 0;
}