#pragma once
#include<iostream>

template<typename T>
struct StackNode {
    T data;
    StackNode<T>* next;
    StackNode(const T& d): data(d), next(nullptr) {}
};

template<typename T>
class Stack {
private:
    StackNode<T>* top;
    int numberOfElements;

public:


    Stack(): top(nullptr), numberOfElements(0) {}

    ~Stack() {
        StackNode<T>* current = top;
        while(current) {
            StackNode<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    void push(const T& value) {
        StackNode<T>* newNode = new StackNode<T>(value);
        newNode->next = top;
        top = newNode;
        numberOfElements++;
    }

    void pop() {
        if(top == nullptr) {
            std::cout << "The stack is empty" << std::endl;
            return;
        }
        StackNode<T>* aux = top;
        top = top->next;
        delete aux;
        numberOfElements--;
    }

    T getTop() const {
        if(top == nullptr) {
            std::cout << "The stack is empty" << std::endl;
            return T();
        }
        return top->data;
    }

    bool isEmpty() const {
        return (top == nullptr);
    }

    int getNumberOfElements() const {
        return numberOfElements;
    }
};