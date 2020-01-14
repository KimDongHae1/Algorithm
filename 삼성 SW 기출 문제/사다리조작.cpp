// 사다리조작(BT)
// 입력을 처리해서 어떻게 사다리를 표현할 것인가?
// 입력된 사다리를 가지고 결과를 어떻게 체크할 수 있을까?
// 추가 할 수 있는 최대 사다리가 3개 뿐이 없기 때문에, 다해보면 된다/
#include <iostream>
using namespace std;
int n,m,k;
int ret;

int map[31][11];

bool check(){
    for(int i=0; i<=n; i++){
        int pos = i;
        for (int j=0; j<=k; j++){
            if(map[j][pos] == 1){
                pos++;
            }
            else if(map[j][pos-1] == 1){
                pos--;
            }
        }
        if (pos != i){
            return false;
        }
    }
    return true;
}

void dfs(int count, int x, int y){
    if(count>=ret) return;

    if(check()) {
        ret = count;
        return;
    }

    if(count==3) return ;

    for(int i=x; i<=k; i++){
        for(int j=y; j<n ;j++){
            if(map[i][j] == 0 && map[i][j-1] ==0 && map[i][j+1]==0) {
                map[i][j]=1;
                dfs(count+1,i,j);
                map[i][j]=0;
            }
        }
        y=1;
    }
}

int main(){
    cin>>n>>m>>k;

    int a,b;
    for(int i=0;i<m;i++){
        cin>>a>>b;
        map[a][b]=1;
    }
    ret=4;

    dfs(0,1,1);

    if(ret==4) ret = -1;
    cout<<ret;
    return 0;
}