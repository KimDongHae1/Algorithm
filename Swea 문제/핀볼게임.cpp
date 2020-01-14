// 핀볼게임(시뮬레이션)
// 5개의 도형이 오는 방향하고 보내는 방향을 제대로 설정해줘야한다.
// 블랙홀 혹은 자기 원래 위치에 왔을 때 게임을 종료한다.
// 최대 값 찾기.
// 웜홀 값을 입력받아 5개의 웜홈을 만들어 웜홀에 도착했을 때 다음 위치로 보내준다.
#include <iostream>
#include <vector>
#include <memory.h>
 
#define MAX 101
using namespace std;
 
int map[MAX][MAX];
 
int tc;
int N;
 
int StartX; // 시작 X좌표
int StartY; // 시작 Y좌표
 
int Max = -987987987;
 
 
int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};
 
struct point{
    int x;
    int y;
};
 
vector<point> v[11];
vector<point> start;
 
void printAll(int a[][MAX]){
    cout<<"==========================================="<<"\n";
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }
}
 
int check(int dir, int shape){
    if(shape == 1){
        if(dir==0) return 1;
        else if(dir==1) return 3;
        else if(dir==2) return 0;
        else if(dir==3) return 2;
    }
    else if (shape == 2){
        if(dir==0) return 3;
        else if(dir==1) return 0;
        else if(dir==2) return 1;
        else if(dir==3) return 2;
    }
    else if (shape == 3){
        if(dir==0) return 2;
        else if(dir==1) return 0;
        else if(dir==2) return 3;
        else if(dir==3) return 1;
    }
    else if (shape == 4){
        if(dir==0) return 1;
        else if(dir==1) return 2;
        else if(dir==2) return 3;
        else if(dir==3) return 0;
    }
    else if (shape == 5){
        if(dir==0) return 1;
        else if(dir==1) return 0;
        else if(dir==2) return 3;
        else if(dir==3) return 2;
    }
    return dir;
}
// 오는 위치를 받아 보내는 위치로 바꿔주는 함수.
void dfs(int x, int y, int dir, int score) {
    int nx = x + dx[dir];
    int ny = y + dy[dir];
 
    if (nx < 0 || ny < 0 || nx >= N || ny >= N) {
        int s = score * 2 + 1;
        if (Max < s) Max = s;
        return;
    }
	// 벽에 부딪혔을 경우. 왔던 길로 돌아가기 때문에 종료.
    else if (nx == StartX && ny == StartY) {
        if (Max < score) Max = score;
        return;
    }
	// 다시 원위치로 돌아오기 때문에 종료.
    else if (map[nx][ny] == 0) {
        dfs(nx, ny, dir, score);
    }
	// 0이면 넘어간다.
    else if (map[nx][ny] > 0 && map[nx][ny] < 6) {
        dir = check(dir,map[nx][ny]);
        dfs(nx, ny, dir, score + 1);
    }
	// 벽을 만났을경우 값을 바꿔준다.
    else if (map[nx][ny] > 5 && map[nx][ny] < 11) {
 
        int ab = map[nx][ny];
        int xx = nx;
        int yy = ny;
             
        if(xx == v[ab][0].x && yy == v[ab][0].y){
            nx = v[ab][1].x;
            ny = v[ab][1].y;
        }
        else{
            nx = v[ab][0].x;
            ny = v[ab][0].y;
        }
         
        dfs(nx, ny, dir, score);
    }
	//웜홀을 만났을 경우 위치 바꿔준다.
 
    else if (map[nx][ny] == -1) {
        if (Max < score) Max = score;
        return;
    }
	// 블랙홀을 만나면 종료
 
}
 
void init(){
    memset(map, 0, sizeof(map));
    Max = 0;
    start.clear();
    for(int i=0; i<11; i++){
        v[i].clear();
    }
}
 
int main(){
    cin >> tc;
    for(int k=1; k<=tc; k++){
        cin >>N;
        init();
 
        for(int i=0; i<N; i++){
            for(int j=0;j<N;j++){
                cin>>map[i][j];
                if(map[i][j] > 5){
                    v[map[i][j]].push_back({i,j});
                }
                else if(map[i][j] == 0){
                    start.push_back({i,j});
                }
            }
        }
 
        for (int i = 0; i < start.size(); i++) {
            for (int j = 0; j < 4; j++) { //dir
                StartX = start[i].x;
                StartY = start[i].y;
                dfs(StartX, StartY, j,0);
            }
        }
            
        cout<<"#"<<k<<" "<<Max<<"\n";
//      printAll(map);
    }
    return 0;
}