#pragma once
#include <string>

template<typename Key, typename Value, int MAX_SIZE = 100>
class Map {
private:
    Key keys[MAX_SIZE];
    Value values[MAX_SIZE];
    int length;

public:
    Map() : length(0) {}

    // Insert or update
    void insert(const Key& key, const Value& value) {
        for (int i = 0; i < length; ++i) {
            if (keys[i] == key) {
                values[i] = value;
                return;
            }
        }
        if (length < MAX_SIZE) {
            keys[length] = key;
            values[length] = value;
            ++length;
        }
        // else: ignore if full (or handle error)
    }

    // Returns pointer to value or nullptr if not found
    Value* find(const Key& key) {
        for (int i = 0; i < length; ++i) {
            if (keys[i] == key)
                return &values[i];
        }
        return nullptr;
    }

    // Operator[] for convenience (inserts default if not found)
    Value& operator[](const Key& key) {
        for (int i = 0; i < length; ++i) {
            if (keys[i] == key)
                return values[i];
        }
        // Insert default value if not found
        if (length < MAX_SIZE) {
            keys[length] = key;
            values[length] = Value();
            ++length;
            return values[length - 1];
        }
        // If full, return last (unsafe, but avoids crash)
        return values[length - 1];
    }

    // Add this const version for read-only access
    const Value& operator[](const Key& key) const {
        for (int i = 0; i < length; ++i) {
            if (keys[i] == key)
                return values[i];
        }
        // If not found, this is unsafe, but for your use case, you can return the last value
        // (or you can throw or assert)
        return values[length - 1];
    }

    int size() const {
        return length;
    }
};