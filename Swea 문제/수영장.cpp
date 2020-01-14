#include <iostream>
using namespace std;
 
int price[4];
int map[12];
int Sol;
int tc;
 
void dfs(int cnt, int sum) {
    if (cnt > 11) {
        if (Sol > sum) {
            Sol = sum;
            return;
        }
        else {
            return;
        }
    }
    if (map[cnt] == 0) {
        dfs(cnt + 1, sum);
        return; 
        // 수영을 하지 않으므로 그냥 무시하고 넘어간다.
    }
    dfs(cnt + 1, sum + (map[cnt] * price[0]));
    // 1일권으로만 계산한다.
    dfs(cnt + 1, sum + price[1]);
    // 1달권으로 계산한다.
    dfs(cnt + 3, sum + price[2]);
    // 3달권으로 계산한다.
 
}
 
int main() {
    cin >> tc;
    for (int k = 1; k <= tc; k++) {
        for (int i = 0; i < 4; i++) {
            cin >> price[i];
        }
        for (int i = 0; i < 12; i++) {
            cin >> map[i];
        }   
        Sol = price[3];
        dfs(0, 0);
        cout << "#" << k << " " << Sol << "\n";
    }
    return 0;
}