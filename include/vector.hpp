#pragma once

template<typename T>
class Vector {
private:
    T* data;
    int capacity;
    int length;

    void resize(int newCapacity) {
        T* newData = new T[newCapacity];
        for (int i = 0; i < length; ++i)
            newData[i] = data[i]; // Consider if T needs deep copy too
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    Vector() : data(nullptr), capacity(0), length(0) {}

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

    // Copy Constructor
    Vector(const Vector& other) : data(nullptr), capacity(0), length(0) {
        if (other.length > 0) {
            data = new T[other.capacity]; // Allocate memory
            capacity = other.capacity;
            length = other.length;
            for (int i = 0; i < length; ++i) {
                data[i] = other.data[i]; // Copy elements
            }
        }
    }

    // Copy Assignment Operator
    Vector& operator=(const Vector& other) {
        if (this == &other) { // Self-assignment check
            return *this;
        }

        delete[] data; // Free existing resource

        data = nullptr;
        capacity = 0;
        length = 0;

        if (other.length > 0) {
            data = new T[other.capacity]; // Allocate memory
            capacity = other.capacity;
            length = other.length;
            for (int i = 0; i < length; ++i) {
                data[i] = other.data[i]; // Copy elements
            }
        }
        return *this;
    }

    ~Vector() {
        delete[] data;
    }

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