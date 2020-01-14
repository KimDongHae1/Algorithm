// 점심식사 시간 (시뮬 + 최소 값 찾기)
// 차량정비소와 같이 queue를 잘 이용해야 하며 
// 각 상황을 순서대로 적어 코딩을 시작해야한다.
// BT 방법으로 모든 경우의 수를 다 본 후, 계단에 넣을지 말지등을 결정해야한다.
#include<iostream>
#include<memory.h>
#include<vector>
#include<queue>
 
#define MAX 11
 
using namespace std;
 
int tc;
 
int n;
int ans;
int map[MAX][MAX];
 
struct Node {
    int x;
    int y;
    int target;
    int value;
    Node(int _x, int _y) : x(_x), y(_y) {};
    Node(int _x, int _y, int _value) : x(_x), y(_y), value(_value) {};
};

vector<Node> node_vec; // 사람들의 위치
vector<Node> stair_vec; // 계단 위치
 
int distance(int n_idx, int s_idx) {
    int x = abs(node_vec[n_idx].x - stair_vec[s_idx].x);
    int y = abs(node_vec[n_idx].y - stair_vec[s_idx].y);
    return x + y;
}
 
void dfs(int idx) {
    if (idx == node_vec.size()) {
        int people_cnt = node_vec.size();
        int time = 0;
        int exit_cnt = 0;
	
        queue<int> waiting[2];
        queue<int> stair[2];
 
        // 각자 원하는 계단으로 가기 위한 거리 계산
        for (int i = 0; i < people_cnt; i++) {
            int dis = distance(i, node_vec[i].target);
            waiting[node_vec[i].target].push(dis); // 모든 사람들을 웨이팅에 넣어준다. 1번으로 갈지 2번으로 갈지 정해서
        }
 
        while (exit_cnt < people_cnt) {
            time++;
             
            // 계단에 있는 인원 내려가기
            for (int i = 0; i < 2; i++) {
                int size = stair[i].size();
                for (int j = 0; j < size; j++) {
                    int top = stair[i].front();
                    stair[i].pop();
                    top--;
                    if (top != 0) {
                        stair[i].push(top);
                    }
                    else {
                        exit_cnt++;
                    }
                }
            }
 
            // 계단에 인원 추가하기
            for (int i = 0; i < 2; i++) {
                int size = waiting[i].size();
                for (int j = 0; j < size; j++) {
                    int dis = waiting[i].front();
                    waiting[i].pop();
                    dis--;
                    if (dis <= 0) // 계단에 도착했다.
                    {
                        if (stair[i].size() < 3) { // 계단에 도착했지만 내려가는 인원이 Full
                            stair[i].push(stair_vec[i].value);
                        }
                        else {
                            waiting[i].push(dis); // 3보다 클 경우.
                        }
                    }
                    else {
                        waiting[i].push(dis);
                    }
                }
            }
        }
         
        if (ans > time + 1) {
            ans = time + 1;
        }
    }
    else {
        for (int i = 0; i < 2; i++) {
            node_vec[idx].target = i;
            dfs(idx + 1);
        }
		// 모든 경우의 수를 다 넣는다.
    }
}
 
int main() {
    cin >> tc;
 
    for (int k = 1; k <= tc; k++) {
        memset(map, 0, sizeof(map));
        node_vec.clear();
        stair_vec.clear();
        cin >> n;
        ans = 987987987;
 
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int temp;
                cin >> temp;
                if (temp == 1) {
                    node_vec.push_back(Node(i, j));
                }
                else if (temp > 1) {
                    stair_vec.push_back(Node(i, j, temp));
                }
            }
        }
        dfs(0);
        cout << "#" << k << " " << ans << '\n';
    }
}