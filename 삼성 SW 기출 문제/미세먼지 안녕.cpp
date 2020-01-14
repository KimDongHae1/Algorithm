// 미세먼지안녕(시뮬레이션)
// 배열 인덱스 확인 필수.

#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>
#define MAX 51

using namespace std;

int map[MAX][MAX];
int memo[MAX][MAX];
int R; // 행의 갯수.
int C; // 열의 갯수.
int T; // 몇 초후를 계산할 것인지.

int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};

struct point{
    int x;
    int y;
    int size;
};

vector<pair<int,int>> v;
queue<point> q;

int ax;
int ay;

int bx;
int by;

void printAll(int a[][MAX]){
    cout<<"========================================="<<"\n";
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void Diffusion(){
    while(!q.empty()){
        int cnt=0;
        int currentX = q.front().x;
        int currentY = q.front().y;
        int curSize = q.front().size;

        q.pop();

        for(int i=0; i<4; i++){
            int nx = currentX+dx[i];
            int ny = currentY+dy[i];
            int nSize = curSize/5;

            if(nx>=0&&nx<R && ny>=0&&ny<C){
                if(map[nx][ny] != -1){
                    memo[nx][ny] += nSize;
                    cnt++;
                }
            }
        }
        memo[currentX][currentY] += (curSize - (curSize/5)*cnt);
    }
}

void check(){
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            if(map[i][j] == -1) continue;
            map[i][j] = memo[i][j];
        }
    }
}

void que(){
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            if(map[i][j]==-1) continue;
            q.push({i,j,map[i][j]});
        }
    }
}

void transfer(){
    for(int i=ax-2 ; i>=0; i--){
        map[i+1][0] = map[i][0];
    }
    for(int i=1 ;i<C; i++){
        map[0][i-1] = map[0][i];
    }
    for(int i=1; i<=ax; i++){
        map[i-1][C-1] = map[i][C-1];
    }
    for(int i=C-2; i>=1; i--){
        map[ax][i+1] = map[ax][i];
    }
    map[ax][ay+1]=0;
    // 위에것 종료

    for(int i=bx+2; i<R; i++){
        map[i-1][0] = map[i][0];
    }
    for(int i=1; i<C; i++){
        map[R-1][i-1] = map[R-1][i];
    }
    for(int i=R-2; i>=bx; i--){
        map[i+1][C-1] = map[i][C-1];
    }
    for(int i=C-2; i>=1; i--){
        map[bx][i+1] = map[bx][i];
    }
    map[bx][by+1]=0;
}
// 이 돌리는 부분을 다시 확인필요함.

int main(){
    cin>>R>>C>>T;
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            cin>>map[i][j];
            if(map[i][j]==-1){
                v.push_back({i,j});
            }
            else if(map[i][j]!=0){
                q.push({i,j,map[i][j]});
            }
        }
    }

    ax = v[0].first;
    ay = v[0].second;

    bx = v[1].first;
    by = v[1].second;

    for(int i=0; i<T; i++){
        memset(memo,0, sizeof(memo));
        Diffusion();
        check();
        //printAll(map);
        transfer();
        //printAll(map);
        que();
    }

    int Sol=0;
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            if(map[i][j]==-1 || map[i][j]==0) continue;
            Sol+=map[i][j];
        }
    }
    cout<<Sol;
//    printAll(map);
    return 0;
}