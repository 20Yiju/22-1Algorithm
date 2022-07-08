//22000690 정이주
// 강의 slide: ch24,25 page 27~48, 52~56, LMS 영상 slide 의 "Floyd-Warshall Algorithm Version 2" (Modified Version)
// blog: https://seoyeonkk.tistory.com/entry/C-공백-기준-문자열-자르기split, https://m.blog.naver.com/ndb796/221234424646, https://www.geeksforgeeks.org/priority-queue-of-pairs-in-c-ordered-by-first/,
// https://blackotter.tistory.com/29, https://www.delftstack.com/ko/howto/cpp/vector-pair-cpp/, https://hsp1116.tistory.com/42,

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <queue>

using namespace std;
typedef struct Node {
    string destination; // 목적지 도시명
    int weight; // edge weight
}node;

#define infinite 100000

void Dijkstra(vector <string> header, int src); // Dijkstra function
void FloydFunction(vector< vector <string> > graph); // Floyd function
void print_F(vector< vector <string> > graph); // Floyd 알고리즘 적용 결과 출력 함수

list<node> *adjList;

int main(){
    string line;
    string first;
    ifstream count("hw5_data.txt"); // hw5_data.txt 파일을 열기
    ifstream file("hw5_data.txt"); // hw5_data.txt 파일을 열기
    vector< vector <string> > td;
    vector <string> od;
    int c = 0;
    int k = 0;
    
    vector <string> header;
    int line_count = 0;

    if(count.is_open()){
        // 인접리스트의 header 부분 설정을 위해 리스트 생성
        getline(count, first);
        stringstream ss(first);
        ss.str(first);
        string city;
        while(ss >> city){
            c++;
            header.push_back(city); 
        }
    }
    else{
        cout << "open file fail...";
        return 1;
    }
    
    // 인접리스트와 edge weight 저장
    if(file.is_open()){
        adjList = new list<node>[c];
        
        while(getline(file, line)) {
            int i = 0;
            stringstream ss(line);
            ss.str(line);
            string word;
            int l = 0;
            while(ss >> word){
                od.push_back(word);
                if(line_count != 0){  // 첫 번째 line은 도시명이므로 제외
                    node newNode;
                    if(l != 0){ // 각 라인의 첫번째 word는 도시명이므로 제외
                        if(word != "INF"){
                            newNode.destination = header[i];
                            newNode.weight = stoi(word);
                            adjList[k].push_back(newNode);
                        }
                        i++;
                        
                    }
                    
                }
                l++;
                
            }

            if(line_count != 0){
                k++;
            }
            line_count++;
            td.push_back(od);
            od.clear();

        }
         
    }
    else {
        cout << "open file fail...";
        return 1;
    }

    
    cout << "The followings are shortest distances between cities with Dijkstra's algorithm.\n" << endl;
    cout << "      ";
    for(int i = 0; i < header.size(); i++) {  
        cout << header[i] <<"   ";
    }
    cout << endl;
    for(int i = 0 ; i < header.size(); i++){ // Dijkstra's algorithm 을 각각의 vertex 에 |V|번 적용
        cout << header[i] <<"   ";
        Dijkstra(header, i); 
        cout << endl;
        
    }
    cout << "\n" << endl;
    FloydFunction(td);
    

    cout << endl;
    file.close();
    count.close();
    return 0;


}

void Dijkstra(vector <string> header, int src) {
    int n = header.size();
    int distance[n];

    for(int i = 0; i < n; i++){ // vertex distance를 infinite로 초기화
        distance[i] = infinite;
    }
    distance[src] = 0; //source vertex distance 를 0 으로 초기화

    set<int> S;
    priority_queue<  pair<int, int>, vector < pair <int, int>> , greater< pair <int, int>> > Q; //Min

    Q.push(make_pair(distance[src], src)); // 큐에 src distance 값과 src 추가


    while(!Q.empty()){

        int u = Q.top().second; // priority queue 에서 최솟값을 가지는 index(node의 도시명을 구하기 위한) 저장
        S.insert(u); // extract-min 값 set 에 저장
        Q.pop(); // queue에서 제거

        list<node> :: iterator it;
        list<node> adnode = adjList[u];

        for(it = adnode.begin(); it != adnode.end(); it++) {
            node des = *it;
            string dest = des.destination;
            int d = 0;
            for(int j = 0; j < n; j++){ // destination의 인덱스 값을 구하기 위한 반복문
                if(header[j] == dest){ 
                    d = j;
                    break;
                }
            }

            if(distance[u]+(des.weight) < distance[d]){  // 기존의 weight 보다 선택된 vertex 를 거쳐 가는 것이 작다면
                distance[d] = distance[u]+(des.weight); // distance 값 update
                Q.push(make_pair(distance[d], d)); //Queue 에 update 된 값 추가
            }
        }

    }

    for(int i = 0; i < n ; i++){
        cout << distance[i] << "    ";
    }
    

}

void FloydFunction(vector< vector <string> > graph){
    vector< vector <string> > vec;
    vec = graph;
    
    for(int k = 1; k < vec.size(); k ++){
        for(int i = 1; i < vec.size(); i++){
            for(int j = 1 ; j < vec[i].size(); j++){
                if(vec[i][k] == "INF"){
                    vec[i][k] = "1000000000";
                }
                if(vec[k][j] == "INF"){
                    vec[k][j] = "1000000000";
                }
                if(vec[i][j] == "INF"){
                    vec[i][j] = "1000000000";
                    
                }
                if(stoi(vec[i][k]) + stoi(vec[k][j]) < stoi(vec[i][j])){ // 기존의 weight 보다 선택된 vertex 를 거쳐 가는 것이 작다면
                    
                    int sp = stoi(vec[i][k]) + stoi(vec[k][j]); // distance 값 update
                    
                    string s_sp = to_string(sp);
                    vec[i][j] = s_sp;
                }
            }
        }
    }
    print_F(vec);
}
void print_F(vector< vector <string> > graph){
    cout << "The followings are shortest distances between cities with Floyd algorithm as follows.\n" << endl;
    cout << "      ";
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[i].size(); j++) {
            cout << graph[i][j]<<"    ";
        }
        cout << endl;
    }
}

