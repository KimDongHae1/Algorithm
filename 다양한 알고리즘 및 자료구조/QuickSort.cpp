#include <iostream>

using namespace std;

int N;
int arr[100];
int  getLeft(int arr[], int start , int end , int pivot , int result[]){
    // 또한 , 작거나 같은 원소의 갯수를 반환한다.
    // arr의 start부터 end까지의 숫자중에서 작거나 같은 값을 result에 채우는 함수이다. 채우기만 하면 된다.
    int inx = 0;
    for (int i = start ; i <= end ; i++){
        if (arr[i] <= pivot){
            result[inx++] = arr[i];
        }
    }
    return inx;
}
int getRight(int arr[] , int start , int end, int pivot , int result[]){
     // pivot 보다 큰 값을 result에 넣는다.

    int inx = 0;

    for (int i = start ; i <= end ; i++){
        if (arr[i] > pivot){
            result[inx++] = arr[i];
        }
    }
    return inx;
}

void quickSort(int arr[], int start , int end){
    // arr을 start부터 end까지 퀵정렬하는 함수.
    // left[]는 pivot보다 작은 값을 넣는다.
    // right[]는 pivot보다 큰 값을 넣는다.
    // 계속해서 줄어들고 결국은 기저조건에 맞게된다.

    if (start >= end) // 숫자가 하나밖에 없거나 아무것도 없을 경우 return 한다. 그 자체로 정렬이 되어있다.
    {
        return;
    }
    // 1번 pivot의 값을 정한다.
    int pivot = arr[start];
    int left[100] , right[100];

    int left_cnt = getLeft(arr , start + 1, end , pivot , left); // left를 넘겨주고 채워주면 된다.
    int right_cnt = getRight(arr , start + 1, end , pivot , right); // left를 넘겨주고 채워주면 된다.

    for (int i = 0 ; i < left_cnt ;i++){
        arr[start + i] = left[i];
    }
    arr[start + left_cnt] = pivot;
    for (int i = 0 ; i < right_cnt ; i++){
        arr[start + left_cnt + 1 + i] = right[i];
    } // 어느 위치에 어떤 것을 넣어야 하나 이 것이 중요하다!
    quickSort(arr, start, start + left_cnt - 1);
    quickSort(arr, start + left_cnt + 1 , end);
}

int main(){
    cin >> N;

    for (int i = 0 ; i < N ; i++){
        cin >> arr[i];
    }
    quickSort(arr, 0 , N - 1);

    for (int i = 0 ; i < N ; i++){
        cout << arr[i] << " ";
    }
}