// 나무제테크(시뮬레이션)
// 봄 여름 가을 겨울 순서대로 만들면 된다.
// 벡터에 벡터를 넣는것이 가능하다는 것을 알려준 문제.
#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 11

using namespace std;

int map[MAX][MAX];
int A[MAX][MAX];

int N, M, K;
int dy[8] = { -1,-1,-1,0,0,1,1,1 };
int dx[8] = { -1,0,1,-1,1,-1,0,1 };

struct tre{
    int x;
    int y;
    int age;
};

int main() {
    cin >> N >> M >> K;
    vector<int> tree[11][11]; //나무의 나이 정보

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++) {
            cin >> A[i][j];
            map[i][j] = 5;
        }
    }


    int x,y,age;
    for (int i = 0; i < M; i++) {
        cin >> x >> y >> age;
        tree[x-1][y-1].push_back(age);
    }

    while (K--) {

        vector<tre> die; //죽은 나무
        vector<tre> breeding; //번식 나무

        //봄
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (tree[i][j].size()==0) continue;
                vector<int> vec;

                sort(tree[i][j].begin(), tree[i][j].end());
                for (int k = 0; k < tree[i][j].size(); k++) {
                    age = tree[i][j][k];

                    if (map[i][j] >= age) {
                        map[i][j] -= age;
                        vec.push_back(age + 1);
                        if ((age + 1) % 5 == 0){
                            tre tree1;
                            tree1.x=i;
                            tree1.y=j;
                            tree1.age=age+1;

                            breeding.push_back(tree1);
                        }
                    }
                    else {
                        tre tree1;
                        tree1.x=i;
                        tree1.y=j;
                        tree1.age=age/2;
                        die.push_back(tree1);
                    }
                }
                tree[i][j] = vec; // 다시 초기화
            }
        }


        //여름(죽은 나무 양분 먹는다)
        for (int i = 0; i < die.size(); i++) {
            x = die[i].x;
            y = die[i].y;
            age = die[i].age;
            map[x][y] += age;
        }


        //가을(번식하는 나무)
        for (int i = 0; i < breeding.size(); i++) {

            x = breeding[i].x;
            y = breeding[i].y;

            for (int j = 0; j < 8; j++) {
                int nx = x + dx[j];
                int ny = y + dy[j];
                if (ny<0 || ny>=N || nx<0 || nx>=N) continue;
                tree[nx][ny].push_back(1);
            }
        }

        //겨울(양분 추가)
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                map[i][j] += A[i][j];
            }
        }
    }

    int Sol = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Sol += tree[i][j].size();
        }
    }

    cout << Sol << endl;
    return 0;
}
