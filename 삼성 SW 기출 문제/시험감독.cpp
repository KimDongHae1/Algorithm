// 시험감독 (시뮬레이션)
// 매우 어렵게 보이지만 매우 쉬운 문제.
// 그냥 수학적 계산이 필요하다.
#include<iostream>
#define MAX 1000001
using namespace std;

int N, b, c;
int person[MAX];

int main() {
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> person[i];
	}
	cin >> b >> c;
	long int Sol = 0;
	for (int i = 0; i < N; i++) {
		person[i] -= b;
		Sol+=1;
		if (person[i] > 0) {
			int res = person[i] / c;
			if (person[i] % c != 0) {
				res++;
			}
			Sol += res;
		}
	}
	cout << Sol;
	return 0;
}