#include <iostream>

using namespace std;
// 선형 큐에서 조금 바꿔져서 하면 된다.
const int MAX = 100; // 의미를 주기 위해서 사용하는 것이다. 아주 중요하다.!!!
struct Queue{

    int data[MAX];
    int f , r;
    int capacity;
    int numElement;
    
    void create(int y){
        capacity = y;
        f = 0;
        r = 0;
        numElement = 0;
    }
    void push(int y){
        if (numElement >= capacity){
            cout << "Overflow"<<"\n";
        }
        else {
            data[r] = y;
            r = (r+1) % MAX; // 0 1 2 3 4 ~~~ 0 1 2 3 4 계속해서 돈다.
            numElement++;
        }
    }
    void pop(){
        if (numElement <= 0){
            cout << "Underflow" <<"\n";
        }
        else{
            data[f] = 0;
            f = (f+1) % MAX;
            numElement--;
        }
    }
    int front(){
        if (numElement <= 0 ){
            return -1;
        }
        else{
            return data[f];
        }
    }
    int size(){
        return numElement;
    }

};
int main(){
    Queue q1;
    q1.create(4);
    //배열의 범위를 넘어선다.
    //     1 2 3 4 5 6 7 8 9
    // data
    for (int i = 0 ; i < 10000 ; i ++){
        q1.push(i);
        q1.push(i+1);
        q1.push(i+2);
        q1.push(i+3);

        q1.pop();
        q1.pop();
        q1.pop();
        q1.pop();

    }

    q1.push(1);
    q1.push(2);

    cout << q1.front() <<"\n"; // 1

    q1.pop();

    cout << q1.front() <<"\n"; // 2

    q1.pop();



    return 0;
}