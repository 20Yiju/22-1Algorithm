//22000690 정이주
// 강의 slide: ch22 page 24, 이전에 수강한 데이타 구조 LinkedList 과제와 강의 슬라이드 참조
// blog: https://datahub.tistory.com/15, https://cryptosalamander.tistory.com/137, https://www.delftstack.com/ko/howto/cpp/sort-strings-alphabetically-in-cpp/
// https://hashcode.co.kr/questions/84/stdstring의-개행-문자들을-다-지우는-방법, https://thispointer.com/creating-a-matrix-using-2d-vector-in-c-vector-of-vectors/


#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm> 
#include <cctype>

using namespace std;

struct Node {
    char data; // node value
    Node* next; // next node
};
using pNode = Node*;

pNode push_back(pNode p , char key); // 인접 리스트에 값 추가
void adj_list(vector< vector<char> > vec, char* arr); // 행렬을 인접 리스트로 변환
vector< vector<char> > trans(vector< vector<char> > vec);  // 그래프 transpose 함수
void print_list(pNode p); // 인접 리스트 출력
pNode clear(pNode p); // 인접 리스트 delete


int main(){
    string line;
	ifstream file("hw4_.data.txt"); // hw4_.data.txt 파일을 열기
	int l = 0;
	char alph[20];
	vector<string> line_v;
	vector<char> od;
	vector< vector<char> > td;
	vector< vector<char> > td_T;

	if(file.is_open()){
		while(getline(file, line)) {
			
			if(l != 0){
				line.erase(remove(line.begin(), line.end(), '	'), line.end()); // tab 제거
				line.erase(remove(line.begin(), line.end(), ' '), line.end());  // 공백 제거
				line.erase(line.find_last_not_of(" \n\r\t")+1);  // 개행 문자 제거
				//cout << line << endl;
				line_v.push_back(line);
			}
			l++;	
		}

        sort(line_v.begin(), line_v.end()); // 알파벳 순으로 정렬

        int r = 0;
        for(string item: line_v){
            alph[r] = item[0];
            item = item.substr(1);
            for(int i = 0; i < item.length(); i++){
                od.push_back(item[i]);
            }
            td.push_back(od);
            od.clear(); // vector 비우기
            r++;
        }

        cout << "1) Array of adjacency list of above graph: " << endl;  // 기존 출력 문구
        adj_list(td, alph); // 기존 그래프의 인접 리스트
        td_T = trans(td); // transpose 된 그래프 저장
        cout << endl;
        cout << "2) Array of adjacency list of transpose graph: " << endl;  // transpose 출력 문구
        adj_list(td_T, alph); // transpose 된 그래프의 인접 리스트
            
    }
    else {
        cout << "open file fail...";
        return 1;
    }
    file.close();
    return 0;
}

void adj_list(vector<vector<char>> vec, char* arr){
    

    for(int i = 0; i < vec.size(); i++){
        Node *head = nullptr;
       // cout << "adj " << arr[i] << endl;
        head = push_back(head, arr[i]);
        int k = 0;
        for(int j = 0; j < vec[i].size(); j++){
            if(vec[i][j] == '1'){
                //cout << "adj " << arr[k] << endl;
                head = push_back(head, arr[k]);
                
            }
            k++;
        }

        //cout << " ->  NIL" << endl;
        print_list(head);
        cout << endl;
        clear(head);
    }
    
}

vector< vector<char> > trans(vector< vector<char> > vec){
    vector< vector<char> > vecT(vec[0].size(), vector<char>(vec.size()));

    for(int i = 0; i < vec.size(); i++){
        for(int j = 0; j < vec[i].size(); j++){
            vecT[j][i] = vec[i][j]; // transpose
        }
    }
    return vecT; // transpose 된 그래프 return
}

pNode push_back(pNode p , char key){
    Node *x = p;
    Node *q = new Node;
    q -> data = key;
    q -> next = nullptr;
    
    if(p == nullptr){
        p = q;
    }
    else{
        while(x -> next != nullptr){
            x = x -> next;
        }
        x -> next = q;
    }
    //cout << "pb " <<  q -> data << endl;
    
    return p;
}



void print_list(pNode p){
    int i;
    int count = 0;
    for (pNode c = p; c != nullptr; c = c->next, count++);
    
    for(int i = 0; i < count ; i++) {
        if(i == 0){
            cout << p -> data;
        }
        else{
            cout << " -> " << p -> data;
        }
        
        p = p -> next;
    }
    cout << " ->  NIL";

}

pNode clear(pNode p) {
    Node* curr = p;
    while (curr != nullptr) {
        Node* zap = curr;
        curr = curr->next;
        delete zap;
    }
    return nullptr;
}




