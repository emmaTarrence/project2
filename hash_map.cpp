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