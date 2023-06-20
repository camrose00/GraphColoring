//
// Created by Cameron Rosenberger on 6/14/22.
//

#include <iostream>

#ifndef PROJ3NOTES_DSLISTDNode_H
#define PROJ3NOTES_DSLISTDNode_H

template<typename T>
class DNode {
public:
    T data;

    DNode* next;
    DNode* prev;
    DNode(const T& arg, DNode* n=nullptr, DNode* p =nullptr);
    DNode();
    bool operator !=(const DNode& arg);
    DNode<T>& operator=(DNode&);
    void print();

};
template <typename T>
DNode<T>::DNode(const T& arg, DNode* n, DNode* p){
    next=n;
    prev=p;
    data=arg;
}
template<typename T>
void DNode<T>::print(){
    DNode* curr = next;
    while(curr!=nullptr){
        std::cout<<curr->data<<std::endl;
        curr=curr->next;
    }
}
template <typename T>
DNode<T>::DNode(){
    next=prev=nullptr;
}

template<typename T>
bool DNode<T>::operator!=(const DNode &arg) {
    if(this->data==arg.data) {
        return false;
    }
    return true;
}

template<typename T>
DNode<T>& DNode<T>::operator=(DNode& arg) {
    delete[] this->data;
    this->data=arg.data;
    this->next=arg.next;
    this->prev=arg.prev;
    this->condition=arg.condition;
    return *this;
}

#endif