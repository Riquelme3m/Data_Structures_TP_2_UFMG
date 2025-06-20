#pragma once
#include<iostream>

// Nó da pilha - estrutura auxiliar
template<typename T>
struct StackNode {
    T data;
    StackNode<T>* next;
    StackNode(const T& d): data(d), next(nullptr) {}
};

// Implementação de pilha usando lista ligada (LIFO - Last In, First Out)
template<typename T>
class Stack {
private:
    StackNode<T>* top;        // Ponteiro para o topo da pilha
    int numberOfElements;     // Contador de elementos

public:
    Stack(): top(nullptr), numberOfElements(0) {}

    // Destrutor - remove todos os elementos
    ~Stack() {
        StackNode<T>* current = top;
        while(current) {
            StackNode<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    // Adiciona elemento no topo da pilha
    void push(const T& value) {
        StackNode<T>* newNode = new StackNode<T>(value);
        newNode->next = top;
        top = newNode;
        numberOfElements++;
    }

    // Remove elemento do topo da pilha
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

    // Retorna elemento do topo sem remover
    T getTop() const {
        if(top == nullptr) {
            std::cout << "The stack is empty" << std::endl;
            return T();
        }
        return top->data;
    }

    // Verifica se a pilha está vazia
    bool isEmpty() const {
        return (top == nullptr);
    }

    // Retorna o número de elementos na pilha
    int getNumberOfElements() const {
        return numberOfElements;
    }
};