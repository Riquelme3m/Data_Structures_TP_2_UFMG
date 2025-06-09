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
            newData[i] = data[i];
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