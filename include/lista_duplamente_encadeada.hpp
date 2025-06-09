#pragma once
#include<iostream>

template<typename T>

struct Node{
    T data;
    Node<T>* next;
    Node<T>* prev;
    Node(const T& d): data(d),next(nullptr),prev(nullptr){}
};

template<typename T>

class DoublyLinkedList{
    private:

    Node<T>* head;
    Node<T>* tail;

    public:

    DoublyLinkedList():head(nullptr),tail(nullptr){}

    ~DoublyLinkedList(){
        Node<T>* current=head;

        while(current){
            Node<T>* next = current->next;

            delete current;

            current=next;
        }
    }

    void append(const T& value){
        Node<T>* newNode = new Node<T>(value);

        if(!head){
            head=tail=newNode;
        }
        else{
            tail->next=newNode;
            newNode->prev=tail;
            tail=newNode;
        }
        
    }

    void appendAtHead(const T& value){
        Node<T>* newNode = new Node<T>(value);

        if(!head){
            head=newNode;
            tail=newNode;
            return;
        }
        else{
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void printForward(){
        Node<T>* current = head;
        while(current){
            std::cout<<current->data<<" "<<std::endl;
            current=current->next;
        }
        std::cout<<std::endl;       
    }

    void printBackwards(){
        Node<T>* current = tail;
        while(current){
            std::cout << current->data << " " << std::endl;
            current = current->prev;
        }
        std::cout << std::endl;
    }
    Node<T>* getHead(){
        return this->head;
    }
};


