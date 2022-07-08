//22000690 정이주
// 강의 slide: ch16 page 6 ~ 15, ch15 page 33
// blog: https://twpower.github.io/71-use-sort-and-stable_sort-in-cpp, https://modoocode.com/304, https://www.delftstack.com/ko/howto/cpp/find-max-value-in-array-in-cpp/,
// https://ansohxxn.github.io/algorithm/dp/, https://ya-ya.tistory.com/101
// My program works for Greedy and Dynamic Programming.

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#define SEED 408  

using namespace std;

// structure for activity
struct activity{
    int start;
    int finish;
} activity;

// structure for selection activity in DP
struct c{
    int count;
    int k;
} c;

int compare(struct activity a, struct activity b); // To sort according to increasing finish times.
void Greedy(struct activity arr[], int n); // Greedy approach
void DP(struct activity arr[], int n); // Dynamic Programming approach


int compare(struct activity a, struct activity b){
    return a.finish < b.finish;
}


int main() {
    cout << "----------------------------------------------------------------\n" << endl;
    cout << "   Number   |           Execution time in microseconds          \n" << endl;
    cout << "  of jobs   |      Greedy      |       Dynamic Programing       \n" << endl;
    cout << "----------------------------------------------------------------\n" << endl;
    
    int jobs[5] = {10, 100, 1000, 10000, 100000};
    srand((int)SEED);
    // To print the execution time at once.
    clock_t GT;
    clock_t DPT;
    clock_t gtime_arr[5] = {0}; 
    clock_t dptime_arr[5] = {0}; 



    for(int i = 0; i < 5; i++){  // Execute All the jobs
        // To calculate the execution time
        clock_t start_D = 0, end_D = 0; 
        clock_t start_G = 0, end_G = 0;
        int js = jobs[i];
        int range = js * 10;
        struct activity arr[js+1];
        // Initialize the index 0 activity start & finish time
        arr[0].finish = 0;
        arr[0].start = 0;


        for(int j = 1; j < js+1; j++){
            arr[j].start = rand() % range;
            int ft = rand() % range;
            while(1){
                if(ft >= arr[j].start){ // check the finish time is bigger than start time.
                    arr[j].finish = ft;
                    break;
                }
                else{
                    ft = rand() % range;
                }

            }
        }

        start_G = clock();
        Greedy(arr, js+1);
        end_G = clock();

        GT = end_G - start_G;
        gtime_arr[i] = GT;

        if (js != 100000){
            start_D = clock();
            DP(arr, js+1);
            end_D = clock();
        }
        
        DPT = end_D - start_D;
        dptime_arr[i] = DPT;
        //cout << "         "<< js <<" |          "<< GT << "      |       "<< DPT <<"       \n" << endl;

    }

    cout << "         10 |          "<< gtime_arr[0] << "      |       "<< dptime_arr[0] <<"       \n" << endl;
    cout << "        100 |         "<< gtime_arr[1] << "      |       "<< dptime_arr[1] <<"      \n" << endl;
    cout << "       1000 |        "<< gtime_arr[2] << "      |       "<< dptime_arr[2] <<"       \n" << endl;
    cout << "      10000 |       "<< gtime_arr[3] << "      |       "<< dptime_arr[3] <<"       \n" << endl;
    cout << "     100000 |      "<< gtime_arr[4] << "      |       "<< "XXXXXXX" <<"      \n" << endl;
    cout << "----------------------------------------------------------------\n" << endl;

}

void Greedy(struct activity arr[], int n){
    sort(arr, arr + n, compare);
    int j = 1;
    for(int i = 2; i < n; i++){ // Since the first activity is naturally selected, then the next activity and the first activity are compared.
        if(arr[i].start >= arr[j].finish){
            j = i;
        }
    }
    
}

// DP code를 다시 작성하였습니다.
void DP(struct activity arr[], int n){
    sort(arr, arr + n, compare);
    // allocate 2D array
    int **m = new int*[n];
    for(int i = 0; i < n; i++){
        m[i] = new int[n];
    }

    // 쓰지 않는 부분 0으로
    for(int i = 0; i < n; i++){
        for(int j = 0; j < i; j++){
            m[i][j]=0;
        }
       
    }

    // initialize
    for(int i = 0; i < n; i++){
        m[i][i+1]=0;
    }

    for(int l = 1; l <= n; l++){
        for(int i = 0; i < n-l+1; i++){
            int j = i + l;
            m[i][j] = 0;
            for(int k = i+1; k < j; k++){
                if(arr[i].finish >= arr[j].start){  // 공집합인 경우
                    m[i][j] = 0;
                }
                else if(arr[i].finish <= arr[k].start && arr[k].finish <= arr[j].start){
                    if(m[i][j] < (m[i][k] + m[k][j] + 1)){
                        m[i][j] = m[i][k] + m[k][j] + 1;
                    }
                }
            }
        } 
    }

    for(int i = 0; i < n; i++){
        delete[] m[i];
    }
    delete[] m;

}
