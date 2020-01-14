// 드래곤 커브.
// 규칙을 찾아야 하는 문제. 
#include <iostream>
#include <memory.h>

#define MAX 101

using namespace std;

int dx[4]={1,0,-1,0};
int dy[4]={0,-1,0,1};

int map[101][101];

int N;

int curve_size=0;
int curve[1024]={0,};

int main(){
    cin>>N;
    for(int i=0;i<N;i++){

        curve_size=0;
        memset(curve,0,sizeof(curve));

        int x,y,dir,g;
        cin>>x>>y>>dir>>g;

        curve[curve_size++] = dir;
        map[y][x]=1;


        for(int j=0;j<g;j++){
            for(int k = curve_size-1; k>=0; k--){
                curve[curve_size] = (curve[k]+1) % 4;
                curve_size++;
            }
        }

        for(int j=0;j<curve_size; j++){
            y+=dy[curve[j]];
            x+=dx[curve[j]];
            if(y<0 || y>MAX || x < 0 || x > MAX) continue;
            map[y][x]=1;
        }
    }
    int Sol = 0;
    for(int j=0; j<MAX;j++){
        for(int k=0; k<MAX; k++){
            if(map[j][k] && map[j+1][k] && map[j][k+1] && map[j+1][k+1]){
                Sol++;
            }
        }
    }
    cout<<Sol;
    return 0;
}