#include <iostream>
#include <queue>
#include <vector>
#include <memory.h>
#define MAX 101
using namespace std;

struct point{
    int x;
    int y;
};

int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};


char str[MAX][MAX];
int map[MAX][MAX];
bool visit[MAX][MAX] = {false,};

int R,C,N;

queue<point> queue1;
vector<point> v;

bool flag=false;

void printAll(int a[][MAX]){
    cout<<"\n"<<"==========================================="<<"\n";
    for(int i=0; i<R; i++){
        for(int j=0;j<C; j++){
            cout<<map[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void bfs(int x, int y,int cnt){
    visit[x][y]=true;
    queue1.push({x,y});

    while(!queue1.empty()){
        int currentX = queue1.front().x;
        int currentY = queue1.front().y;
        visit[currentX][currentY]=true;

        queue1.pop();

        if(currentX==R-1){
            flag=true;
        }

        for(int i=0;i<4;i++){
            int nx = currentX+dx[i];
            int ny = currentY+dy[i];

            if(nx>=0&&nx<R && ny>=0&&ny<C){
                if(!visit[nx][ny] && map[nx][ny]!=0){
                    queue1.push({nx,ny});
                }
            }
        }
    }
}

void down(int cnt){
    v.resize(0);
    for(int i=0; i<R; i++) {
        for (int j = 0; j < C; j++) {
            if (visit[i][j]) {
                v.push_back({i, j});
            }
        }
    }

    bool flag2 = false;
    
    for(int i=0; i<v.size(); i++){
        map[v[i].x][v[i].y] = 0;
    }

    for (int k = 1; k <= R; k++) {
        for(int i=0; i<v.size(); i++){
            v[i].x+=1;
        }
        for(int i=0; i<v.size(); i++){
            if(map[v[i].x][v[i].y] == 1){
                flag2=true;
                break;
            }
        }
        if (flag2){
            for(int i=0; i<v.size(); i++){
                v[i].x-=1;
            }
            break;
        }
    }

    for(int i=0; i<v.size(); i++){
        map[v[i].x][v[i].y] = 1;
    }


}

int main(){
    cin>>R>>C;
    for(int i=0; i<R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> str[i][j];
            if (str[i][j] == '.') {
                map[i][j] = 0;
            } else {
                map[i][j] = 1;
            }
        }
    }
    cin >> N;
    int r;
    bool abs = false;
    while(N--) {

        cin >> r;
        r = R - r;
        memset(visit,false, sizeof(visit));
        if(!abs){
            for (int i = 0; i < C; i++) {
                if (map[r][i] == 0) continue;
                map[r][i] = 0;
                break;
            }
        }
        else{
            for (int i = C - 1; i >= 0; i--) {
                if (map[r][i] == 0) continue;
                map[r][i] = 0;
                break;
            }
        }
        // 창을 던지는 부
        // 그위에 있는 것들만 클러스 확인하면 되겠군!!!
        int cnt = 1;
        bool flag3=false;
        for (int i = 0; i <= r; i++) {
            for (int j = 0; j < C; j++) {
                if (!visit[i][j] && map[i][j] == 1 && !flag3) {
                    flag = false;
                    bfs(i, j, cnt);
                    if (!flag) {
                        flag3=true;
                        down(cnt);
                    }
                }
            }
        }

        if(!abs){
            abs=true;
        }
        else {
            abs=false;
        }

    }
    for(int i=0; i<R; i++){
        for(int j=0;j<C;j++){
            if(map[i][j]==0){
                cout<<".";
            }
            else {
                cout<<"x";
            }
        }
        cout<<"\n";
    }
    return 0;
}