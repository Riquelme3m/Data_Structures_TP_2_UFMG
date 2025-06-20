#pragma once
#include<iostream>

// Nó da lista duplamente encadeada
template<typename T>
struct Node{
    T data;
    Node<T>* next; // Ponteiro para próximo nó
    Node<T>* prev; // Ponteiro para nó anterior
    Node(const T& d): data(d),next(nullptr),prev(nullptr){}
};

// Lista duplamente encadeada - permite navegação bidirecional
// Usada para representar rotas de pacotes
template<typename T>
class DoublyLinkedList{
    private:
        Node<T>* head; // Primeiro nó da lista
        Node<T>* tail; // Último nó da lista

    public:
        DoublyLinkedList():head(nullptr),tail(nullptr){}

        // Destrutor - remove todos os nós
        ~DoublyLinkedList(){
            Node<T>* current=head;

            while(current){
                Node<T>* next = current->next;

                delete current;

                current=next;
            }
        }

        // Adiciona elemento no final da lista
        void append(const T& value){
            Node<T>* newNode = new Node<T>(value);

            if(!head){
                head=tail=newNode; // Primeiro elemento
            }
            else{
                tail->next=newNode;
                newNode->prev=tail;
                tail=newNode;
            }
        }

        // Adiciona elemento no início da lista
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

        bool isEmpty() const {
            return head == nullptr;
        }
};