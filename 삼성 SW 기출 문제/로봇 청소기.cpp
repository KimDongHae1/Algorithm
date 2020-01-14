// 로봇청소기(DFS)
// dfs를 돌리면서 모든 경우의 수를 다 넣어줘서 다 생각하게 만든다.
// dfs문제의 아주 좋은 예.
#include <iostream>

using namespace std;

const int MAX = 51;

// 바라보는 방향(북, 동, 남, 서)
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};

// 바라보는 방향에 따른 후진 (남, 서, 북, 동)
int back_dx[4] = { 1,0,-1,0 };
int back_dy[4] = { 0,-1,0,1 };

int ans=0; // 로봇청소기가 청소하는 칸의 개수
int map[MAX][MAX];
int N;
int M;// 영역의 크기
int r;// 로봇의 행 위치.
int c;// 로봇의 열 위치.
int d; // 로봇의 방향.

void printAll(){
    cout<<"========================================================="<<"\n";
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cout<<map[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void dfs(int x, int y, int dir)
{
    // 벽이면 끝
//    printAll();
    if (map[x][y] == 1) return;

    // 빈 칸이면 청소한다.
    if (map[x][y] == 0)
    {
        map[x][y]=2;
        ans++;
    }

    // 네 방향 검사
    for (int k = 0; k < 4; k++)
    {

        int nDir;
        if (dir ==0){
            nDir=3;
        }
        else {
            nDir =  dir-1;
        }
        // 계속하여 왼쪽 방향으로 간다.
        int nx = x + dx[nDir];
        int ny = y + dy[nDir];

        // 빈 칸이면 청소
        if (map[nx][ny] == 0)
        {
            dfs(nx, ny, nDir);
            // 다음 칸으로 넘어간 경우에 더 이상 나머지 방향을 검사하지 않는다.
            return;
        }
            // 청소했거나 벽이면 방향만 바꿔준다.
        else
        {
            dir = nDir;
        }
    }
    // 검사 끝

    // 네 방향 모두 청소했거나 벽이면 방향을 유지한채로 후진한다.
    int nx = x + back_dx[dir];
    int ny = y + back_dy[dir]; // 더 이상 방향전환할 수 없을 때

    dfs(nx, ny, dir);
}

int main()
{
    cin >> N >> M >> r >> c >> d;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cin >> map[i][j];
        }
    }
    dfs(r, c, d);

    cout << ans << "\n";
    return 0;
}