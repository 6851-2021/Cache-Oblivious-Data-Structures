#include <iostream>
#include <stdlib.h>
#include <static_search_trees.h>
#include <time.h>

using namespace std;

void test_get_update_1() {
    // Test with a tree of size 15.
    CO_static_search_tree tree = CO_static_search_tree(15);
    tree.update(13, 200);
    if (tree.get(13) != 200) {
        cout << "test_get_update_1 failed: expected 200 at index 13." << endl;
        return;
    }
    tree.update(5, 24);
    if (tree.get(5) != 24) {
        cout << "test_get_update_1 failed: expected 24 at index 5." << endl;
        return;
    }
    tree.update(0, 10);
    if (tree.get(0) != 10) {
        cout << "test_get_update_1 failed: expected 10 at index 0." << endl;
        return;
    }
    tree.update(13, 55);
    if (tree.get(13) != 55) {
        cout << "test_get_update_1 failed: expected 55 at index 13." << endl;
        return;
    } else if (tree.get(5) != 24 || tree.get(0) != 10) {
        cout << "test_get_update_1 failed: modified values at incorrect indices." << endl;
        return;
    }
    cout << "test_get_update_1: OK" << endl;
}

void test_get_update_2() {
    // Test edge case with a tree of size 1.
    CO_static_search_tree tree = CO_static_search_tree(1);
    tree.update(0, 2);
    if (tree.get(0) != 2) {
        cout << "test_get_update_2 failed: expected 2 at index 0." << endl;
        return;
    }
    tree.update(0, 5);
    if (tree.get(0) != 5) {
        cout << "test_get_update_2 failed: expected 5 at index 0." << endl;
        return;
    }
    tree.update(0, 501);
    if (tree.get(0) != 501) {
        cout << "test_get_update_2 failed: expected 501 at index 0." << endl;
        return;
    }
    cout << "test_get_update_2: OK" << endl;
}

void test_get_update_3() {
    // -- This is a bit of stress test
    // Test update all elements in order from element 0 to last element.
    // make value = key. Do multiple passes with random tree sizes.
    srand(time(NULL));
    for (int i = 0; i < 100; i++) {
        // limit size to the range [0...10000]
        // no point in doing more.
        int t_size = 1 + rand() % 10000;
        CO_static_search_tree tree = CO_static_search_tree(t_size);
        for (int j = 0; j < t_size; j++) {
            tree.update(j, j);
        }
        for (int j = 0; j < t_size; j++) {
            if (tree.get(j) != j) {
                cout << "test_get_update_3 failed: expected value " << j << " at index " << j << ", tree size: " << t_size << endl;
                return;
            }
        }
    }
    cout << "test_get_update_3: OK" << endl;
}

void test_get_update_4() {
    // -- This is a bit of stress test
    // Test update all elements.
    // make value = key^2. Do multiple passes with random tree sizes.
    srand(time(NULL));
    for (int i = 0; i < 100; i++) {
        // limit size to the range [0...10000]
        // no point in doing more.
        int t_size = 1 + rand() % 10000;
        CO_static_search_tree tree = CO_static_search_tree(t_size);
        for (int j = 0; j < t_size; j++) {
            tree.update(j, j);
        }
        // now update them again but in BACKWARDS order.
        for (int j = t_size - 1; j >= 0; j--) {
            tree.update(j, j*j);
        }
        for (int j = 0; j < t_size; j++) {
            if (tree.get(j) != j*j) {
                cout << "test_get_update_4 failed: expected value " << j*j << " at index " << j << ", tree size: " << t_size << endl;
                return;
            }
        }
    }
    cout << "test_get_update_4: OK" << endl;
}

int main() {
    test_get_update_1();
    test_get_update_2();
    test_get_update_3();
    test_get_update_4();

    return 0;
}
