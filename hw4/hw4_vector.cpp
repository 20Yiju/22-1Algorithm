//22000690 정이주
// 강의 slide: ch22 page 24
// blog: https://datahub.tistory.com/15, https://cryptosalamander.tistory.com/137, https://www.delftstack.com/ko/howto/cpp/sort-strings-alphabetically-in-cpp/
// https://hashcode.co.kr/questions/84/stdstring의-개행-문자들을-다-지우는-방법, https://thispointer.com/creating-a-matrix-using-2d-vector-in-c-vector-of-vectors/

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm> 
#include <cctype>

using namespace std;

void adj_list(vector<vector<char>> vec, char* arr, int n); // 행렬을 인접 리스트로 출력 함수
vector< vector<char> > trans(vector< vector<char> > vec);  // 그래프 transpose 함수

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

		adj_list(td, alph, 0); // 기존 그래프의 인접 리스트
		td_T = trans(td); // transpose 된 그래프 저장
		cout << endl;
		adj_list(td_T, alph, 1); // transpose 된 그래프의 인접 리스트
			
	}
	else {
		cout << "open file fail...";
		return 1;
	}
	file.close(); 
	return 0;
}

void adj_list(vector<vector<char>> vec, char* arr, int n){
	if(n == 0){
		cout << "1) Array of adjacency list of above graph: " << endl;  // 기존 출력 문구
	}
	else{
		cout << "2) Array of adjacency list of transpose graph: " << endl;  // transpose 출력 문구
	}
	
	for(int i = 0; i < vec.size(); i++){
		cout << arr[i];
		int k = 0;
		for(int j = 0; j < vec[i].size(); j++){
			if(vec[i][j] == '1'){
				cout << " -> " << arr[k];
			}
			k++;
		}

		cout << " ->  NIL" << endl;	
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
