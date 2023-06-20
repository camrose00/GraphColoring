#include <iostream>
#include <fstream>
#include <stack>
#include "LL.h"
#include "Graph.h"
#include <chrono>
using namespace std;

// Structure for a singly linked list node
int main(int argc, char **argv) {
    int E, V;
    string G, DIST;

    //atoi(argv[1]);
    //atoi(argv[2]);
    G = argv[3];
    DIST = "RANDOM";
    //cycle complete uniform skewed high

    ofstream send;
    send.open("Verticies.csv");//std::ios_base::app
    //for (int i = 100; i < 1000; i+=100) {
    int i=10;
        Graph graph;
        graph.V = i;
    auto t1 = std::chrono::high_resolution_clock::now();
        Graph::Node **gph = graph.generateCompleteGraph(i);
        //graph.print();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto ms_int = chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
    send<<i<<","<<ms_int.count()<<endl;


        //random
//        double time = graph.rando(gph);
//        send << i <<","<< time << ",";
//
//        //origionalDegree
//        time = graph.origionalDegree();
//        send << time << ",";

        //smallestLast
        map<int,int> pp = graph.smallest(gph);
    auto it = pp.begin();
    while(it!=pp.end()){
        send<<it->first<<","<<it->second<<endl;
        it++;
    }

        //send  << time<<",";
        //greatestLast
//        time = graph.greatest(gph);
//        send <<  time <<endl;
    for (int k = 0; k < i; k++) {
        Graph::Node *temp = *(gph + k);
        while (temp != nullptr) {  // keep iterating until head is null
            Graph::Node *curr = temp->next;
            delete temp;
            temp = curr;
        }
        gph[k] = NULL;
    }
}