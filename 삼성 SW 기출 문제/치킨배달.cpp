#include <iostream>
#include <vector>


#define MAX 51
using namespace std;
int N; // 마을의 크기.
int M; // 최대 치킨집의 갯수.
int map[MAX][MAX];
bool visit[MAX][MAX];
int memo[13][2];
int Min = 987987987;

vector <pair<int, int>> v1;
vector <pair<int, int>> v2;

int check() {
    int Sum = 0;
    for (int i = 0; i < v1.size(); i++) {
        int x1 = v1[i].first;
        int y1 = v1[i].second;
        int Min2 = 98798787;
        for (int j = 0; j < v2.size(); j++) {
            int x2 = v2[j].first;
            int y2 = v2[j].second;
            
            int sum = abs(x1 - x2) + abs(y1 - y2);
            if (Min2 > sum) {
                Min2 = sum;
            }
        }
        Sum += Min2;
    }
    // cout << Sum<<"\n"; 
    return Sum;
}

void Backtracking(int cnt, int dest) {
    if (cnt == dest) {
        // 계산 해주는 함수를 만들어 주면 된다. 
        v2.clear();
        for (int i = 0; i < dest; i++) {
            v2.push_back({ memo[i][0],memo[i][1] });
        }
        // for (int i = 0; i < dest; i++) {
        //  cout << v2[i].first << " " << v2[i].second << "\n";
        //}
        int sum = check();
        // cout << sum << "\n";
        if (Min > sum) {
            Min = sum;
        }
    }
    else {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (cnt == 0 && !visit[i][j] && map[i][j] == 2) {
                    memo[cnt][0] = i;
                    memo[cnt][1] = j;
                    visit[i][j] = true;
                    Backtracking(cnt + 1, dest);
                    visit[i][j] = false;
                }
                else if (!visit[i][j] && cnt > 0 && map[i][j] == 2) {
                    int before = memo[cnt - 1][0] * N + memo[cnt - 1][1];
                    int current = i * N + j;
                    if (before < current) {
                        memo[cnt][0] = i;
                        memo[cnt][1] = j;
                        visit[i][j] = true;
                        Backtracking(cnt + 1, dest);
                        visit[i][j] = false;
                    }
                }
            }
        }
    }
}

int main() {
    cin >> N >> M ;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            if (map[i][j] == 1) {
                v1.push_back({ i,j });
            }
        }
    }
    Backtracking(0, M);
    cout << Min;
    return 0;
}