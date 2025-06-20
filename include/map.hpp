#pragma once
#include <string>

// Implementação simples de mapa usando arrays paralelos
// Limitado a MAX_SIZE elementos para simplicidade
template<typename Key, typename Value, int MAX_SIZE = 100>
class Map {
private:
    Key keys[MAX_SIZE];      // Array de chaves
    Value values[MAX_SIZE];  // Array de valores correspondentes
    int length;              // Número de pares chave-valor armazenados

public:
    Map() : length(0) {}

    // Insere ou atualiza par chave-valor
    void insert(const Key& key, const Value& value) {
        // Procura se chave já existe
        for (int i = 0; i < length; ++i) {
            if (keys[i] == key) {
                values[i] = value; // Atualiza valor existente
                return;
            }
        }
        // Adiciona novo par se há espaço
        if (length < MAX_SIZE) {
            keys[length] = key;
            values[length] = value;
            ++length;
        }
    }

    // Busca valor por chave (retorna ponteiro ou nullptr)
    Value* find(const Key& key) {
        for (int i = 0; i < length; ++i) {
            if (keys[i] == key)
                return &values[i];
        }
        return nullptr;
    }

    Value& operator[](const Key& key) {
        for (int i = 0; i < length; ++i) {
            if (keys[i] == key)
                return values[i];
        }
        if (length < MAX_SIZE) {
            keys[length] = key;
            values[length] = Value();
            ++length;
            return values[length - 1];
        }
        return values[length - 1];
    }

    const Value& operator[](const Key& key) const {
        for (int i = 0; i < length; ++i) {
            if (keys[i] == key)
                return values[i];
        }
        return values[length - 1];
    }

    const Value& operator[](int index) const {
        if (index >= 0 && index < length) {
            return values[index];
        }
        static Value defaultValue;
        return defaultValue;
    }

    int size() const {
        return length;
    }
};