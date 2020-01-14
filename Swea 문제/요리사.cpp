// 1. 절반으로 팀을 나눈다. 모든 경우의 수 확인
// 2. Backtracking을 사용해 모든 경우의 수 확인
// 3. 나눈 팀의 총 합을 구한 다음에 차를 구한다.
#include <iostream>
#include <memory.h>
 
using namespace std;
const int MAX=21;
int yori[MAX][MAX];
bool visit[MAX]= {false,};
bool visit2[MAX] = {false,};
int A[MAX];
int B[MAX];
int s2[2];
int N;
int Min=987897897;
 
int sum2;
void printAll(int arr[MAX]){
    for(int i=0; i<N/2; i++){
        cout<<arr[i]<<" ";
    }
    cout<<"\n";
}
 
void sum(int a,int arr[MAX]){
    if(a==2){
        int sum = yori[s2[0]][s2[1]] + yori[s2[1]][s2[0]];
        sum2 += sum;
    }
    else {
        for(int i=0; i<N/2; i++){
            if(!visit2[arr[i]]){
                visit2[arr[i]]=true;
                s2[a]=arr[i]-1;
                sum(a+1,arr);
                s2[a]=0;
                visit2[arr[i]]=false;
            }
        }
    }
}
 
void coulink(bool arr2[MAX]){
    int cnt=0;
    for(int i=1; i<=N; i++){
        if(!arr2[i]){
            B[cnt]=i;
            cnt++;
        }
    }
}
// 두 개의 팀을 나누는 Backtracking
void Backtracking(int a){
    if(N/2==a){
        coulink(visit);
 
        sum2=0;
        sum(0,A);
        int startsum = sum2;
 
        sum2=0;
        sum(0,B);
        int linksum =sum2;
 
        if(abs(startsum-linksum)<Min){
            Min=abs(startsum-linksum);
        }
        return;
    }
    else{
        for(int i=1; i<=N; i++){
            if(!visit[i] && A[a-1] < i){
                visit[i]=true;
                A[a]=i;
                Backtracking(a+1);
                A[a]=0;
                visit[i]=false;
            }
        }
    }
}
 
void init(){
    memset(visit,false,MAX);
    memset(visit2,false,MAX);
    memset(A,0,MAX);
    memset(B,0,MAX);
    for(int i=0;i<N;i++){
        memset(yori[i],0,MAX);
    }
}
 
int main(){
    int T;
    cin>>T;
    for(int k=1; k<=T; k++){
        cin>>N;
        init();
        Min=98798789;
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                cin>>yori[i][j];
            }
        }
        Backtracking(0);
        cout<<"#"<<k<<" "<< Min/2<<"\n";
    }
    return 0;
}