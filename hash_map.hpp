#include<iostream>
#include<optional>
#include "hash_map.h"
#include "hash_list.h"


template<typename K, typename V>
hash_map<K,V>::hash_map(size_t capacity,
             float upper_load_factor,
             float lower_load_factor) {
    _size = 0;
    _capacity = capacity;
    _head = new hash_list<K,V>[_capacity];  
}

template<typename K, typename V>
hash_map<K,V>::hash_map(const hash_map &other) {
    _capacity = other._capacity;
    _size = other._size;
    _head = new hash_list<K,V>[_capacity];
    for (size_t i = 0; i < other._capacity; i++) {
        _head[i] = other._head[i];  
    }
}

template<typename K, typename V>
hash_map<K,V> &hash_map<K,V>::operator=(const hash_map &other) {
    if (this == &other) return *this;
    delete[] _head;  
    _capacity = other._capacity;
    _size = other._size;
    _head = new hash_list<K,V>[_capacity];
    for (size_t i = 0; i < _capacity; i++) {
        _head[i] = other._head[i];  
    }
    return *this;
}

template<typename K, typename V>
void hash_map<K,V>::insert(K key, V value) {
    int new_key = abs(key) % _capacity;  
    std::optional<float> existing_value = _head[new_key].get_value(key);
    if (!existing_value.has_value()) {
        _size++;  
    }
    _head[new_key].insert(key, value); 
}

template<typename K, typename V>
std::optional<V> hash_map<K,V>::get_value(K key) const {
    int new_key = abs(key) % _capacity;  
    return _head[new_key].get_value(key);  
}

template<typename K, typename V>
bool hash_map<K,V>::remove(K key) {
    int new_key = abs(key) % _capacity; 
    bool is_removed = _head[new_key].remove(key); 
    if (is_removed) {
        _size--;  
    }
    return is_removed;
}

template<typename K, typename V>
size_t hash_map<K,V>::get_size() const {
    return _size;  
}

template<typename K, typename V>
size_t hash_map<K,V>::get_capacity() const {
    return _capacity;  
}

template<typename K, typename V>
void hash_map<K,V>::get_all_keys(K *keys) {
    size_t index = 0;
    for (size_t i = 0; i < _capacity; i++) {
        _head[i].reset_iter();  
        while (!_head[i].iter_at_end()) {
            std::optional<std::pair<const K *, V *>> iter_value = _head[i].get_iter_value();
if (iter_value.has_value()) {
                keys[index] = *(iter_value->first); 
                index++;
            }
            _head[i].increment_iter();  
        }
    }
}

template<typename K, typename V>
void hash_map<K,V>::get_bucket_sizes(size_t *buckets) {
    for (size_t i = 0; i < _capacity; ++i) {
        buckets[i] = _head[i].get_size(); 
    }
}

template<typename K, typename V>
hash_map<K,V>::~hash_map() {
    delete[] _head;  
}
