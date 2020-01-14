// 차량정비소(시뮬레이션)
// queue를 잘 이용해야하는 문제.

#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
 
int tc;
int ans;
int N, M, K, A, B;
 
int receptime[10];  // 접수대 걸리는 시간 저장
int repairtime[10]; // 정비소 걸리는 시간 저장
int arrive[1001]; // 처음 주어진 사람들이 접수대에 도착하는 시간
 
struct point {
    int num; // 들어온 사람 숫자.
    int time; // 걸리는 시간. 사람들에게 주어진 시간.
};
 
point recep[10]; // 들어가 있는 접수대 숫자, 들어간 사람의 숫자, 걸리는 시간 저장
point repair[10]; // 들어가 있는 정비대 숫자, 들어간 사람의 숫자, 걸리는 시간 저장
// 여기까지 접수대에 대한 정보
 
queue<int> recwait; // 접수대 들어가기 전에 사람들
queue<int> repwait; // 정비소 들어가기 전에 사람들
// 선입 선출을 사용하기위해 사용한다,
 
struct people {
    int rec; // 사용한 rec 숫자
    int rep; // 사용한 rep 숫자.
};
// 들어간 사람의 정보를 알려준다.
people person[1001]; // 사람이 거쳐간 곳을 저장합니다. 나중에 이결과를 토대로 정답 도출
 
int t;
int cnt;
 
void check() {
 
    while (1) {
 
        //도달하는 시간이 현재시간과 동일하면 rec 대기에 넣어주기
        for (int i = 1; i <= K; i++) {
            if (arrive[i] == t) {
                recwait.push(i);
            }
        }
 
        //접수대 끝난 사람 -> 정비실 대기 넣기
        for (int i = 1; i <= N; i++) {
            if (recep[i].num != 0 && recep[i].time == t) {
                repwait.push(recep[i].num);
                recep[i].num = 0;
            }
        }
     
        //정비실 끝난 사람 -> 끝난 사람 숫자 ++
        for (int i = 1; i <= M; i++) {
            if (repair[i].num !=0 && repair[i].time == t) {
                repair[i].num = 0;
                cnt++;
            }
        }
 
        //접수대 대기 -> 접수대 비어 있으면 넣기
        for (int i = 1; i <= N; i++) {
            if (recwait.empty()) {
                break;
            }
            if (recep[i].num == 0) {
                recep[i].num = recwait.front();
                recep[i].time = t + receptime[i];
                recwait.pop();
                person[recep[i].num].rec = i;
            }// 비어 있을 경우.
        }
 
 
        //정비실 대기 -> 정비실 비어 있으면 넣기
        for (int i = 1; i <= M; i++) {
            if (repwait.empty()) {
                break;
            }
            if (repair[i].num == 0) {
                repair[i].num = repwait.front();
                repair[i].time = t + repairtime[i];
                repwait.pop();
                person[repair[i].num].rep = i;
            }// 비어 있을 경우.
        }
 
        // 결과 확인
        if (K == cnt) {
            for (int i = 1; i <= K; i++) {
                if (person[i].rec == A && person[i].rep == B) {
                    ans += i;
                }
            }
            return;
        }
        t++;
    }
}
 
int main() {
    cin >> tc;
    for (int k = 1; k <= tc; k++) {
        cin >> N >> M >> K >> A >> B;
        ans = 0;
        t = 0;
        cnt = 0;
        for (int i = 1; i <= N; i++) {
            cin >> receptime[i];
        }
        for (int i = 1; i <= M; i++) {
            cin >> repairtime[i];
        }
        for (int i = 1; i <= K; i++) {
            cin >> arrive[i];
        }
        check();
        if (ans == 0) {
            ans = -1;
        }
        cout << "#" << k << " " << ans << endl;
    }
    return 0;
}