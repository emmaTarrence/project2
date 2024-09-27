#include<iostream>
#include<optional>


template<typename K, typename V>
hash_map<K,V>::hash_map(size_t capacity,
             float upper_load_factor,
             float lower_load_factor) {
    _size = 0;
    _capacity = find_nearest_capacity(capacity);
    _head = new hash_list<K,V>[_capacity];
    _upper_load_factor = upper_load_factor;
    _lower_load_factor = lower_load_factor;  
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
    int new_key = _hash(key) % _capacity;  
    std::optional<V> existing_value = _head[new_key].get_value(key);
    if (!existing_value.has_value()) {
        _size++;  
    }
    _head[new_key].insert(key, value); 
    if(checkRehash()) { 
      //  std::cout << "in loop"  << std::endl;
        rehash(_capacity);
       
    }
}

template<typename K, typename V>
std::optional<V> hash_map<K,V>::get_value(K key) const {
    int new_key = _hash(key) % _capacity;  
    return _head[new_key].get_value(key);  
}

template<typename K, typename V>
bool hash_map<K,V>::remove(K key) {
    int new_key = _hash(key) % _capacity; 
    bool is_removed = _head[new_key].remove(key); 
    if (is_removed) {
        _size--;  
    }
        if(checkRehash()) { 
        rehash(_capacity);
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
    if(index < _size){ 
                keys[index] = *(iter_value->first); 
                index++;
            }
            else { 
                break;
            }
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


template<typename K, typename V>
bool hash_map<K,V>::checkRehash() {
    bool needs_rehash = (_size > (_upper_load_factor * _capacity)) || (_size < (_lower_load_factor * _capacity / 4)); // Adjust lower load factor check
    //std::cout << "Check rehash: " << needs_rehash << std::endl;
    return needs_rehash;
}

template<typename K, typename V>
 void hash_map<K,V>::get_all_sorted_keys(K *keys){
    size_t new_key = 0;
    for(size_t i = 0; i < _capacity; i ++) { 
        _head[i].reset_iter();
        while(!_head[i].iter_at_end()){
            std::optional<std::pair<const K*, V*>> iter_value = _head[i].get_iter_value();
            if(iter_value.has_value()){
                if(new_key <_size) { 
                    keys[new_key] = *(iter_value->first);
                    new_key++;
                }
                else{
                    break;
                }
            }
            _head[i].increment_iter();
        }
    }
    for(size_t i = 0; i < _size -1; i++) { 
        for(size_t j = 0; j < _size -1; j++){
            if(keys[j] > keys [j + 1]){
                K temp = keys[j];
                keys[j] = keys[j+ 1];
                keys[j+1] = temp;
            }
        }
    }
 }
 template<typename K, typename V>
size_t hash_map<K, V>::find_nearest_capacity(size_t new_capacity) {
    // Default to the first capacity
    size_t nearest = _capacities[0];
    size_t min_diff = std::abs(static_cast<int>(new_capacity) - static_cast<int>(nearest));

    for (size_t capacity : _capacities) {
        size_t diff = std::abs(static_cast<int>(new_capacity) - static_cast<int>(capacity));
        if (diff < min_diff) {
            min_diff = diff;
            nearest = capacity;
        }
    }
    return nearest;
}

template<typename K, typename V>
void hash_map<K, V>::rehash(size_t new_capacity) {
    new_capacity = find_nearest_capacity(new_capacity * 2 );

    //std::cout << "Rehashing from capacity " << _capacity << " to " << new_capacity << std::endl;
    if(new_capacity == _capacity) { 
        return;
    }
    hash_list<K, V>* new_head = new hash_list<K, V>[new_capacity];  
    size_t old_capacity = _capacity; 
    hash_list<K, V>* old_head = _head;

    _head = new_head; 
    _capacity = new_capacity; 
    _size = 0; 

    for (size_t i = 0; i < old_capacity; ++i) {
        old_head[i].reset_iter(); 
        while (!old_head[i].iter_at_end()) {
            auto iter_value = old_head[i].get_iter_value();
            if (iter_value.has_value()) {
                insert(*(iter_value->first), *(iter_value->second));
            }
            old_head[i].increment_iter();
        }
    }

    delete[] old_head;  
}
