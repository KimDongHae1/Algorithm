// 퇴사(DP)
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX= 16;

int t[MAX];
int p[MAX];
int dp[MAX];

int main()
{
    int N;
    int next;
    cin >> N;
    for (int i = 1;i <= N;i++) {
        cin >> t[i] >> p[i];
    }
    for (int i = N;i > 0;i--) {
        next = i + t[i];
        if (next > N + 1) {
            dp[i] = dp[i + 1];
        }
        else {
            dp[i] = max(dp[i + 1], dp[next] + p[i]);
        }
    }
    cout << dp[1] << endl;
    return 0;
}