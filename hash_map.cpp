#include "hash_map.h"
#include<iostream>


hash_map::hash_map(size_t capacity){
   _size = 0;
   _capacity = capacity;
   _head = new hash_list[_capacity];
}

hash_map::hash_map(const hash_map &other){
   _head = new hash_list[other._capacity];
   for(size_t i =0; i < other._capacity; i++) {
      _head[i] = other._head[i];
   }
}


void hash_map::insert(int key, float value){
   int new_key = abs(key) % _capacity;
   _head[new_key].insert(key,value);
   _size++;
}

std::optional<float> hash_map::get_value(int key)const{
   int new_key = abs(key) % _capacity;
   return _head[new_key].get_value(key);
}

hash_map &hash_map::operator=(const hash_map &other){
   delete[] _head; 
   _head = new hash_list[_capacity];
   for(size_t i = 0; i< other._capacity; i++){
      _head[i] = other._head[i];
   }
   return *this;
}

bool hash_map::remove(int key) { 
      int new_key = abs(key) % _capacity;
      bool is_removed = _head[new_key].remove(key);
      if(is_removed){
         _size--;
      }
   return is_removed; 
}

size_t hash_map::get_size() const{ 
   size_t _size = 0;

   for(size_t i =0; i < _capacity; i++) {
      if(_head){
         _size++;
      }
   }
   return _size;
}

size_t hash_map::get_capacity() const{ 
return _capacity;
}

void hash_map::get_all_keys(int *keys){
    
} 

void hash_map::get_bucket_sizes(size_t *buckets) { }

hash_map::~hash_map() {
   delete[] _head;
}