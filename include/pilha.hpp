#pragma once
#include<iostream>

template<typename T>

struct Node{
    T data;
    Node<T>* next;
    Node(const T& d): data(d),next(nullptr){}
};

template<typename T>

class Stack{
    private:
        Node<T>* top;
        int numberOfElements;

    public:

        Stack():top(nullptr),numberOfElements(0){};
        ~Stack(){
            Node<T>* current=top;

            while(current){
                Node<T>*next = current->next;
                delete current;
                current=next;
            }
        }
        void push(const T& value){
            Node<T>* newNode = new Node(value);
            newNode->next=top;
            top=newNode;
            numberOfElements++;

        }
        void pop(){
            if(top==nullptr){
                std::cout<<"The stack is empty"<<std::endl;
                return;
            }
            Node<T>* aux=top;
            top=top->next;
            delete aux;
            numberOfElements--;
        }
        T getTop()const{
            if(top==nullptr){
                std::cout<<"The stack is empty"<<std::endl;
                return T();
            }
            return top->data;
        }
        bool isEmpty()const{
            return (top==nullptr);
        }
        int getNumberOfElements()const{
            return numberOfElements;
        }

    
};