//22000690 정이주
// 강의 slide: ch8 page 14 ~ 21
// blog: https://coding-factory.tistory.com/666

#include <iostream>
#include <cstdlib>
# define seed 1024 // SEED
# define k 10 // K

using namespace std;
void CountingSort(int A[], int B[], int n);

int main(){
    int n = 0;
    
    //int Arr_A[1000] = {2, 5, 3, 0, 2, 3, 0, 3};
    int Arr_A[1000] = {0};  // 정렬 전 배열
    int Arr_B[1000] = {0};  // 정렬 후 배열
    
    cout << "input N: ";  // 배열 사이즈 입력
    cin >> n;

    srand((int) seed); // 랜덤 seed 
    for(int i = 0; i < n; i++){  // 배열에 랜덤으로 값 생성하여 저장
        Arr_A[i] = (rand() % (k+1)); // 0 ~ K 범위의 랜덤 수 생성
    }
    cout << "Befor CountSort: " << endl;
    for(int j = 0; j < n; j++){
        cout << "  " << Arr_A[j];
    }
    cout << endl;

    CountingSort(Arr_A, Arr_B, n);
}
void CountingSort(int A[], int B[], int n){
    int Count[k+1];

    for(int i = 0 ; i < k+1; i++){  // Count 배열 초기화
        Count[i] = 0;
    }

    for(int j = 0; j < n; j++){  // Counting
        Count[A[j]] = Count[A[j]] + 1;
    }

    for(int i = 1 ; i <= k; i++){ // Counting
        Count[i] = Count[i] + Count[i - 1];
    }

    for(int j = n-1; j >= 0; j--){ // Counting 결과로 배열을 정렬하여 정렬 후 저장할 배열에 값 저장
        Count[A[j]] = Count[A[j]] - 1;
        B[Count[A[j]]] = A[j];
    }

    cout << "After CountSort: " << endl;
    for(int j = 0; j < n; j++){
        cout << "  " << B[j];
    }
}