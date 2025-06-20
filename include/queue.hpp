#pragma once

// Nó da fila - estrutura auxiliar
template<typename T>
struct QueueNode {
    T data;
    QueueNode<T>* next;
    QueueNode(const T& d) : data(d), next(nullptr) {}
};

// Implementação de fila usando lista ligada (FIFO - First In, First Out)
template<typename T>
class Queue {
private:
    QueueNode<T>* frontNode; // Ponteiro para o primeiro elemento
    QueueNode<T>* rearNode;  // Ponteiro para o último elemento
    int count;               // Contador de elementos

public:
    Queue() : frontNode(nullptr), rearNode(nullptr), count(0) {}

    // Destrutor - remove todos os elementos
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // Adiciona elemento no final da fila
    void enqueue(const T& value) {
        QueueNode<T>* node = new QueueNode<T>(value);
        if (rearNode) {
            rearNode->next = node;
        } else {
            frontNode = node; // Primeiro elemento
        }
        rearNode = node;
        count++;
    }

    // Remove elemento do início da fila
    void dequeue() {
        if (isEmpty()) return;
        QueueNode<T>* temp = frontNode;
        frontNode = frontNode->next;
        if (!frontNode) rearNode = nullptr; // Fila ficou vazia
        delete temp;
        count--;
    }

    T& front() {
        return frontNode->data;
    }

    bool isEmpty() const {
        return frontNode == nullptr;
    }

    int size() const {
        return count;
    }


};