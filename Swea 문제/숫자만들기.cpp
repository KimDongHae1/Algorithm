#include <iostream>
 
using namespace std;
 
int operation[13];
int Operator[4];
 
int op[13];
 
int tc; // 테스트 케이스 갯수.
int N; // 총 연산자의 갯수.
int Max = -987987897;
int Min = 987987897;
 
 
int check(){
    int sum=operation[0];
    for(int i=0; i<N-1; i++){
        if(op[i] == 0){
            sum += operation[i+1];
        }
        else if(op[i] == 1){
            sum -= operation[i+1];
        }
        else if(op[i] == 2){
            sum *= operation[i+1];
        }
        else if(op[i] == 3){
            sum /= operation[i+1];
        }
    }
    return sum;
}
 
void Backtracking(int cnt){
    if(cnt == N-1){
        // 계산
       int sol = check();
       if(Max < sol)
       {
           Max = sol;
       }
 
       if(Min > sol){
           Min = sol;
       }
    }
    else {
        for(int i=0; i<4; i++){
            if(Operator[i] != 0){
                Operator[i]--;
                op[cnt] = i;
                Backtracking(cnt+1);
                op[cnt] = -1;
                Operator[i]++;
            }
        }
    }
}
 
int main(){
    cin >> tc;
 
    for(int k=1; k<=tc; k++){
        cin >> N;
        Max = -987987987;
        Min = 987987987;
        for(int i=0; i<4; i++){
            cin>>Operator[i];
        }
        for(int i=0; i<N;i++){
            cin>>operation[i];
        }
        // 배열에 모든 경우의 수가 들어왔다.
 
        Backtracking(0);
 
        cout<<"#"<<k<<" "<<Max-Min<<"\n";
    }
    return 0;
}