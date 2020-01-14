#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
 
int N, ans, ans_temp;
int player[51][10]; //1회부터 n회까지 타자들의 성적을 기록
int player_temp[10];
bool visit[10] = { false , }; //next_permutation을 이용하여 모든 경우의 수를 고려하기위한 배열
int s[4]; //1루부터 홈까지 사람이 있는지 판단
int out_cnt;//아웃카운트
bool nex; //3아웃일 경우 중단시켜 주기위한 bool

int maxx = -987897987;

void game_go() {
    int start = 1; 
	ans = 0;
    for (int n = 1; n <= N; n++) // 이닝수
	{
        out_cnt = 0; // out_count
		nex = false; // 
        while (1) {
            for (int i = start; i <= 9; i++) { 
                int ss = player[n][player_temp[i]];
				// 타자가 할 것들.
				if (ss == 0) {
					//아웃이라면
					out_cnt++;
				}
                else if (ss == 1) {
                    if (s[3] == 1) {
                        s[3] = 0;
                        ans++;
                    }
                    for (int ss = 3; ss > 1; ss--) {
                        if (s[ss - 1] != 0) {
							//선수가 위치에 있다면
                            s[ss] = 1;
                            s[ss - 1] = 0;
                        }
                    }
					
                    s[1] = 1;
                }//1루타
                else if (ss == 2) {//2루타라면
                    if (s[3] == 1) {
                        s[3] = 0;
                        ans++;
                    }
                    if (s[2] == 1) {
                        s[2] = 0;
                        ans++;
                    }
                    if (s[1] == 1) {
                        s[1] = 0;
                        s[3] = 1;
                    }
                    s[2] = 1;
                }//2루타
                else if (ss == 3) {//3루타라면
                    for (int j = 1; j <= 3; j++) {
                        if (s[j] == 1) {
                            s[j] = 0;
                            ans++;
                        }
                    }
                    s[3] = 1;
                }//3루타

                else if (ss == 4) {//홈런이라면
                    for (int j = 1; j <= 3; j++) {
                        if (s[j] == 1) {
                            s[j] = 0;
                            ans++;
                        }
                    }
                    ans++;
                }//홈런

                if (out_cnt == 3) { //3아웃이라면
                    if (i + 1 == 10) {
                        start = 1;
                    }
					else {
						start = i + 1;
					}
                    for (int j = 1; j <= 3; j++) {
                        s[j] = 0;
                    }
                    nex = true;
                    break;
                }
            }
			if (nex) {
				break;
			}
            start = 1;
        }
    }
}
 
void scoree(int cnt) {
	if (cnt == 10) {
		//cout << "\n\n";
		player_temp[4] = 1;
	/*	for (int i = 1; i <= 9; i++) {
			cout << player_temp[i] << " ";
		}*/

		game_go();
		if (maxx < ans) {
			maxx = ans;
		}
	}
	else {
		if (cnt == 4) {
			scoree(cnt + 1);
		}
		for (int i = 2; i <= 9; i++) {
			if (!visit[i]) {
				visit[i] = true;
				player_temp[cnt] = i;
				scoree(cnt + 1);
				player_temp[cnt] = 0;
				visit[i] = false;
			}
		}
	}
}
int main() {
	cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= 9; j++) {
			cin >> player[i][j];
        }
    }
	ans = 0;
    scoree(1);
    cout << maxx;
}