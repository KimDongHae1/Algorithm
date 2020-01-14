//테트로미노(DFS,시뮬레이션)
// ㅗ,ㅏ,ㅜ,ㅓ 방향은 DFS로 구현을 못한다.
#include <iostream>
#include <algorithm>

#define MAX 500

using namespace std;

int map[MAX][MAX];
bool visit[MAX][MAX];

int N,M;
int maxx=-908089;
int Sol = 0;

int dx[] = {0,0,-1,1};
int dy[] = {1,-1,0,0};
int sum=0;

//DFS를 할 수 있는 경우의 도형들

void dfs(int x, int y, int cnt){

    if(cnt==4){
        if(maxx<sum){
           // printAll(visit);
            maxx=sum;
        }
        return;
    }
    else {
        for(int i=0; i<4; i++){
            int nx= x+dx[i];
            int ny= y+dy[i];
            if(nx>=0&&nx<N && ny>=0&&ny<M && !visit[nx][ny]){
                visit[nx][ny]=true;
                sum+=map[nx][ny];
                dfs(nx,ny,cnt+1);
                sum-=map[nx][ny];
                visit[nx][ny]=false;
            }
        }
    }

}

void bfs(int x,int y){
    int summ=0;
    if(x+1<N && y+2<M){
        summ = map[x][y] + map[x][y+1] + map[x][y+2] + map[x+1][y+1];
        if(maxx<summ){
            maxx=summ;
        }
    }
    if(x-1>=0 && y+2<M){
        summ = map[x][y] + map[x][y+1] + map[x][y+2] + map[x-1][y+1];
        if(maxx<summ){
            maxx=summ;
        }
    }

    if(x+2<N && y-1>=0){
        summ = map[x][y] + map[x+1][y-1] + map[x+2][y] + map[x+1][y];
        if(maxx<summ){
            maxx=summ;
        }
    }

    if(x+2<N && y+1<M){
        summ = map[x][y] + map[x+1][y+1] + map[x+2][y] + map[x+1][y];
        if(maxx<summ){
            maxx=summ;
        }
    }
}

int main(){
    cin >>N >>M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin>>map[i][j];
        }
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            visit[i][j]=true;
            sum+=map[i][j];
            dfs(i,j,1);
            sum-=map[i][j];
            visit[i][j]=false;
            bfs(i,j);
        }
    }

    cout<<maxx;
    return 0;
}