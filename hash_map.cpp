#include "hash_map.h"
#include<iostream>

hash_map::hash_map(size_t capacity) {
    _size = 0;
    _capacity = capacity;
    _head = new hash_list[_capacity];  
}

hash_map::hash_map(const hash_map &other) {
    _capacity = other._capacity;
    _size = other._size;
    _head = new hash_list[_capacity];
    for (size_t i = 0; i < other._capacity; i++) {
        _head[i] = other._head[i];  
    }
}

hash_map &hash_map::operator=(const hash_map &other) {
    if (this == &other) return *this;
    delete[] _head;  
    _capacity = other._capacity;
    _size = other._size;
    _head = new hash_list[_capacity];
    for (size_t i = 0; i < _capacity; i++) {
        _head[i] = other._head[i];  
    }
    return *this;
}

void hash_map::insert(int key, float value) {
    int new_key = abs(key) % _capacity;  
    std::optional<float> existing_value = _head[new_key].get_value(key);
    if (!existing_value.has_value()) {
        _size++;  
    }
    _head[new_key].insert(key, value); 
}

std::optional<float> hash_map::get_value(int key) const {
    int new_key = abs(key) % _capacity;  
    return _head[new_key].get_value(key);  
}

bool hash_map::remove(int key) {
    int new_key = abs(key) % _capacity; 
    bool is_removed = _head[new_key].remove(key); 
    if (is_removed) {
        _size--;  
    }
    return is_removed;
}

size_t hash_map::get_size() const {
    return _size;  
}

size_t hash_map::get_capacity() const {
    return _capacity;  
}

void hash_map::get_all_keys(int *keys) {
    size_t index = 0;
    for (size_t i = 0; i < _capacity; i++) {
        _head[i].reset_iter();  
        while (!_head[i].iter_at_end()) {
            std::optional<std::pair<const int *, float *>> iter_value = _head[i].get_iter_value();
            if (iter_value.has_value()) {
                keys[index] = *(iter_value->first); 
                index++;
            }
            _head[i].increment_iter();  
        }
    }
}

void hash_map::get_bucket_sizes(size_t *buckets) {
    for (size_t i = 0; i < _capacity; ++i) {
        buckets[i] = _head[i].get_size(); 
    }
}

hash_map::~hash_map() {
    delete[] _head;  
}
