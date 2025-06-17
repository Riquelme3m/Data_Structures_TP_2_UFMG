#pragma once

template<typename T>
struct QueueNode {
    T data;
    QueueNode<T>* next;
    QueueNode(const T& d) : data(d), next(nullptr) {}
};

template<typename T>
class Queue {
private:
    QueueNode<T>* frontNode;
    QueueNode<T>* rearNode;
    int count;

public:
    Queue() : frontNode(nullptr), rearNode(nullptr), count(0) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(const T& value) {
        QueueNode<T>* node = new QueueNode<T>(value);
        if (rearNode) {
            rearNode->next = node;
        } else {
            frontNode = node;
        }
        rearNode = node;
        count++;
    }

    void dequeue() {
        if (isEmpty()) return;
        QueueNode<T>* temp = frontNode;
        frontNode = frontNode->next;
        if (!frontNode) rearNode = nullptr;
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