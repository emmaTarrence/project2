#include <iostream>
#include "hash_map.h"

void test_insert() {
    std::cout << "Testing insert function...\n";
    hash_map<int, float> map(10, 0.75, 0.5);  // Example capacity and load factor

    map.insert(1, 1.1f);
    map.insert(2, 2.2f);
    map.insert(3, 3.3f);

    if (map.get_value(1) == 1.1f && map.get_value(2) == 2.2f && map.get_value(3) == 3.3f) {
        std::cout << "Insert test passed.\n";
    } else {
        std::cout << "Insert test failed.\n";
    }
}

void test_remove() {
    std::cout << "Testing remove function...\n";
    hash_map<int, float> map(10, 0.75, 0.5);

    map.insert(1, 1.1f);
    map.insert(2, 2.2f);
    map.remove(1);

    if (map.get_size() == 1 && map.get_value(2) == 2.2f) {
        std::cout << "Remove test passed.\n";
    } else {
        std::cout << "Remove test failed.\n";
    }
}

void test_get_value() {
    std::cout << "Testing get_value function...\n";
    hash_map<int, float> map(10, 0.75, 0.5);

    map.insert(1, 1.1f);
    map.insert(2, 2.2f);

    if (map.get_value(1) == 1.1f && map.get_value(2) == 2.2f) {
        std::cout << "Get value test passed.\n";
    } else {
        std::cout << "Get value test failed.\n";
    }
}

void test_resize() {
    std::cout << "Testing resize function...\n";
    hash_map<int, float> map(3, 0.75, 0.5);  // Smaller capacity to trigger resizing

    map.insert(1, 1.1f);
    map.insert(2, 2.2f);
    map.insert(3, 3.3f);  // This should cause a resize

    if (map.get_capacity() > 3) {  // Assuming get_capacity() returns the capacity
        std::cout << "Resize test passed.\n";
    } else {
        std::cout << "Resize test failed.\n";
    }
}

int main() {
    test_insert();
    test_remove();
    test_get_value();
    test_resize();
    std::cout << "All tests complete.\n";
    return 0;
}
