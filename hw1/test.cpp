//22000690 정이주
// 강의 slide ch6 page 10, 20, 26
// 21-1 학기 수강한 데이터 구조 heap 강의 pdf 와 과제 내용
// blog: https://woongsin94.tistory.com/4, https://gmlwjd9405.github.io/2018/05/10/data-structure-heap.html, https://m.blog.naver.com/tkdldjs35/221301759270

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

#define HEAP_SIZE 30 // heap 사이즈



typedef struct {
    char name[10];
    float key;
} element;  //  score and name 을 담기 위한 element 구조체 선언


struct element heap[HEAP_SIZE];

void insert (heap h,  char* value, float key);  // element를 heap에 추가하는 함수
element trim (heap h);  //element를 삭제하는 함수 (root 삭제)
void replace (heap h, int index, float newKey);  // key(score)를 수정하는 함수
void print (heap h);  // heap의 모든 element를 출력해주는 함수
void heapify (heap p, int k, int N);  // element가 추가, 삭제, 수정 이후 min-heap 을 유지하기 위한 과정을 수행하는 함수
void clear(heap h);

void insert(heap h,  char* value, float key) {
    int k = 0;
    int N = 0;
    element item;
    
    
    strcpy(item.name, value);  // 입력 받은 name 값을 element 구조체의 value 멤버에 저장
    item.key = key;   // 입력 받은 score 값을 element 구조체의 key 멤버에 저장
    h -> item[++(h->N)] = item;

    
    for (int i = (h->N)/2; i >= 1; i--){  // 부모 노드 부터 root 까지 heapify 수행
        heapify(h, i, (h->N));
    }
    
    
}

element trim(heap h) {
    element item, temp;
    int k = h -> index;

    item = h -> index[1];  // root 인 heap 의 첫 요소 저장
    temp = h -> index[(h -> N)--]; // 한가지 element를 삭제하는 것이기에 index 값 감소

    h -> heap[1] = temp; // root 에 가장 마지막 element 저장

    heapify(h, 1, k); // root 부터 heapify 실행

    return item; // 삭제된 값 출력을 위해 element 로 return

}

void heapify(heap h, int k, int N) {
    element smallest;
    element left = h -> index[2*k]; // 왼쪽 값
    element right = h -> index[(2*k) + 1]; // 오른쪽 값
    int small_index; // smallest element 의 index 값
    
    if(N != 1){ // root 만 존재하지 않을 때 (root 만 존재시 비교 대상 x)

        if ( 2*k <= N && (left.key < h -> index[k].key)) { // 왼쪽(index : 2k) 에 값이 존재하고 왼쪽 score 가 현재(index : k) 의 score 보다 작을 때 최소값은 왼쪽 score
            smallest = left;
            small_index = 2*k;
        }
        else{
            smallest = h -> index[k]; // 왼쪽(index : 2k) 에 값이 존재하고  현재(index : k) score 가 왼쪽의 score 보다 작을 때 최소값은 현재 score
            small_index = k;
        }
        if ( (2*k) + 1 <= N && (right.key < smallest.key)) { // 오른쪽(index : 2k + 1) 에 값이 존재하고 오른쪽 score 가 위에서 정해진 smallest 의 score 보다 작을 때 최소값은 오른쪽 score
            smallest = right;
            small_index = (2*k) + 1;
        }

        if(k != small_index) { // 현재 (index : k) 가 최솟값 index 와 다른 경우 (swap 필요)
            element temp;
            temp =  h -> index[k]; // overlap 방지

            h -> index[k] = smallest;

            smallest = temp;
            h -> index[small_index] = smallest;

            heapify(h, small_index, N); // 최솟값 index 부터 recursive 하게 heapify 수행
            
        }
        
    }
}

void replace(heap h, int ind, float newKey) {
    h -> index[ind].key = newKey;  // oldKey 를 사용자가 입력한 newKey 로 변경
    heapify(h, 1, h->N); // 변경한 값이 min-heap 을 만족하는지 확인하고 아니라면 min-heap 을 만족시키기 위해 코드 수행
}

void print(heap h) {
    for(int i = 1; i <= h->N; i++) { // index 1 부터 끝까지 모든 element 내용 출력
        element item = h -> index[i];
        cout << " [" << item.name << ", " << item.key << "] ";
    }
}

// deallocates a heap.
void clear(heap h) {
    free(h->index);
    return;
}

int main(int argc, char* argv[]) {
    heap hp = new Heap; // heap 구조체 new


    char type;  // 메뉴 선택 저장 변수
    char name[10]; // name 사용자 력 값
    float score;  // score 사용자 입력 값
    float new_score; // 수정하고자 하는 score 사용자 입력 값
    int update_index; // 수정하고자 하는 element index 사용자 입력 값

    do {
        // menu 출력
        cout << "\n*********** MENU ***********\n" << endl;
        cout << "I : Insert new element into queue." << endl;
        cout << "D : Delete element with smallest key from queue." << endl;
        cout << "C : Decrease key of element in queue." << endl;
        cout << "P : Print out all elements in queue." << endl;
        cout << "Q : Quit" << endl;
        cout << endl;

    
        cout << "Choose menu: ";
        cin >> type;

        // case 로 menu 선택에 따라 적절한 수행
        switch (type){
            case 'I': {
                if (hp -> N == HEAP_SIZE){  // heap size 이상으로 insert 할 수 없음
                    cout << "FULL HEAP\n";
                    break;
                }
                else{
                    cout << "Enter name of element: ";
                    cin >> name;

                    cout << "Enter key value of element: ";
                    cin >> score;

                    while (score < 0.0 || score > 100.0) {  // 0.0 < score <100.0 범위 만족 조건 확인
                        cout << "Score Range ERROR again...\n";
                        cout << "Enter key value of element: ";
                        cin >> score;
                    }

                    insert(hp, name, score); // 입력값으로 insert 함수 호출
                    cout << "New element [" << name << ", " << score << "] is inserted.\n"; // 입력값으로 확인 출력
                }
                
                break;
            }

            case 'D': {
                if(hp->N == 0){ // heap 에 아무것도 없을 때 조건
                    cout << "Nothing to delete...\n";
                }
                else{
                    element del;
                    del = trim(hp); // 삭제할 root 값을 return 하므로 변수에 담아서 확인 출력
                    cout << "[" << del.name << ", " << del.key << "] is deleted.\n";
                }
                
                break;
            }
            
            case 'C': {
                cout << "Enter index of element: ";
                cin >> update_index;
                
                while(update_index > hp->N && update_index > 0 ) { // 수정할 index 존재여부 확인
                    cout << "Index is uavailble...\n";
                    cout << "Enter index of element: ";
                    cin >> update_index;
                }
                
                cout << "Enter new key value: ";
                cin >> new_score;

                while(new_score >= hp->index[update_index].key) { // 수정할 key value 가 기존 값보다 작아야 함으로 조건 확인 (decrease key)
                    cout << "New key should be decrease...\n";
                    cout << "Enter new key value: ";
                    cin >> new_score;
                }

                replace(hp, update_index, new_score); // 수정할 key 값 위치 index 와 새로운 key 값을 전달하며 replace 함수 호출

                break;
            }

            case 'P': {
                print(hp);  // 모든 element 출력 함수 호출
                
                break;
            }
        }

    } while ( type != 'Q'); // 사용자가 Q 입력 시 프로그램 종료

    clear(hp);

    cout << "Thank you. Bye!\n";

}
