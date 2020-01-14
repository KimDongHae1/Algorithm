// 낚시왕
// 배열의 최적화가 필요한 문제. 다시 돌아오는 부분을 찾아서 움직임을 최적화 시켜주어야 한다.
// 구조체 사용 필수.
// vector 사용 필수. 
#include <iostream>
#include <queue>

#define MAX 110
using namespace std;

typedef struct Shark{
    int x;
    int y;
    int s;
    int dir;
    int size;
}shark;

shark map[MAX][MAX];
queue<shark> q;

int dx[4]={-1,1,0,0};
int dy[4]={0,0,1,-1};

int xx[101];

int R;
int C;
int M;
vector<shark> v;
void printAll(shark arr[][MAX]){
    cout<<"======================================================================="<<"\n";
    for(int i=1;i<=R;i++){
        for(int j=1;j<=C;j++){
            cout<<arr[i][j].size<<" ";
        }
        cout<<"\n";
    }
}
int main(){
    cin>>R>>C>>M;

    for(int i=2; i<101; i++){
        xx[i]=(i-1)*2;
    }
    // 최적화 시키기 위해 필요한 배열.

    for(int i=0;i<M;i++){
        int x,y,s,dir,size;
        cin>>x>>y>>s>>dir>>size;
        map[x][y]={x,y,s,dir-1,size};
    }
    // 상어들을 map에 넣어준다.
   // printAll(map);
    int sum=0;

    for(int a=1; a<=C; a++){

        // 2. 잡아 먹는다.
        for(int j=1; j<=R; j++){
            if(map[j][a].size!=0){
                sum+=map[j][a].size;
                map[j][a].size=0;
                break;
            }
        }
//        printAll(map);
        // 3. 살아있는 상어들 vector에 넣는다.
        for(int j=1; j<=R; j++){
            for(int k=1; k<=C; k++){
                if (map[j][k].size != 0){
                    q.push({j,k,map[j][k].s,map[j][k].dir,map[j][k].size});
                    map[j][k].size=0;
                }
            }
        }
        // 남은 상어들 이동.
        while(!q.empty()){

            int x = q.front().x;
            int y = q.front().y;
            int s = q.front().s;
            int dir = q.front().dir;
            int size = q.front().size;
            q.pop();


            if (dir == 0 || dir == 1)
            {
                int ss = s % xx[R];
                for(int i=0; i<ss; i++){
                    int next = x + dx[dir];
                    if(1 > next || next > R){
                        dir = 1 - dir;
                    }
                    x += dx[dir];
                }
            }
            else if (dir == 2 || dir == 3)
            {
                int ss = s % xx[C];
                for(int i=0; i<ss; i++) {
                    int next = y + dy[dir];
                    if (1 > next || next > C) {
                        dir = 5 - dir;
                    }
                    y += dy[dir];
                }
            }
            if(map[x][y].size<size){
                map[x][y] = {x,y,s,dir,size};
            }
        }
    }
    cout<<sum;
    return 0;
}