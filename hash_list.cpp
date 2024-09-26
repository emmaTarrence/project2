#include "hash_list.h"
#include "hash_map.h"

#include <iostream>
hash_list::hash_list() : size(0), head(nullptr), iter_ptr(nullptr) {}
//constructor 
//where we set up the l

/**-----------------------------------------------------------------------------------
* START Part 1
*------------------------------------------------------------------------------------*/
template <typename K, typename V>
void hash_list::insert(K key, V value) {
   node<k,V>* current = head; 
   if(head == nullptr) {
       head = new node<K,V>(); //allocate memory 
       head->key = key;
       head->value = value; 
       head->next = nullptr;
       size = size + 1; 
       return; 
   }
   else{
       while(current != nullptr) { 
       
           if(current->key == key){
               current->value = value; 
               return;
           }
           current = current->next;
       }
       node* newNode= new node<K,V>();
       newNode->key = key;
       newNode->value = value;
       newNode->next = head;
       head = newNode;

   }

}

template <typename K, typename V>
std::optional<V> hash_list<K,V>::get_value(K key) const { 
   node* current = head; 
   while(current != nullptr) { 
         
       if(current->key == key){
           return  current->value;
       }
       current = current->next;
   }
   return std::nullopt; 
}

bool hash_list<K,V>::remove(K key) { 
   node<K,V>* curr = head; 
   node<K,V>* prev = nullptr;
   
   while (curr != nullptr){
       if (curr->key == key) {
           if (prev == nullptr){
               head = curr->next; 
           } else {
           prev->next = curr->next; 
           }

           delete curr; 
           size--; 
           return true; 
       }
       prev = curr; 
       curr = curr -> next;
   }

   return false;
}

template <typename K< typename V>
size_t hash_list::<K,V>get_size() const { 
       node<K,V>* current = head; 
       size_t count = 0;
   while(current != nullptr) { 
       count++;
             current = current->next;
}
return count;
}

templat < typename K, typename V>
hash_list<K,V>::~hash_list() {
   node<K,V>*current = head;
   while(current != nullptr){
       node<K,V>* next = current->next;
       delete current;
       current = next;
   }
   head = nullptr;
}


/**-----------------------------------------------------------------------------------
* END Part 1
*------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------
* START Part 2
*------------------------------------------------------------------------------------*/

tmeplate <typename K, typename V>
hash_list<K,V>::hash_list(const hash_list &other) {
   if (other.head == nullptr) {
        head = nullptr;
        size = 0;
        return;
   }

   head = new node<K,V>();
   head->key = other.head->key;
   head->value = other.head->value;

   node<K,V>* current = head;
   node<K,V>* other_current = other.head->next;
   
   while (other_current != nullptr) {
       current->next = new node<K,V>();
       current = current->next;
       current->key = other_current->key;
       current->value = other_current->value;
       other_current = other_current->next;
   }
   current->next = nullptr; 
   size = other.size;
}

template <typename K, typename V>
hash_list<K,V> &hash_list<K,V>::operator=(const hash_list &other) {     
    if (this == &other) return *this;

  
    node<K,V>* current = head;
    while (current != nullptr) {
        node<K,V>* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;

    size =  0;
    
    if (other.head == nullptr) {
        return *this;
    } 
        head = new node<K,V>();
        head->key = other.head->key;
        head->value = other.head->value;
        
    node* this_current = head;
    node* other_current = other.head->next;

    while (other_current != nullptr) {
        this_current->next = new node<K,V>();
        this_current = this_current->next;
        this_current->key = other_current->key;
        this_current->value = other_current->value;
        other_current = other_current->next;
    }
    this_current->next = nullptr; // Ensure last node's next is nullptr
    size = other.size;

    return *this;
}

template <typename K, typename V>
void hash_list<K,V>::reset_iter() {
   iter_ptr = head;
}

template <typename K, typename V>
void hash_list<K,V>::increment_iter() {
   if (iter_ptr != nullptr) {
       iter_ptr = iter_ptr->next;
   }
}

template <typename K, typename V> 
std::optional<std::pair<const K *, V *>> hash_list<K,V>::get_iter_value() { 
   if (iter_ptr == nullptr) {
       return std::nullopt;
   }
   return std::make_optional(std::make_pair(&iter_ptr->key, &iter_ptr->value));
}

template <typename K, typename V> 
bool hash_list<K,V>::iter_at_end() { 
       return iter_ptr == nullptr;
}
/**-----------------------------------------------------------------------------------
* END Part 2
*------------------------------------------------------------------------------------*/

