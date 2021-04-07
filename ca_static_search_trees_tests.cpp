#include <iostream>
#include <stdlib.h>
#include "static-search-trees.h"
#include <time.h>
#include <chrono>

using namespace std;

void print_array(int *a, int n) {
    printf("Array of length: %d\n", n);
    for (int i = 0; i < n; ++i){
        printf("%d ", a[i]);
    }
    printf("\n");
}

void test_get_update_1() {
    // Test with a tree of size 15.
    int n = 15;
    CA_static_search_tree tree(n);
    int a[15];
    a[0] = rand() % 10;
    // for (int i = 1; i < n; ++i) {
    //     a[i] = a[i - 1] + rand() % 10;
    //     tree.update(i, a[i]);
    // }

    for (int i = 0; i < n; ++i) {
        a[i] = i;
        tree.update(i, i);
    }

    int index;

    index = tree.get(a[13]);
    if (index != 13)
    {
        print_array(a, n);
        printf("test_get_update_1 failed: expected %d at index 13, got: %d\n", a[13], index);
        tree.print_tree();
        return;
    }

    index = tree.get(a[5]);
    if (index != 5)
    {
        print_array(a, n);
        printf("test_get_update_1 failed: expected %d at index 5, got: %d\n", a[5], index);
        return;
    }

    index = tree.get(a[0]);
    if (index != 0)
    {
        print_array(a, n);
        printf("test_get_update_1 failed: expected %d at index 0, got: %d\n", a[0], index);
        return;
    }

    index = tree.get(a[13]);
    if (index != 13)
    {
        print_array(a, n);
        printf("test_get_update_1 failed: expected %d at index 13, got: %d\n", a[13], index);
        return;
    }
    cout << "test_get_update_1: OK" << endl;
}

void test_get_update_2() {
    // Test edge case with a tree of size 1.
    CA_static_search_tree tree(1);
    tree.update(0, 2);
    if (tree.get(2) != 0) {
        cout << "test_get_update_2 failed: expected 2 at index 0." << endl;
        return;
    }
    tree.update(0, 5);
    if (tree.get(5) != 0) {
        cout << "test_get_update_2 failed: expected 5 at index 0." << endl;
        return;
    }
    tree.update(0, 501);
    if (tree.get(501) != 0) {
        cout << "test_get_update_2 failed: expected 501 at index 0." << endl;
        return;
    }
    cout << "test_get_update_2: OK" << endl;
}

void test_get_update_3() {
    // -- This is a bit of stress test
    // Test update all elements in order from element 0 to last element.
    // make value = key. Do multiple passes with random tree sizes.
    for (int i = 0; i < 100; i++) {
        // limit size to the range [0...10000]
        // no point in doing more.
        int t_size = 1 + rand() % 10000;
        CA_static_search_tree tree(t_size);
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
    for (int i = 0; i < 100; i++) {
        // limit size to the range [0...10000]
        // no point in doing more.
        int t_size = 1 + rand() % 10000;
        CA_static_search_tree tree(t_size);
        for (int j = 0; j < t_size; j++) {
            tree.update(j, j);
        }
        // now update them again but in BACKWARDS order.
        for (int j = t_size - 1; j >= 0; j--) {
            tree.update(j, j*j);
        }
        for (int j = 0; j < t_size; j++) {
            if (tree.get(j * j) != j) {
                cout << "test_get_update_4 failed: expected value " << j*j << " at index " << j << ", tree size: " << t_size << endl;
                return;
            }
        }
    }
    cout << "test_get_update_4: OK" << endl;
}
void test_get_update_5() {
    // -- This is a bit of stress test
    // Test update all elements.
    // make value = key^2. Do multiple passes with random tree sizes.
    for (int i = 0; i < 1; i++) {
        // limit size to the range [0...10000]
        // no point in doing more.
        int t_size = 5000000;
        CA_static_search_tree tree(t_size);
        for (int j = 0; j < t_size; j++) {
            tree.update(j, j);
        }
        // now update them again but in BACKWARDS order.
        for (int j = t_size - 1; j >= 0; j--) {
            tree.update(j, 2*j);
        }
        // for (int j = 0; j < t_size; j++) {
        //     if (tree.get(2*j) != j) {
        //         cout << "test_get_update_5 failed: expected value " << j*j << " at index " << j << ", tree size: " << t_size << endl;
        //         return;
        //     }
        // }
        for (int j = 0; j < t_size; j++) {
            if (tree.get(2*j) != j) {
                cout << "test_get_update_5 failed: expected value " << 2*j << " at index " << j << ", tree size: " << t_size << endl;
                return;
            }
            if (tree.get(2*(t_size-j-1)) != (t_size-j-1)) {
                cout << "test_get_update_5 failed: expected value " << 2*j << " at index " << j << ", tree size: " << t_size << endl;
                return;
            }
        }
    }
    cout << "test_get_update_5: OK" << endl;
}


int main() {
    srand(10);
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    test_get_update_1();
    test_get_update_2();
    test_get_update_3();
    test_get_update_4();
    test_get_update_5();
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Time difference = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    return 0;
}
