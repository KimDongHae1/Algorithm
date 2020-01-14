#include <iostream>

using namespace std;

struct Queue{
    int data[100];
    int f , r;
    int capacity;
    void create(int y){
        capacity = y;
        f = 0;
        r = 0;
    }
    void push(int y){
        if (r >= capacity){
            cout << "Overflow"<<"\n";
        }
        else {
            data[r++] = y;
        }
    }
    void pop(){
        if (f >= r){
            cout << "Underflow" <<"\n";
        }
        else{
            data[f] = 0;
            f++;
        }
    }
    int front(){
        if (r - f <= 0 ){
            return -1;
        }
        else{
            return data[f];
        }
    }
    int size(){
        return r-f;
    }

};
int N; // Queue의 크기를 나타낸다.
int K; // 총 질문의 갯수를 나타낸다.
int choice;
int pushNumber;
int main(){
    cin >> N >> K;
    Queue q1;
    q1.create(N);
    for (int i = 0 ; i < K ; i ++){
        cin >> choice;
        if (choice == 1){
            cin >> pushNumber;
            q1.push(pushNumber);
        }
        else if (choice == 2){
            q1.pop();
        }
        else if(choice == 3){
            if (q1.front() == -1){
                cout << "NULL"<<"\n";
            }
            else{
                cout << q1.front() << "\n";
            }
        }
    }

}