// 홈방범서비스
// 운영비용을 초과하지 않으면서 최대로 많은 집을 서비스해줘라.

#include <iostream>
#include <memory.h>
#include <queue>
#include <vector>
#define MAX 21
 
using namespace std;
 
int map[MAX][MAX];
int Memo[MAX][MAX];
bool visit[MAX][MAX];
 
int Performance[51];
 
struct point{
    int x;
    int y;
};
 
queue<point>queue1;
 
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
 
int tc; // 테스트 케이스 갯수
int N; // 마을의 크기
int M; // 한 집안이 지불해야할 돈.
 
void printAll(int arr[][MAX]){
    cout<<"============================================="<<"\n";
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<"\n";
    }
}
 
void BFS(int x, int y){
    visit[x][y]=true;
    queue1.push({x,y});
    Memo[x][y]=0;
    while(!queue1.empty()){
        int currentX = queue1.front().x;
        int currentY = queue1.front().y;
        queue1.pop();
        for(int i=0;i<4;i++){
            int nx = currentX+dx[i];
            int ny = currentY+dy[i];
 
            if(nx>=0&&nx<N && ny>=0&&ny<N){
                if(!visit[nx][ny]){
                    visit[nx][ny]=true;
                    Memo[nx][ny] = Memo[currentX][currentY]+1;
                    queue1.push({nx,ny});
                }
            }
        }
    }
}
// 범위안에 들어오는 지 찾는다.
 
void init(){
    for(int i=0;i<N;i++){
        memset(visit[i],false,N);
        memset(Memo[i],0,N);
    }
}
 
 
int check(){
    int Max = -987987987;
    int sum=0;
    bool flag;
    int sol=-987987987;
    for(int k=1;k<=40; k++){
        int cnt=0;
        for(int i=0; i<N; i++) {
            for (int j = 0; j < N; j++) {
                if (Memo[i][j] < k && map[i][j] == 1) {
                    cnt++;
                }
            }
        }
        sum = (M*cnt)-Performance[k];
        if(0<=sum&&sol<cnt){
            Max = sum;
            sol = cnt;
        }
    }
    return sol;
}
// 값에 들어오는지 확인.
 
int main(){
    cin>>tc;
    for (int i=1;i<=50;i++){
        Performance[i] = i*i + (i-1)*(i-1);
    }
 
    for(int k=1; k<=tc; k++){
        cin>>N>>M;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                cin>>map[i][j];
            }
        }
 
        int M=-987987897;
 
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                BFS(i,j);
                if(M<check()){
                    M=check();
                }
                init();
            }
        }
 
        cout<<"#"<<k<<" "<<M<<"\n";
    }
    return 0;
}