#include "hash_list.h"
#include "hash_map.h"

#include <iostream>
hash_list::hash_list() : size(0), head(nullptr), iter_ptr(nullptr) {}
//constructor 
//where we set up the l

/**-----------------------------------------------------------------------------------
* START Part 1
*------------------------------------------------------------------------------------*/

void hash_list::insert(int key, float value) {
   node* current = head; 
   if(head == nullptr) {
       head = new node(); //allocate memory 
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
       node* newNode= new node();
       newNode->key = key;
       newNode->value = value;
       newNode->next = head;
       head = newNode;

   }

}

std::optional<float> hash_list::get_value(int key) const { 
   node* current = head; 
   while(current != nullptr) { 
         
       if(current->key == key){
           return  current->value;
       }
       current = current->next;
   }
   return std::nullopt; 
}

bool hash_list::remove(int key) { 
   node* curr = head; 
   node* prev = nullptr;
   
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

size_t hash_list::get_size() const { 
       node* current = head; 
       size_t count = 0;
   while(current != nullptr) { 
       count++;
             current = current->next;
}
return count;
}

hash_list::~hash_list() {
   node*current = head;
   while(current != nullptr){
       node* next = current->next;
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

hash_list::hash_list(const hash_list &other) {
   if (other.head == nullptr) {
        head = nullptr;
        size = 0;
        return;
   }

   head = new node();
   head->key = other.head->key;
   head->value = other.head->value;

   node* current = head;
   node* other_current = other.head->next;
   
   while (other_current != nullptr) {
       current->next = new node();
       current = current->next;
       current->key = other_current->key;
       current->value = other_current->value;
       other_current = other_current->next;
   }
   current->next = nullptr; 
   size = other.size;
}

hash_list &hash_list::operator=(const hash_list &other) {     
    if (this == &other) return *this;

  
    node* current = head;
    while (current != nullptr) {
        node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;

    size =  0;
    
    if (other.head == nullptr) {
        return *this;
    } 
        head = new node();
        head->key = other.head->key;
        head->value = other.head->value;
        
    node* this_current = head;
    node* other_current = other.head->next;

    while (other_current != nullptr) {
        this_current->next = new node();
        this_current = this_current->next;
        this_current->key = other_current->key;
        this_current->value = other_current->value;
        other_current = other_current->next;
    }
    this_current->next = nullptr; // Ensure last node's next is nullptr
    size = other.size;

    return *this;
}

void hash_list::reset_iter() {
   iter_ptr = head;
}


void hash_list::increment_iter() {
   if (iter_ptr != nullptr) {
       iter_ptr = iter_ptr->next;
   }
}


std::optional<std::pair<const int *, float *>> hash_list::get_iter_value() { 
   if (iter_ptr == nullptr) {
       return std::nullopt;
   }
   return std::make_optional(std::make_pair(&iter_ptr->key, &iter_ptr->value));
}


bool hash_list::iter_at_end() { 
       return iter_ptr == nullptr;
}
/**-----------------------------------------------------------------------------------
* END Part 2
*------------------------------------------------------------------------------------*/

