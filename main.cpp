#include <iostream>
#include <cassert>
#include "hash_map.h"

void test_hash_map() {
    // Create a hash map with initial capacity, upper and lower load factors
    hash_map<int, std::string> map(10, 0.7f, 0.2f);

    // Test insertion
    map.insert(1, "One");
    map.insert(2, "Two");
    map.insert(3, "Three");

    // Test size after insertions
    assert(map.get_size() == 3);
    std::cout << "Insertion test passed. Size: " << map.get_size() << std::endl;

    // Test retrieval
    auto value = map.get_value(2);
    assert(value.has_value() && value.value() == "Two");
    std::cout << "Retrieval test passed. Value: " << value.value() << std::endl;

    // Test retrieval of a non-existing key
    auto non_existing_value = map.get_value(4);
    assert(!non_existing_value.has_value());
    std::cout << "Non-existing retrieval test passed." << std::endl;

    // Test removal
    bool removed = map.remove(2);
    assert(removed);
    assert(map.get_size() == 2);
    assert(!map.get_value(2).has_value());
    std::cout << "Removal test passed. Size: " << map.get_size() << std::endl;

    // Test rehashing by exceeding the upper load factor
    for (int i = 4; i <= 10; i++) {
        map.insert(i, "Value " + std::to_string(i));
        std::cout <<"adding: "<< i <<std::endl;
    }

    // Check size and capacity after rehashing
    assert(map.get_size() == 7);
    assert(map.get_capacity() > 10); // Ensure capacity increased
    std::cout << "Rehashing test passed. New Size: " << map.get_size() << ", New Capacity: " << map.get_capacity() << std::endl;

    // Test retrieving all keys
    int keys[10];
    map.get_all_keys(keys);
    std::cout << "All keys: ";
    for (size_t i = 0; i < map.get_size(); i++) {
        std::cout << keys[i] << " ";
    }
    std::cout << std::endl;

    // Test sorted keys
    int sorted_keys[10];
    map.get_all_sorted_keys(sorted_keys);
    std::cout << "Sorted keys: ";
    for (size_t i = 0; i < map.get_size(); i++) {
        std::cout << sorted_keys[i] << " ";
    }
    std::cout << std::endl;

    // Test bucket sizes
    size_t bucket_sizes[map.get_capacity()];
    map.get_bucket_sizes(bucket_sizes);
    std::cout << "Bucket sizes: ";
    for (size_t i = 0; i < map.get_capacity(); i++) {
        std::cout << bucket_sizes[i] << " ";
    }
    std::cout << std::endl;

    // Cleanup is handled by the destructor
}

int main() {
    test_hash_map();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
