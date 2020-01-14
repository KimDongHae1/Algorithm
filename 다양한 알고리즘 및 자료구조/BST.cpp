// 재귀 호출을 구현할 수 있다.
// 재귀 호출로 binarySearch을 한 경우
#include <iostream>

using namespace std;

int arr[100];
int N;
int M;
int binarySearch(int arr[], int start , int end , int value){
    // arr의 start부터 end까지의 숫자에서 value의 숫자를 찾는 함수이다. 존재한다면 그 위치를 반환하고
    // 없다면 -1을 반환하는 함수이다.
    // 기저조건은 가장 단순한 경우. 숫자가 없을 경우가 가장 단순하다. arr에 value가 없다는 의미이다.
    if (start > end){
        return -1;
    }
    else if (start == end) {
        if (arr[start] == value) {
            return start;
        }
        else return -1;
    }
    else {
        int mid = (start + end) / 2;
        if (arr[mid] == value) return mid;
        else if(arr[mid] > value) return binarySearch(arr,start,mid,value);
        else return binarySearch(arr,mid+1,end,value);
    }

    // 반환해줄 때 인덱스를 반환해주면 된다.
}

int main(){
    cin >> N;
    for (int i = 0 ; i < N ; i ++){
        cin >> arr[i];
    }
    cin >> M; // 정렬이 되어 있다고 가정해야 한다.

    int inx = binarySearch(arr,0,N-1,M);

    if (inx == -1) {
        cout << "숫자가 없습니다." << "\n";
    }
    else{
        cout << "숫자는 " << inx << "에 있습니다"  << "\n";
    }
}