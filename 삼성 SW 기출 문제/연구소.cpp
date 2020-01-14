// 연구소 (BT+BFS)
#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>
#define MAX 9
using namespace std;

int map[MAX][MAX];
int temp[MAX][MAX];
bool visit[MAX][MAX] = {false,};
int N;
int M;

int Maxx=-987987;

struct point{
    int x;
    int y;
};

int memo[3][2];

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

queue<point> q;
vector<point> v;

void printAll(int a[][MAX]){
    cout<<"======================================================="<<"\n";
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void bfs(){
    for(int i =0; i<v.size(); i++){
        q.push({v[i].x,v[i].y});
    }
    while(!q.empty()){
        int currentX = q.front().x;
        int currentY = q.front().y;

        q.pop();

        for(int i=0; i<4; i++){
            int nx = currentX+dx[i];
            int ny = currentY+dy[i];

            if(nx>=0&&nx<N && ny>=0&&ny<M){
                if(!visit[nx][ny] && map[nx][ny] == 0){
                    map[nx][ny] = 2;
                    visit[nx][ny]=true;
                    q.push({nx,ny});
                }
            }
        }
    }
}

void check(){
    int cnt=0;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++) {
            if (map[i][j] == 0) {
                cnt++;
            }
        }
    }
    if(Maxx < cnt){
        Maxx = cnt;
    }
}

void init(){
    memset(visit,false, sizeof(visit));
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            map[i][j] = temp[i][j];
        }
    }
}

void BT(int cnt){
    if(cnt==3){

        for(int i=0; i<3; i++){
            map[memo[i][0]][memo[i][1]]=1;
        }
        bfs();
        check();
        init();
    }
    else{
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                if(map[i][j]!=0) continue;

                if(cnt==0){
                    memo[cnt][0]=i;
                    memo[cnt][1]=j;
                    BT(cnt+1);
                }
                else{
                    int x = memo[cnt-1][0];
                    int y = memo[cnt-1][1];
                    if(x*N+y < i*N+j){
                        memo[cnt][0]=i;
                        memo[cnt][1]=j;
                        BT(cnt+1);
                    }
                }
            }
        }
    }
}

int main(){
    cin >> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin>>map[i][j];
            temp[i][j]=map[i][j];
            if(map[i][j]==2){
                v.push_back({i,j});
            }
        }
    }

    BT(0);

    cout<<Maxx;
    return 0;
}