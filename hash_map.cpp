#include "hash_map.h"
#include<iostream>

 int main() { 
    std::cout <<"running" << std::endl;
    return 0;
 }

hash_map::hash_map(size_t capacity){
   _size = 0;
   _capacity = capacity;
   _head = new hash_list[_capacity];
}

hash_map::hash_map(const hash_map &other){
   _size = 0;
   _head = new hash_list[other._capacity];
   for(size_t i =0; i < other._capacity; i++) {
      _head[i] = other._head[i];
   }
}


void hash_map::insert(int key, float value){

}

//std::optional<float> get_value(int key) const{}

/*bool hash_map::remove(int key) { 
}
*/
size_t hash_map::get_size() const{ 
   size_t _size = 0;

   for(size_t i =0; i < _capacity; i++) {
      if(_head){
         _size++;
      }
   }
   return _size;
}/*
size_t hash_map::get_capacity() const{ 

}*/

void hash_map::get_all_keys(int *keys){} 

void hash_map::get_bucket_sizes(size_t *buckets) { }

