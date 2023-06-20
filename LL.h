//
// Created by Cameron Rosenberger on 6/14/22.
//
#include "DNode.h"
#include <iostream>
#include <exception>
using namespace std;
#ifndef PROJ3NOTES_LL_H
#define PROJ3NOTES_LL_H
template<typename T>
class LL{
public:
    DNode<T>* front;
    DNode<T>* tail;

    LL();
    LL(const LL&);
    LL& operator=(const LL&);
    ~LL();

    void push_front(const T& arg);

    void insert(const T& arg, int loc);
    T& at(int loc);
    bool remove(int arg);
    int size()const;
    void print();
    void clear();
    int find(const T&)const;
    T& operator[](int);

};
template<typename T>
LL<T>::LL(): front(nullptr),tail(nullptr){
}
template<typename T>
void LL<T>::push_front(const T& arg){
    DNode<T>* newNode = new DNode<T>;

    //assign data to new node
    newNode->data = arg;

    //new node is head and previous is null, since we are adding at the front
    newNode->next = (front);
    newNode->prev = NULL;

    //previous of head is new node
    if ((front) != NULL)
        (front)->prev = newNode;

    //head points to new node
    (front) = newNode;
}
template<typename T>
bool LL<T>::remove(int arg){
    DNode<T>* current = front;
    bool ret = false;
    while (current != NULL) {
        if (current->data == arg) {
            ret = true;
            break;
        }
        current = current->next;
    }
    if(ret == false){
        return false;
    }
    if(current == front){
        front = current->next;
    }
    if(current->next != NULL){
        current->next->prev = current->prev;
    }
    if(current->prev != NULL){
        current->prev->next = current->next;
    }
    if(current == tail){
        tail = current->prev;
    }
    delete current;
    return true;
}
template<typename T>
void LL<T>::print(){

    DNode<T>* curr = front;
    while(curr!=nullptr){
        std::cout<<curr->data<<" ";
        curr=curr->next;
    }
    std::cout<<std::endl;
}
template<typename T>
T& LL<T>::at(int loc){
    DNode<T>* curr=front;
    int counter=0;
    while(counter<loc && curr!=nullptr){
        counter++;
        curr = curr->next;
    }
    if(counter==loc && curr!=nullptr){
        return curr-> data;
    }

    throw runtime_error("Linked List @ location out of bounds");
}
template<typename T>
void LL<T>::insert(const T& arg, int loc){
    if(loc==0){
        push_front(arg);
    }else {
        DNode<T> temp = new T(arg);
        DNode<T> *curr = front;
        int i = 0;
        while (curr != nullptr && i < loc) {
            curr = curr->next;
            i++;
        }
        if(curr!= nullptr&& i==loc){
            temp->next = curr;
            temp->prev=curr->prev;
            curr->prev->next=temp;curr->prev=temp;
        }
    }
}
template<typename T>
int LL<T>::size()const{
    int i=0;
    DNode<T>* curr = front;
    while(curr!=nullptr){
        curr=curr->next;
        i++;
    }
    return i;
}
template<typename T>
int LL<T>::find(const T& arg)const{
    DNode<T>* curr= front;
    for(int i=0;i<this->size();i++){
        if(curr->data == arg){
            return i;
        }
        curr=curr->next;
    }
    return -1;
}
template<typename T>
T& LL<T>::operator[](int loc) {
    return this->at(loc);
}
template<typename T>
LL<T>::~LL() {
    DNode<T>* temp = front;
    while (temp != nullptr) {  // keep iterating until head is null
        temp = front->next;
        delete front;
        front = temp;
    }
    delete front;  // delete head
}
template<typename T>
LL<T>::LL(const LL& arg) {
    front =nullptr;
    tail=nullptr;
   DNode<T>* temp = arg.front;
   for(int i=0;i<arg.size();i++){
       push_front(temp->data);
       temp=temp->next;
   }
   delete temp;
}
template<typename T>
void LL<T>::clear(){
    DNode<T>* temp = front;
    while (temp != nullptr) {  // keep iterating until head is null
        temp = front->next;
        delete front;
        front = temp;
    }
    delete front;  // delete head
}
template<typename T>
LL<T>& LL<T>::operator=(const LL& arg) {
    front = tail = nullptr;
    this->clear();
    DNode<T>*curr = arg.front;
    while (curr != nullptr) {
        this->push_back(curr->data);
        curr = curr->next;
    }

   return *this;
}

#endif //PROJ3NOTES_LL_H