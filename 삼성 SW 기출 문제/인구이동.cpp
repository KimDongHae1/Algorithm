// 인구이동(BFS+시뮬레이션)

#include <iostream>
#include <queue>
#include <vector>
#include <memory.h>

#define MAX 52

using namespace std;

struct point{
    int x;
    int y;
};

int map[MAX][MAX];
bool visit[MAX][MAX];

int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};

int N; // map의 크기.
int L; //
int R;

vector<point> v;
queue<point> q;

void printAll(int a[][MAX]){
    cout<<"===================================================="<<"\n";
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void bfs(int x, int y){
    int sum=0;
    q.push({x,y});
    visit[x][y]=true;
    while(!q.empty()){
        int currentX = q.front().x;
        int currentY = q.front().y;
        int curSize = map[currentX][currentY];
        v.push_back({currentX,currentY});
        sum+=map[currentX][currentY];

        q.pop();

        for(int i=0; i<4; i++) {
            int nx = currentX + dx[i];
            int ny = currentY + dy[i];
            int nSize = map[nx][ny];
            if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                if (!visit[nx][ny] && abs(nSize-curSize)>=L && abs(nSize-curSize)<=R){
                    // 범위안에 들어온다.
                    visit[nx][ny]=true;
                    q.push({nx,ny});
                }
            }
        }
    }

    for(int i=0; i<v.size(); i++){
        map[v[i].x][v[i].y] = (sum/v.size());
    }

}

bool check(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            int curSize = map[i][j];

            for(int a=0; a<4; a++){
                int nx = i+dx[a];
                int ny = j+dy[a];
                int nSize = map[nx][ny];
                if(nx>=0&&nx<N && ny>=0&&ny<N){
                    if(abs(nSize-curSize)>=L && abs(nSize-curSize)<=R){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


int main(){
    cin >> N >> L >> R;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin>>map[i][j];
        }
    }
    int Sol=0;
    while(1){
        if(check()){
            Sol++;
            // 인구이동이 한번이라도 있을 경우
        }
        else {
            break;
        }
        // 더 이상 인구이동이 없을 경우 종료.
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if(!visit[i][j]){
                    bfs(i,j);
                    v.clear();
                }
            }
        }
        memset(visit,false, sizeof(visit));
    }
    cout << Sol;

    return 0;
}