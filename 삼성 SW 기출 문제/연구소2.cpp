// 연구소2 (시뮬레이션 + BFS)
// BT 방법을 사용해 모든 경우의 수에 바이러스를 심는다.
// BFS 방법으로 방안에 바이러스가 다 퍼지는 최단 시간을 체크한다.
#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#define MAX 51

using namespace std;

int map[MAX][MAX];
int temp[MAX][MAX];
bool check[MAX][MAX];
int N;
int M;

int dx[4] ={1,0,-1,0};
int dy[4] ={0,1,0,-1};

int minn=987987987;

struct point{
    int x;
    int y;
};

struct birus{
    int x;
    int y;
    int size;
};

vector<point> v; // 바이러스가 갈 수 있는 모든 위치 정보를 가지고 있다.
vector<point> v2; // 바이러스가 직접 들어갔다.
queue<birus> q;

void init(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            map[i][j] = temp[i][j];
        }
    }
    memset(check,false, sizeof(check));
}

void printAll(int a[][MAX]){
    cout<<"================================================="<<"\n";
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }
}

bool checks(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(map[i][j]==0){
                return false;
            }
        }
    }
    return true;
}

void bfs(){
    for(int i=0; i<v2.size(); i++){
        q.push({v2[i].x,v2[i].y,0});
        check[v2[i].x][v2[i].y]=true;
    }
    int maxx=-987;
    while(!q.empty()){
        int currentX = q.front().x;
        int currentY = q.front().y;
        int curSize = q.front().size;

        q.pop();

        if(maxx<curSize){
            maxx=curSize;
        }

        for(int i=0; i<4; i++){
            int nx = currentX+dx[i];
            int ny = currentY+dy[i];
            int nSize = curSize+1;
            if(nx>=0&&nx<N && ny>=0&&ny<N){
                if(!check[nx][ny] && map[nx][ny]==0){
                    check[nx][ny]=true;
                    map[nx][ny]=2;
                    q.push({nx,ny,nSize});
                }
            }
        }
    }

    if(maxx < minn && checks()){
        minn=maxx;
    }

}

void BT(int cnt){
    if(cnt==M){
        for(int i=0; i<v2.size(); i++){
            map[v2[i].x][v2[i].y] = 2;
        }
        bfs();
        init();
    }
    else {
        for(int i=0; i<v.size(); i++){
            if(cnt==0){
                v2.push_back({v[i].x,v[i].y});
                BT(cnt+1);
                v2.pop_back();
            }
            else {
                int x = v2[cnt-1].x;
                int y = v2[cnt-1].y;
                int xx = v[i].x;
                int yy = v[i].y;
                if(x*N+y < xx*N+yy){
                    v2.push_back({v[i].x,v[i].y});
                    BT(cnt+1);
                    v2.pop_back();
                }
            }
        }
    }
}

int main(){
    cin>>N>>M;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin>>map[i][j];
            if(map[i][j]==2){
                v.push_back({i,j});
                map[i][j]=0;
            }
            temp[i][j]=map[i][j];
        }
    }

    BT(0);

    if(minn>987987){
        cout<<-1;
    }
    else {
        cout<<minn;
    }
    return 0;
}