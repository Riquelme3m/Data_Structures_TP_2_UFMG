#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include "vector.hpp"

// Implementação de Min-Heap usando array dinâmico
// Usado para manter eventos ordenados por prioridade (tempo)
template<typename T>
class MinHeap {
private:
    Vector<T> heap;
    
    // Funções auxiliares para navegação na árvore
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    // Restaura propriedade do heap subindo elementos
    void heapifyUp(int index) {
        while (index > 0 && heap[parent(index)] > heap[index]) {
            T temp = heap[index];
            heap[index] = heap[parent(index)];
            heap[parent(index)] = temp;
            index = parent(index);
        }
    }
    
    // Restaura propriedade do heap descendo elementos
    void heapifyDown(int index) {
        int minIndex = index;
        int left = leftChild(index);
        int right = rightChild(index);
        
        // Encontra o menor entre pai e filhos
        if (left < heap.size() && heap[left] < heap[minIndex]) {
            minIndex = left;
        }
        
        if (right < heap.size() && heap[right] < heap[minIndex]) {
            minIndex = right;
        }
        
        // Se necessário, troca e continua descendo
        if (index != minIndex) {
            T temp = heap[index];
            heap[index] = heap[minIndex];
            heap[minIndex] = temp;
            heapifyDown(minIndex);
        }
    }
    
public:
    MinHeap() {}
    
    // Insere elemento mantendo propriedade do min-heap
    void insert(const T& item) {
        heap.push_back(item);
        heapifyUp(heap.size() - 1);
    }
    
    // Remove e retorna o menor elemento (raiz)
    T extractMin() {
        if (heap.size() == 0) {
            throw std::runtime_error("Heap vazio");
        }
        
        T min = heap[0];
        heap[0] = heap[heap.size() - 1]; // Move último para raiz
        heap.pop_back();
        
        if (heap.size() > 0) {
            heapifyDown(0); // Restaura propriedade
        }
        
        return min;
    }
    
    const T& getMin() const {
        if (heap.size() == 0) {
            throw std::runtime_error("Heap vazio");
        }
        return heap[0];
    }
    
    bool isEmpty() const {
        return heap.size() == 0;
    }
    
    int size() const {
        return heap.size();
    }
    
    void clear() {
        heap.clear();
    }
};

#endif
