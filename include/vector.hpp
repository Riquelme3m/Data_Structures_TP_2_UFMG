#pragma once

template<typename T>
class Vector {
private:
    T* data;
    int capacity; // Capacidade atual do array
    int length;   // Número de elementos armazenados

    // Redimensiona o array quando necessário
    void resize(int newCapacity) {
        T* newData = new T[newCapacity];
        // Copia elementos existentes para o novo array
        for (int i = 0; i < length; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    Vector() : data(nullptr), capacity(0), length(0) {}

    // Construtor que cria vector com n elementos iguais a value
    Vector(int n, const T& value) : data(nullptr), capacity(0), length(0) {
        if (n > 0) {
            data = new T[n];
            capacity = n;
            length = n;
            for (int i = 0; i < n; ++i) {
                data[i] = value;
            }
        }
    }

    // Construtor de cópia
    Vector(const Vector& other) : data(nullptr), capacity(0), length(0) {
        if (other.length > 0) {
            data = new T[other.capacity];
            capacity = other.capacity;
            length = other.length;
            for (int i = 0; i < length; ++i) {
                data[i] = other.data[i];
            }
        }
    }

    // Operador de atribuição
    Vector& operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }

        delete[] data;

        data = nullptr;
        capacity = 0;
        length = 0;

        if (other.length > 0) {
            data = new T[other.capacity];
            capacity = other.capacity;
            length = other.length;
            for (int i = 0; i < length; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    ~Vector() {
        delete[] data;
    }

    // Adiciona elemento no final (redimensiona se necessário)
    void push_back(const T& value) {
        if (length == capacity) {
            int newCapacity = (capacity == 0) ? 2 : capacity * 2;
            resize(newCapacity);
        }
        data[length++] = value;
    }

    void pop_back() {
        if (length > 0) {
            length--;
        }
    }

    T& operator[](int idx) {
        return data[idx];
    }

    const T& operator[](int idx) const {
        return data[idx];
    }

    int size() const {
        return length;
    }

    void clear() {
        length = 0;
    }
};