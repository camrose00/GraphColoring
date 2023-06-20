//
// Created by Cameron Rosenberger on 3/23/23.
//

#ifndef FINALPROJ_GRAPH_H
#define FINALPROJ_GRAPH_H
// A C++ program to implement greedy algorithm for graph coloring
#include <iostream>
#include "LL.h"
#include <random>
#include <cmath>
#include <map>
#include <iterator>

using namespace std;
bool DEBUG = true;

class Graph {
public:
    struct Node {
        int vertex;
        Node *next;

        Node(int a, Node *b) {
            vertex = a;
            next = b;
        }

        Node(int a) {
            vertex = a;
            next = nullptr;
        }

        Node() {}
    };

    int V;
    int E;
    LL<int> *deg;
    Node **adj;
    int *degreeDeleted;
    Node** cpy;

    Node **&generateCycleGraph(int V) {
        adj = new Node *[V];
        for (int i = 0; i < V; i++) {
            adj[i] = new Node;
            adj[i]->vertex = (i == 0 ? V - 1 : i - 1);
            adj[i]->next = nullptr;
            Node *new_node = new Node;
            new_node->vertex = (i + 1) % V;
            new_node->next = adj[i]->next;
            adj[i]->next = new_node;
        }
        return adj;
    }

    Node **&generateCompleteGraph(int V) {
        adj = new Node *[V];
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (i != j) {
                    Node *new_node = new Node(j);
                    new_node->next = adj[i];
                    adj[i] = new_node;
                }
            }
        }
        return adj;
    }

    Node **&generateRandomGraphUniform(int V, int E) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(0, V - 1);
        adj = new Node *[V];
        for (int i = 0; i < V-1; i++) {
            Node* a = new Node(i+1);
            a->next = adj[i];
            adj[i] = a;
            Node* b = new Node(i);
            b->next = adj[i+1];
            adj[i+1] = b;
        }
        Node* a = new Node(0);
        a->next = adj[V-1];
        adj[V-1] = a;
        Node* b = new Node(V-1);
        b->next = adj[0];
        adj[0] = b;

        int count = V;
        while (count < E) {
            int u = dist(gen);
            int v = dist(gen);
            if (u != v) {
                bool dup = false;
                Node *curr = adj[u];
                while (curr != nullptr) {
                    if (curr->vertex == v ) {
                        dup = true;
                        break;
                    }
                    curr = curr->next;
                }
                if (!dup && curr == nullptr) {
                    Node *new_node = new Node;
                    new_node->vertex = v;
                    new_node->next = adj[u];
                    adj[u] = new_node;
                    new_node = new Node;
                    new_node->vertex = u;
                    new_node->next = adj[v];
                    adj[v] = new_node;
                    count++;
                }
            }
        }
        return adj;
    }

    bool hasEdge(Node *head, int dest) {
        Node *current = head;
        while (current != nullptr) {
            if (current->vertex == dest) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    Node **&generateRandomGraphSkewed(int V, int E) {

        adj = new Node *[V];
        for (int i = 0; i < V-1; i++) {
            Node* a = new Node(i+1);
            a->next = adj[i];
            adj[i] = a;
            Node* b = new Node(i);
            b->next = adj[i+1];
            adj[i+1] = b;
        }
        Node* a = new Node(0);
        a->next = adj[V-1];
        adj[V-1] = a;
        Node* b = new Node(V-1);
        b->next = adj[0];
        adj[0] = b;
        int dist = .25*V;
        int count = V;
        while (count < E) {
            int u = rand() % dist;
            int v = rand() % dist;
            if (u != v) {
                bool dup = false;
                Node *curr = adj[u];
                while (curr != nullptr) {
                    if (curr->vertex == v ) {
                        dup = true;
                        break;
                    }
                    curr = curr->next;
                }
                if (!dup && curr == nullptr) {
                    Node *new_node = new Node;
                    new_node->vertex = v;
                    new_node->next = adj[u];
                    adj[u] = new_node;
                    new_node = new Node;
                    new_node->vertex = u;
                    new_node->next = adj[v];
                    adj[v] = new_node;
                    count++;
                }
            }
        }
        return adj;
    }

    Node **&generateRandomGraphHigh(int V, int E) {
        adj = new Node *[V];
        for (int i = 0; i < V-1; i++) {
            Node* a = new Node(i+1);
            a->next = adj[i];
            adj[i] = a;
            Node* b = new Node(i);
            b->next = adj[i+1];
            adj[i+1] = b;
        }
        Node* a = new Node(0);
        a->next = adj[V-1];
        adj[V-1] = a;
        Node* b = new Node(V-1);
        b->next = adj[0];
        adj[0] = b;
        int dist = .75*V;
        int count = V;
        while (count < E) {
            int u = dist + rand() % V;
            int v = dist + rand() % V;
            if (u != v) {
                bool dup = false;
                Node *curr = adj[u];
                while (curr != nullptr) {
                    if (curr->vertex == v ) {
                        dup = true;
                        break;
                    }
                    curr = curr->next;
                }
                if (!dup && curr == nullptr) {
                    Node *new_node = new Node;
                    new_node->vertex = v;
                    new_node->next = adj[u];
                    adj[u] = new_node;
                    new_node = new Node;
                    new_node->vertex = u;
                    new_node->next = adj[v];
                    adj[v] = new_node;
                    count++;
                }
            }
        }
        return adj;
    }

    LL<int> *&groupByDegree() {
        deg = new LL<int>[V];

        for (int i = 0; i < V; i++) {
            Node *temp = adj[i];
            int len = 0;
            while (temp != NULL) {
                temp = temp->next;
                len++;
            }
            deg[len].push_front(i);
        }
        //cout << "ORIGIONAL DEGREE" << endl;
//        for (int i = 0; i < V; i++) {
//            if (deg[i].front != NULL) {
//                //cout << i << "--> ";
//                //deg[i].print();
//            }
//        }
        return deg;
    }

    void decrementDegree(int x,int idx) {
            LL<int> current = *(deg + idx+1);
            bool rem = deg[idx+1].remove(x);
            LL<int> dec = *(deg + idx);
            deg[idx].push_front(x);
    }

    void print() {
        cout << "ADJACENCY LIST" << endl;
        for (int i = 0; i < V; ++i) {
            Node *temp = *(adj + i);

            // Linked list number
            cout << i << "-->\t";

            // Print the Linked List
            while (temp != NULL) {
                cout << temp->vertex << " ";
                temp = temp->next;
            }
            cout << '\n';
        }
        cout<<"CPY"<<endl;
        for (int i = 0; i < V; ++i) {
            Node *temp = *(cpy + i);

            // Linked list number
            cout << i << "-->\t";

            // Print the Linked List
            while (temp != NULL) {
                cout << temp->vertex << " ";
                temp = temp->next;
            }
            cout << '\n';
        }
    }
    int adjustGraph(int arg,int remove){
        Node* curr = adj[arg];
        int len = 0;
        if(curr->vertex == remove){
            adj[arg] = curr->next;
            delete curr;
            curr = adj[arg];
            if(curr){
                len++;
            }else{
                return 0;
            }
        }
        while(curr->next!=NULL){
            if(curr->next->vertex == remove){
                Node* del = curr->next;
                curr->next = curr->next->next;
                delete del;
                len++;
                break;
            }
            curr=curr->next;
            len++;
        }
        curr = adj[arg];
        return len;
    }
    void copy() {
        this->cpy = new Node *[V];
        for (int i = 0; i < V; i++) {
            Node *temp = *(adj + i);
            cpy[i] = NULL;
            while (temp != NULL) {
                Node *place = new Node(temp->vertex);
                place->next = cpy[i];
                cpy[i] = place;
                temp = temp->next;
            }
        }
    }

    void deleteVertex(int x,int idx) {
        Node *curr = *(adj + x);
        while (curr != NULL) {
            int len = adjustGraph(curr->vertex, x);
            decrementDegree(curr->vertex,len);
            curr = curr->next;
        }
            LL<int> row = *(deg + idx);
            deg[idx].remove(x);
            curr = *(adj+x);
            while(curr!=NULL){
            Node* a = curr;
            curr=curr->next;
            delete a;
            }
            adj[x] = NULL;
    }

    stack<int> randoOrder() {
        vector<int> bag(V);
        stack<int> st;
        for (int i = 0; i < V; i++) {
            bag[i] = i;
        }
        for (int i = 0; i < V; i ++) {
            int choose = rand() % bag.size();
            st.push(bag[choose]);
            bag.erase(bag.begin()+choose);
        }
        return st;
    }
    stack<int> smallestOrigional(){
        stack<int> st;
       for(int i=0;i<V;i++){
           DNode<int>* curr = deg[i].front;
           while(curr!=NULL){
               st.push(curr->data);
               curr=curr->next;
           }
       }
        return st;
    }
    stack<int> smallestLast() {
        int vLeft = V;
        int terminalClique = 0;
        bool checked = false;
        degreeDeleted = new int[V];
        stack<int> st;
        for (int i = 0; i < V; i++) {
            DNode<int> *current = deg[i].front;
            if (current == NULL)
                continue;
            st.push(current->data);
            degreeDeleted[current->data] = i;
            if (i == (vLeft - 1) && !checked) {
                terminalClique = vLeft;
                checked = true;
            }
            deleteVertex(current->data,i);
            vLeft--;
            (i >= 2 ? i -= 2 : i = -1);
        }
        cout<<"Terminal clique: "<<terminalClique<<endl;
        cout<<"Vertex #s - ";
        for (int i = 0; i < V; i++) {
            cout<<i<<" ";
        }
        cout<<endl;
        cout<<"Degree    - ";
        for (int i = 0; i < V; i++) {
            cout<<degreeDeleted[i]<<" ";
        }
        cout<<endl;
        delete degreeDeleted;
        return st;
    }

    stack<int> greatestLast() {
        bool checked = false;
        degreeDeleted = new int[V];
        stack<int> st;
        for (int i = V - 1; i >= 0; i--) {
            DNode<int> *current = deg[i].front;
            if (current == NULL)
                continue;
            if (i == 0) {
                while (current != NULL) {
                    st.push(current->data);
                    current = current->next;
                }
                break;
            }
            if (current != NULL) {
                st.push(current->data);
                degreeDeleted[current->data] = i;
                deleteVertex(current->data,i);
                i++;
            }
        }
        //cout<<"Vertex #s - ";
//        for (int i = 0; i < V; i++) {
//            cout<<i<<" ";
//        }
//        cout<<endl;
//        cout<<"Degree    - ";
//        for (int i = 0; i < V; i++) {
//            cout<<degreeDeleted[i]<<" ";
//        }
//        cout<<endl;

        return st;
    }

    int *color(stack<int> st) {
        //code in color() modified from geeks for geeks
        //https://www.geeksforgeeks.org/graph-coloring-set-2-greedy-algorithm/#
        stack<int> ref = st;
        int *result = new int[V];

        // Assign the first color to first vertex
        int a = st.top();
        cout<<a<<" ";
        st.pop();
        result[a] = 0;
        // Initialize remaining V-1 vertices as unassigned
        for (int u = 0; u < V; u++) {
            if (u != a) {
                result[u] = -1;
            }
        }
        // A temporary array to store the available colors. True
        // value of available[cr] would mean that the color cr is
        // assigned to one of its adjacent vertices
        bool available[V];
        for (int cr = 0; cr < V; cr++) {
            available[cr] = false;
        }

        // Assign colors to remaining V-1 vertices
        while (!st.empty()) {
            // Process all adjacent vertices and flag their colors
            // as unavailable
            int nxt = st.top();
            st.pop();
            Node *curr = *(cpy + nxt);
            int i = 0;
            while (curr != NULL) {
                if (result[curr->vertex] != -1)
                    available[result[curr->vertex]] = true;
                curr = curr->next;
            }
            // Find the first available color
            int cr;
            for (cr = 0; cr < V; cr++)
                if (available[cr] == false)
                    break;
            result[nxt] = cr; // Assign the found color
            // Reset the values back to false for the next iteration
            curr = *(cpy + nxt);
            while (curr != NULL) {
                if (result[curr->vertex] != -1)
                    available[result[curr->vertex]] = false;
                curr = curr->next;
            }
        }
        if(DEBUG){
//             print the result
            for (int u = 0; u < V; u++) {
                cout <<u <<" ";
            }
            cout<<endl;
            cout <<"Color     - ";
            for (int u = 0; u < V; u++) {
                cout <<result[u] <<" ";
            }
            cout<<endl;
            }
        return result;

    }

    double rando(Node **&gph) {
        this->deg = groupByDegree();
        copy();
        //print();

        stack<int> st = randoOrder();
        auto t1 = std::chrono::high_resolution_clock::now();
        int *r = color(st);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto ms_int = chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
        return double(ms_int.count());

    }
    double origionalDegree(){
        //print();
        stack<int> st = smallestOrigional();
        auto t1 = std::chrono::high_resolution_clock::now();
        int *r = color(st);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto ms_int = chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
        return double(ms_int.count());
    }
    map<int,int> smallest(Node**& gph) {
        this->adj = gph;
        copy();
        auto t1 = std::chrono::high_resolution_clock::now();
        this->deg = groupByDegree();
        auto t2 = std::chrono::high_resolution_clock::now();
        //print();
        stack<int> st = smallestLast();

        int *r = color(st);

        auto ms_int = chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
        map<int,int> pp;
        for(int i=0;i<V;i++){
            pp[r[i]]++;
        }
        return pp;
    }
    double greatest(Node **&gph) {
        this->adj = cpy;
        this->deg = groupByDegree();
        copy();
        //print();
        stack<int> st = greatestLast();
        auto t1 = std::chrono::high_resolution_clock::now();
        int *r = color(st);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto ms_int = chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
        return double(ms_int.count());
    }
};
#endif //FINALPROJ_GRAPH_H