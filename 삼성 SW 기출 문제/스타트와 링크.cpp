// 1. 절반으로 팀을 나눈다. 모든 경우의 수 확인
// 2. Backtracking을 사용해 모든 경우의 수 확인
// 3. 나눈 팀의 총 합을 구한 다음에 차를 구한다.
#include <iostream>

using namespace std;
const int MAX=21;
int Soccer[MAX][MAX];
bool visit[MAX]= {false,};
bool visit2[MAX] = {false,};
int start[MAX];
int link[MAX];
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
        int sum = Soccer[s2[0]][s2[1]] + Soccer[s2[1]][s2[0]];
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

void coulink(bool arr[MAX]){
    int cnt=0;
    for(int i=1; i<=N; i++){
        if(!arr[i]){
            link[cnt]=i;
            cnt++;
        }
    }
}
// 두 개의 팀을 나누는 Backtracking
void Backtracking(int a){
    if(N/2==a){
        coulink(visit);
//        cout<<"start"<<"\n";
//        printAll(start);
//        cout<<"link"<<"\n";
//        printAll(link);
        sum2=0;
        sum(0,start);
        int startsum = sum2;
        sum2=0;
        sum(0,link);
        int linksum =sum2;
        if(abs(startsum-linksum)<Min){
            Min=abs(startsum-linksum);
        }
        return;
    }
    else{
        for(int i=1; i<=N; i++){
            if(!visit[i] && start[a-1] < i){
                visit[i]=true;
                start[a]=i;
                Backtracking(a+1);
                start[a]=0;
                visit[i]=false;
            }
        }
    }
}

int main(){
    cin>>N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin>>Soccer[i][j];
        }
    }
    Backtracking(0);
    cout<<Min/2;
    return 0;
}
