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
    string destination;
    int weight;
}node;

#define infinite 100000

void Dijkstra(vector <string> header, int src);
void FloydFunction(vector< vector <string> > graph);
void print_F(vector< vector <string> > graph);
void showList(int src, list<node> lt);
int find_MIN(node a, node b);

int find_MIN(node a, node b){
    return a.weight > b.weight;
}

list<node> *adjList;


int main(){
    string line;
    string first;
    ifstream count("/Users/jeong-yiju/Documents/22-1 알고리듬/hw5/hw5_data.txt"); // hw4_.data.txt 파일을 열기
    ifstream file("/Users/jeong-yiju/Documents/22-1 알고리듬/hw5/hw5_data.txt"); // hw4_.data.txt 파일을 열기
    vector< vector <string> > td;
    vector <string> od;
    int c = 0;
    int k = 0;
    
    vector <string> header;
    int line_count = 0;
    
    if(file.is_open()){
        getline(count, first);
        stringstream ss(first);
        ss.str(first);
        string city;
        while(ss >> city){
            c++;
            header.push_back(city);
        }
        adjList = new list<node>[c];
        
        
        while(getline(file, line)) {
            int i = 0;
            stringstream ss(line);
            ss.str(line);
            string word;
            string city;
            int l = 0;
            while(ss >> word){
                od.push_back(word);
                if(line_count != 0){
                    node newNode;
                    if(l != 0){
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
    cout << "       ";
    for(int i = 0; i < header.size(); i++) {
        cout << header[i] <<"   ";
    }
    cout << endl;
    for(int i = 0 ; i < header.size(); i++){
        cout << header[i] <<"   ";
        Dijkstra(header, i); // apply Dijkstra's algorithm |V| times on each vertex.
        cout << endl;
        
    }
    cout << "\n" << endl;
    FloydFunction(td);
    

    /*for(int i = 0; i < c; i++) {
        list<node> tempList = adjList[i];
        showList(i, tempList);
    }*/

    cout << endl;
    file.close();
    return 0;


}

void Dijkstra(vector <string> header, int src) {
    int n = header.size();
    int distance[n];

    for(int i = 0; i < n; i++){ // vertex distance intialize in INF
        distance[i] = infinite;
    }
    distance[src] = 0; //source vertex distance intialize  in 0

    set<int> S;
    //list<int> Q;
    priority_queue<  pair<int, int> > Q;
    /*for(int i = 0; i < n; i++){
        Q.push_back(i);
    }*/
    Q.push(make_pair(distance[src], src));


    while(!Q.empty()){

        int u = Q.top().second;
        Q.pop();

        list<node> :: iterator it;
        list<node> adnode = adjList[u];
        //showList(u, adnode);

        for(it = adnode.begin(); it != adnode.end(); it++) {
            node des = *it;
            string dest = des.destination;
            int d = 0;
            for(int j = 0; j < n; j++){
                if(header[j] == dest){
                    d = j;
                    break;
                }
            }
            int di = distance[d];
            int ui = distance[u];
            int w = des.weight;
            if(distance[u]+(des.weight) < distance[d]){
                distance[d] = distance[u]+(des.weight);
                Q.push(make_pair(distance[d], d));
            }
        }

    }

    for(int i = 0; i < n ; i++){
        cout << distance[i] << "    ";
    }
    

}

void showList(int src, list<node> lt) {
    list<node> :: iterator i;
    node tempNode;

    for(i = lt.begin(); i != lt.end(); i++) {
        tempNode = *i;
        cout << "(" << src << ")---("<<tempNode.destination << "|"<<tempNode.weight<<") ";
    }
    cout << endl;
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
                if(stoi(vec[i][k]) + stoi(vec[k][j]) < stoi(vec[i][j])){
                    
                    int sp = stoi(vec[i][k]) + stoi(vec[k][j]);
                    
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

