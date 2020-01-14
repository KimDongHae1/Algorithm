//stack을 직접 구현해본다.
#include <iostream>

using namespace std;

// S.create(y) 크기가 y인 스택을 만들어라
// S.push(y) y를 넣어라
// S.pop() 맨 위에것 지워주기
// S.top() 맨 위에것 출력하기
// S.size() 원소의 갯수 출력하


//       0 1 2 3 4 5 6 7 8 9
// data  7 8 9 1 2
// 배열을 이용해 구현한다.

struct Stack{
    int data[100];
    int len = 0;
    int capacity = 0;

    void create(int y){
        capacity = y;
    }
    void push(int y){
        //    0 1 2 3 4 5
        //    1 2 3
        // 이미 못넣은 수준으로 됬을 경우를 생각해야한다.
        if (len >= capacity){
            cout << "Overflow" << "\n";
        }
        else {
            data[len++] = y;
        }
    }
    void pop(){
        if (len <= 0){
            cout << "Underflow" << "\n";
        }
        else{
            data[len - 1] = 0;
            len--;
        }
    }

    int top(){
        // 스택의 가장 위에있는 수를 반환한다.
        // 스택에 아무것도 없을경우 -1을 반환한다.

        if (len <= 0){
            return -1;
        }
        else {
            return data[len - 1];
        }
    }
    int size(){
        return len;
    }
};

int N; // stack의 크기
int M; // 연산의 갯수
int p;
int y;
int main(){
    cin >> N >> M;
    Stack s1;
    s1.create(N); // n의 크기의 스택을 만들었다.
    for (int i = 0 ; i < M ; i ++){
        cin >> p;
        if (p == 1){
            cin >> y;
            s1.push(y);
        }
        else if (p == 2){
            s1.pop();
        }
        else if (p == 3){
           if (s1.top() == -1){
               cout << "NULL" <<"\n";
           }
           else {
               cout << s1.top() <<"\n";
           }
        }
    }
    return 0;
}