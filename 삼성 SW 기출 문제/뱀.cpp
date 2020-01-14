// 뱀(시뮬레이션)
// 뱀의 움직이는 방향과 움직일 때마다 꼬리와 머리의 위치를 잘 조절해주면 된다.
#include <iostream>
#include <queue>
#include <vector>

#define MAX 101

using namespace std;

struct snake {
    int x;
    int y;
    int dir;
};

struct po{
    int time;
    char ch;
};

vector<po> v;

int N;
int K;
int L;

int map[MAX][MAX];
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};

queue<snake> head;
queue<snake> tail;

void printAll(int arr[][MAX]){
    cout<<"\n";
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<"\n";
    }
}

int main(){
    cin >> N >> K;
    for(int i=0; i<K; i++){
        int x,y;
        cin>>x>>y;
        map[x-1][y-1]=-1;
    }
    cin>>L;
    for(int i=0; i<L; i++){
        int s;
        char a;
        cin>>s>>a;
        po po1;
        po1.time = s;
        po1.ch = a;
        v.push_back(po1);
    }
    // 게임을 시작하기전에 모든 정보 입력.


    int time=0;

    map[0][0] = 1;

    head.push({0,0,0});
    tail.push({0,0,0});

    while(1){
        time++;
      //  printAll(map);
        int currentX = head.front().x;
        int currentY = head.front().y;
        int dir = head.front().dir;

        head.pop();

        int nx = currentX+dx[dir];
        int ny = currentY+dy[dir];

        for(int i=0; i<v.size(); i++){
            if(time == v[i].time){
                if(v[i].ch == 'L'){
                    if(dir==0){
                        dir=3;
                    }
                    else {
                        dir = dir-1;
                    }
                }
                else {
                    if(dir==3){
                        dir=0;
                    }
                    else {
                        dir=dir+1;
                    }
                }
            }
        }
        // 시간이 되어 방향을 바꿀 때.

        if(map[nx][ny] == 1){
            break;
        }
        // 자기몸에 부딪혔을 경우.
        if(nx<0||nx>=N || ny<0||ny>=N){
            break;
        }
        // 범위를 벗어났을 경우.

        tail.push({nx,ny,dir});
        // 꼬리에 추가.

        if(map[nx][ny] == 0){
            map[nx][ny] = 1; // 그 다음 부분을 채워준다.
            map[tail.front().x][tail.front().y]=0; // 꼬리를 지워준다.
            tail.pop();
            head.push({nx,ny,dir});
        }
        else if(map[nx][ny]==-1){
            map[nx][ny] = 1; // 그 다음 부분을 채워준다.
            head.push({nx,ny,dir});
        }
    }
    cout<<time;
    return 0;
}