// 원자 소멸 시뮬레이션
// 범위가 무제한이므로 일정 값을 잡아주어야 한다.
// 좌표와 배열의 좌표가 다르기 때문에 이 부분을 유의해서 풀어야 한다.
// bool 형을 이용해 죽었는지 살았는지 확인한다.
#include <iostream>
#include <vector>
#include <memory.h>
 
#define MAX 4001
 
using namespace std;
 
int tc;
int N;
 
int dx[4] = {0,0,-1,1};
int dy[4] = {1,-1,0,0};
// 배열을 이동시켰으므로, 움직이는 방향도 다르다. 0일 경우 오른쪽, 1일경우 왼쪽, 2일 경우 위, 3일경우 아래
int map[MAX][MAX];
 
struct micros{
    int x;
    int y;
    int dir;
    int size;
    bool live; //true면 살아있는거, false면 죽어있느거.
};
 
vector<micros> v;
 
int sum=0;
 
bool die(){
    for(int i=0; i<v.size(); i++){
        if(v[i].live){
            return false;
        }
    }
    return true;
}
// 모든 세포들이 죽었을 경우.
 
void move(){
    sum=0;
    while(1){
        int temp_ener = 0;
 
        if(die()){
            break;
        } // 1개 이하로 살아남을 경우 끝!
        // 살아남은 원자가 1개나 0개일 경우 종료.
        for (int i=0; i<v.size(); i++)
        {
            if (!v[i].live) continue;
            // 죽었으면 종료.
 
            int x = v[i].x;
            int y = v[i].y;
            int dir = v[i].dir;
 
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            // 범위를 벗어나 죽는 경우.
            if (nx>=0&&nx<MAX && ny>=0&&ny<MAX)
            {
                map[x][y] = 0;
                map[nx][ny] = map[nx][ny]+1;
                x = nx;
                y = ny;
                v[i].x = x;
                v[i].y = y;
                // 원자 위치 이동.
            }
            else
            {
                v[i].live = false;
                map[x][y] = 0;
            }
        }
        // 모든 원자들을 이동시킨다.

        for (int i=0; i<v.size(); i++)
        {
            if (!v[i].live) {
                continue;
            }
 
            int x = v[i].x;
            int y = v[i].y;
            // 범위를 벗어나 죽는 경우.
            if(map[x][y] >= 2){
                for(int j=0; j<v.size(); j++){
                    if(i==j) {
                        continue;
                    }
                    if(!v[j].live) {
                        continue;
                    }
 
                    int xx = v[j].x;
                    int yy = v[j].y;
 
                    if(x == xx && y == yy){
                        temp_ener = temp_ener + v[j].size;
                        v[j].live = false;
                    }
                }
                temp_ener = temp_ener + v[i].size;
                v[i].live=false;
                map[x][y] = 0;
            }
        }
		// 겹치는 원자들을 다 죽이고 에너지 더해준다.
        sum += temp_ener;
    }
}

 
void init(){
    N=0;
    sum=0;
    memset(map,0, sizeof(map));
    v.clear();
}
 
 
int main(){
    cin >> tc;
    for(int k=1; k<=tc; k++){
        init();
        cin >> N;
        for(int i=0; i<N; i++){
            int x,y,dir,size;
            cin >> x >> y >> dir >> size;
            x = (x + 1000) * 2;
            y = (y + 1000) * 2;
            micros m;
            m.x = x;
            m.y = y;
            m.dir = dir;
            m.size = size;
            m.live = true;
            v.push_back(m);
            map[x][y] = 1;
        }
 
        if (v.size() < 2)
        {
            cout << "#" << k <<" " << sum << "\n";
        }
        else {
            move();
            cout << "#" << k <<" " << sum << "\n";
        }
    }
    return 0;
}