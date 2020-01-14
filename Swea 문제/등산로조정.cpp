// 등산로 조정 
#include <iostream>
#include <vector>
#include <memory.h>
#define MAX 9
using namespace std;
 
int tc; // 테스트 케이스의 갯수.
int N; // 등산로 맵의 크기
int K; // 최대 공사 가능 깊이.
int MaxHe = -987;
 
int sol = -987;
 
int map[MAX][MAX];
bool visit[MAX][MAX] = {false,};
 
bool flag = false;
 
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
 
vector<pair<int,int>> v1; // 최고 높은 봉우리들의 위치를 가지고 있는 vector
 
void printAll(int a[][MAX]){
    cout<<"\n\n";
    for(int i=0; i<N;i++){
        for(int j=0;j<N;j++){
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }
}
 
void dfs(int x, int y, int cnt, int hei){
    visit[x][y] = true;
    // 중복방지를 위해 사용/
    for(int i=0; i<4;i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx>=0 && nx<N && ny>=0&&ny<N){
            // 범위안에 들어온다.
            if(!visit[nx][ny]){
                // 방문했나 안했나를 비교한다.
                if(hei > map[nx][ny]){
					// 지금 높이보다 낮은 곳을 찾아간다.
                    dfs(nx,ny,cnt+1,map[nx][ny]);
                }
                else if(hei<=map[nx][ny] && !flag){
					// 크고 공사를 안한경우.
                    if(hei > map[nx][ny]-K){
                        flag = true;
                        dfs(nx,ny,cnt+1,map[x][y]-1);
                        flag = false;
                    }
                }
 
            }
        }
    }
    if(sol < cnt){
        sol = cnt;
    }
	// 결과를 계속 바꿔준다.
    visit[x][y] = false;
	// 중복을 허용하기위해 사용.
}
 
 
void init(){
    for(int i=0; i<MAX; i++){
        memset(visit[i],false,MAX);
        memset(map[i],0,MAX);
    }
    v1.resize(0);
}
 
int main(){
    cin >> tc;
 
    for(int k=1; k<=tc; k++){
        cin>>N>>K;
        sol = -987;
        MaxHe = -987;
        init();
        // cout<<v1.size()<<"\n";
        for(int i=0; i<N;i++){
            for(int j=0; j<N;j++){
                cin>>map[i][j];
                if(MaxHe < map[i][j]){
                    MaxHe = map[i][j];
                }
				// 제일 높은 봉우리 찾는 부분.
            }
        }
        for(int i=0; i<N;i++){
            for(int j=0;j<N;j++){
                if(MaxHe==map[i][j]){
                    v1.push_back({i,j});
					//제일 높은 부분 vector에 넣는다.
                }
            }
        }

        // printAll(map);
        for(int i=0; i<v1.size(); i++){
            flag = false;
			// 그 가장 높은 위치에서 dfs시작.
            dfs(v1[i].first,v1[i].second,1,MaxHe);
        }
        cout<<"#"<<k<<" "<<sol<<"\n";
 
    }
    return 0;
}