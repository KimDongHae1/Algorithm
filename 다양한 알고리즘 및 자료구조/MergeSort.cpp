#include <iostream>

using namespace std;

int n;
int arr[100000];
void merging(int arr[] , int s1 , int e1 , int s2 , int e2){
    // 두개를 합치는 정렬.
    // 1 2 4 8   3 4 6 7
    // p         q 포인터를 두고 하면 편하다.
    // s1    e1  s2     e2
    // temp라는 배열을 하나 만들 것이다. 그리고 둘이를 비교하고 작은 값을 넣으면 된다.

    int p , q; // p와 q의 현재 최솟값을 가리키는 변수들
    int temp[100000];
    int temp_inx = 0; // temp에 넣는 인덱스

    p = s1;
    q = s2;

    while(p <= e1 && q <= e2){
        if (arr[p] <= arr[q]){
            temp[temp_inx++] = arr[p];
            p++;
        }
        else {
            temp[temp_inx++] = arr[q];
            q++;
        }
        // 두개 값을 비교해주면서 작은 것부터 채워 나간다.
    }
    // p 와 q 중에 하나가 나오면 나머지를 다 넣는다.
    if (p > e1){
        for(int i = q ; i <= e2 ; i++){
            temp[temp_inx++] = arr[i];
        }
    }

    else {
        for(int i = p ; i <= e1 ; i++){
            temp[temp_inx++] = arr[i];
        }
    }
    // temp에 있는 값을 다시 arr에 넣어준다.

    for (int i = s1 ; i <= e2 ; i++){
        arr[i] = temp[i - s1];
    }
    // 두개의 값을 다 넣어준다.
}
void mergeSort(int arr[] , int start , int end) // start부터 end의 숫자까지 정렬하는 함수이다.
{
    if(start == end) // 같다고 해도 상관없다. // 더이상 나눌 것이 없을 때 
    {
        return; // 아무것도 안한다. 그냥 반환만 한다.
    }
    else {
        int mid = (start+end) / 2;

        mergeSort(arr,start,mid); // 왼쪽 정렬
        mergeSort(arr,mid+1,end); // 오른쪽 정렬
        merging(arr,start,mid,mid+1,end); // 왼쪽 절반과 오른쪽 절반을 합치는 함수이다.
    }
}
int main (){
    cin >> n;

    for (int i = 0 ; i < n ; i ++){
        cin >> arr[i];
    }
    mergeSort(arr,0,n-1);
    // 0부터 n-1까지 
    for (int i = 0 ; i < n ; i++){
        cout << arr[i] << " ";
    }
    return 0;
}