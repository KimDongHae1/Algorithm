#include <iostream>
// 우선순위 queue를 구현할 때 무조건 heap을 이용해서 구현한다.
using namespace std;
const int MAX = 100;
struct PriorityQueue{
    int data[MAX];
    int len = 1; // 원소의 맨 끝을 가리키고 있다.
    //      0 1 2 3 4 5 6 7
    // data
    void push(int x){
        data[len++] = x;

        int inx = len - 1;
        while (inx > 1){
            if (data[inx] < data[inx/2]){
                int temp = data[inx];
                data[inx] = data[inx/2];
                data[inx/2] = temp;
            }
            else {
                break;
            }
            inx = inx / 2;
        }
    }
    void pop(){
        data[1] = data[len - 1];
        data[len - 1] = 0;
        len--;

        int inx = 1;

        while(1){
            //1. 자식들 중에 우선순위가 높은 친구를 알아내야한다.
            //2. 나와 우선순위가 높은 친구를 비교해서 자리를 바꾸어야함.
            int pInx = -1; // 우선순위가 높은 친구의 노드 번호
            // 1, 자식이 모두 없는 경우
            // 2. 왼쪽 자식이 없는 경우
            // 3. 모든 자식이 존재하는 경우
            if (inx * 2  >= len) //자식이 모두 없는 경우를 나타낸 것이다. 더 이상 내려 갈 곳이 없다.
            {
                break;
            }
            else if (1 <= inx*2 && inx*2 < len && len <= inx*2+1){
                pInx = 2*inx;
            }
            else {
                if (data[inx * 2] < data[inx * 2 + 1]){
                    pInx = inx * 2;
                }
                else {
                    pInx = inx * 2 + 1;
                }
            }
            if (data[inx] > data[pInx]){
                int temp = data[inx];
                data[inx] = data[pInx];
                data[pInx] = temp;

                inx = pInx;
            }
            else {
                break;
            }
        }
    }
    int top(){
        return data[1];
    }
};

int main(){
    return 0;
}