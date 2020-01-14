// 무선충전 (시뮬레이션)
// 
#include <iostream>
#include <vector>
#include <math.h>
 
using namespace std;
 
struct BC {
    int x, y, c, p;
};
 
int dx[5] = { 0,-1,0,1,0 };
int dy[5] = { 0,0,1,0,-1 };
 
 
int col, row, size2, charge;
 
int map[10][10]; // 지도의 크기
int tc; // 테스트 케이스의 갯수.
int M; // 몇 개의 이동 경로를 가질 것인가.
int Bc; // Bc의 갯수, 
int A[101];
int B[101];
 
int ax, ay, ac, bx, by, bc;
 
vector<BC> v;
 
int go() {
    ax = 1; ay = 1; // a의 처음위치
    ac = 0; // a의 양
    bx = 10; by = 10; // b의 처음 위치
    bc = 0; // b의 처음양
 
    for (int t = 0; t <= M; t++) {
        vector<int> a, b;
        // 처음위치부터 100번 움직이는 위치
        // 사용자들의 BC 구하기
        for (int i = 0; i < v.size(); i++) {
			// 모든 경우의 충전기의 위치를 다 본다.
            // 사용자 A
            if (abs(ax - v[i].x) + abs(ay - v[i].y) <= v[i].c) {
                a.push_back(i);
            }
 
            // 사용자 B
            if (abs(bx - v[i].x) + abs(by - v[i].y) <= v[i].c) {
                b.push_back(i);
            }
        }
		// 범위안에 들어와있나? 그것을 확인한다.
 
        int res = 0;
        int addA = 0;
        int addB = 0;
 
        // 사용자 A만 충전소를 이용하는 경우
        if (a.size() >= 1 && b.size() == 0) {
            for (int i = 0; i < a.size(); i++) {
                int chargeA = v[a[i]].p;
 
                if (res < chargeA) {
                    res = chargeA;
                    addA = chargeA;
                }
            }
        }
        // 사용자 B만 충전소를 이용하는 경우
        else if (a.size() == 0 && b.size() >= 1) {
            for (int i = 0; i < b.size(); i++) {
                int chargeB = v[b[i]].p;
 
                if (res < chargeB) {
                    res = chargeB;
                    addB = chargeB;
                }
            }
        }
        // 사용자 A,B 모두 충전소를 이용하는 경우
        else {
            for (int i = 0; i < a.size(); i++) {
                for (int j = 0; j < b.size(); j++) {
                    int chargeA = v[a[i]].p;
                    int chargeB = v[b[j]].p;
                    // 넣은 것중에서 가장 큰 경우의 수 찾아서 넣어준다.
                    if (a[i] == b[j]) {
                        chargeA /= 2;
                        chargeB /= 2;
                    }
 
                    if (res < chargeA + chargeB) {
                        res = chargeA + chargeB;
                        addA = chargeA;
                        addB = chargeB;
                    }
                }
            }
        }
 
        ax += dx[A[t + 1]];
        ay += dy[A[t + 1]];
        bx += dx[B[t + 1]];
        by += dy[B[t + 1]];
        // 위치 이동
        ac += addA;
        bc += addB;
        // 값을 더해준다.
    }
 
    return ac + bc;
}
 
int main() {
    cin >> tc;
    for (int k = 1; k <= tc; k++) {
        cin >> M >> Bc;
        for (int i = 1; i <= M; i++) {
            cin >> A[i];
        }
        for (int i = 1; i <= M; i++) {
            cin >> B[i];
        }
        v.clear();
        for (int i = 0; i < Bc; i++) {
            cin >> col >> row >> size2 >> charge;
            v.push_back({ row,col,size2,charge });
        }
        int Sol = go();
        cout << "#" << k << " " << Sol << "\n";
    }
    return 0;
}