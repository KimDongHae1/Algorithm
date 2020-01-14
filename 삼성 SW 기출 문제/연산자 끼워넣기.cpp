#include <iostream>

using namespace std;

const int MAX=12;
int N;
int operation[4];
int Operator[MAX];
char stri[MAX];

int Max = -987897987;
int Min = 987897987;

int result(int arr[MAX],char str[MAX]){
    int sum = arr[0];
//    cout<<"sum : " << sum <<"\n";
    for(int i=0; i<N-1; i++){
        if(str[i] == '+'){
            sum=sum+arr[i+1];
        }
        else if(str[i] == '-'){
            sum=sum-arr[i+1];
        }
        else if(str[i] == '*'){
            sum=sum*arr[i+1];
        }
        else {
            sum=sum/arr[i+1];
        }
    }
    return sum;
}

void backtracking(int a){
    if(a==N-1){
        int solution = result(Operator,stri);
//        cout<<"solution : " << solution<<"\n";
        if(Max<solution){
            Max=solution;
        }
        if(Min>solution){
            Min=solution;
        }
    }
    else {
        for(int i=0; i<4; i++){
            if(operation[i]!=0){
                if(i==0){
                    stri[a] = '+';
                    operation[i]--;
                    backtracking(a+1);
                    operation[i]++;
                    stri[a] = 'q';
                }
                else if (i==1){
                    stri[a] = '-';
                    operation[i]--;
                    backtracking(a+1);
                    operation[i]++;
                    stri[a] = 'q';
                }
                else if(i==2){
                    stri[a] = '*';
                    operation[i]--;
                    backtracking(a+1);
                    operation[i]++;
                    stri[a] = 'q';
                }
                else{
                    stri[a] = '/';
                    operation[i]--;
                    backtracking(a+1);
                    operation[i]++;
                    stri[a] = 'q';
                }
            }
        }
    }

}

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> Operator[i];
    }
    for (int i = 0; i < 4; i++) {
        cin >> operation[i];
    }


    backtracking(0);

    cout<<Max<<"\n";
    cout<<Min<<"\n";

}