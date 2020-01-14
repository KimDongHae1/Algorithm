#include <iostream>
#include <memory.h>

using namespace std;

char str[4][8];
int map[4][8];
bool visit[4]={false, };

int N;

int num;
int dir;

void printAll(int arr[][8]){
    for(int i=0;i<4;i++){
        for(int j=0;j<8;j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<"\n";
    }
}


void turn(int arr[8], int tur){
    if(tur == 1){
        int temp = arr[7];
        for(int i=6; i>=0; i--){
            arr[i+1] = arr[i];
        }
        arr[0] = temp;
    }
    else if(tur==-1){
        int temp = arr[0];
        for(int i=0; i<7; i++){
            arr[i] = arr[i+1];
        }
        arr[7] = temp;
    }
}


void Backtracking(int num, int wise){
    visit[num]=true;

    if(!visit[num-1] && num > 0 && (map[num][6] != map[num-1][2])){
        Backtracking(num-1,-1*wise);
    }

    if(!visit[num+1] && num < 3 && (map[num][2] != map[num+1][6])){
        Backtracking(num+1,-1*wise);
    }

    turn(map[num],wise);
}


int main(){
    for(int i=0;i<4;i++){
        for(int j=0;j<8;j++){
            cin>>str[i][j];
            map[i][j] =str[i][j]-48;
        }
    }
    cin>>N;

    for(int i=0;i<N;i++){
        for (int j=0;j<4;j++){
            visit[j]=false;
        }
        cin>>num>>dir;
        Backtracking(num-1,dir);
    }
 
    int sum=0;

    if(map[0][0]==1){
        sum+=1;
    }
    if (map[1][0]==1){
        sum+=2;
    }
    if(map[2][0]==1){
        sum+=4;
    }
    if (map[3][0]==1){
        sum+=8;
    }
    cout<<sum;
}