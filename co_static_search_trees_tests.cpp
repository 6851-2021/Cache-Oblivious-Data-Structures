#include <iostream>
#include <stdlib.h>
#include "static-search-trees.h"
// #include <time.h>
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
    CO_static_search_tree tree(n);
    int a[15];
    a[0] = rand() % 10;
    for (int i = 1; i < n; ++i) {
        a[i] = a[i - 1] + rand() % 10;
        tree.update(i, a[i]);
    }

    for (int i = 0; i < n; ++i) {
        tree.update(i, a[i]);
    }

    int index;

    index = tree.get(a[13]);
    if (index != 13)
    {
        print_array(a, n);
        printf("test_get_update_1 failed: expected %d at index 13, got: %d\n", a[13], index);
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
    CO_static_search_tree tree(1);
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
        CO_static_search_tree tree(t_size);
        for (int j = 0; j < t_size; j++) {
            tree.update(j, j);
        }
        for (int j = 0; j < t_size; j++) {
            int index = tree.get(j);
            if (index != j)
            {
                cout << "test_get_update_3 failed: expected value " << j << " at index " << j << ", tree size: " << t_size <<", got: "<<index<< endl;
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
        CO_static_search_tree tree(t_size);
        for (int j = 0; j < t_size; j++) {
            tree.update(j, j);
        }
        // now update them again but in BACKWARDS order.
        for (int j = t_size - 1; j >= 0; j--) {
            tree.update(j, j*j);
        }
        for (int j = 0; j < t_size; j++) {
            int index = tree.get(j * j);
            if (index != j)
            {
                cout << "test_get_update_4 failed: expected value " << j*j << " at index " << j << ", tree size: " << t_size <<", got: "<<index<< endl;
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
        CO_static_search_tree tree(t_size);
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

void test_range_update_small() {
    const int n = 8;
    CO_static_search_tree tree(n);
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7};
    tree.range_update(0, n - 1, arr);
    cout << "First Update" << endl;
    for (int i = 0; i < n; ++i)
    {
        int result = tree.get(i);
        if (result != i)
        {
            printf("Incorrect index for query value %d, got %d, expected %d\n", i, result, i);
            exit(-1);
        }
    }

    arr[5] = 10;
    arr[6] = 17;
    arr[7] = 20;
    tree.range_update(5, 7, arr);

    for (int i = 0; i < 5 ; ++i) {
        int result = tree.get(i);
        if (result != i)
        {
            printf("Incorrect index for query value %d, got %d, expected %d\n", i, result, i);
            exit(-1);
        }
    }
    for (int i = 5; i <= 10 ; ++i) {
        int result = tree.get(i);
        int expected = 5;
        if (result != expected)
        {
            printf("Incorrect index for query value %d, got %d, expected %d\n", i, result, expected);
            exit(-1);
        }
    }

    for (int i = 11; i <= 17 ; ++i) {
        int result = tree.get(i);
        int expected = 6;
        if (result != expected)
        {
            printf("Incorrect index for query value %d, got %d, expected %d\n", i, result, expected);
            exit(-1);
        }
    }

    for (int i = 18; i <= 20 ; ++i) {
        int result = tree.get(i);
        int expected = 7;
        if (result != expected)
        {
            printf("Incorrect index for query value %d, got %d, expected %d\n", i, result, expected);
            exit(-1);
        }
    }

    for (int i = 21; i <= 25 ; ++i) {
        int result = tree.get(i);
        int expected = -1;
        if (result != expected)
        {
            printf("Incorrect index for query value %d, got %d, expected %d\n", i, result, expected);
            exit(-1);
        }
    }
    cout << "Range Update Small: Success\n";
}

void test_range_update_uniform(const int n) {
    CO_static_search_tree tree(n);
    int arr[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = i * 5;
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j){
            arr[j] = j * 5;
        }
        int len = rand() % (n / 2) + 1;
        int R = min(i + len - 1, n - 1);
        tree.range_update(i, R, arr);

        i += (len - 1);
    }
    for (int i = 0; i < (n - 1) * 5; ++i) {
        int result = tree.get(i);
        int expected = ceil(i / 5.0);
        if (result != expected)
        {
            printf("Incorrect index for query value %d, got %d, expected %d\n", i, result, expected);
            exit(-1);
        }
    }
    cout << "Success range update uniform: " << n << endl;
}

int main() {
    srand(10);
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    test_get_update_1();
    test_get_update_2();
    test_get_update_3();
    test_get_update_4();
    test_get_update_5();
    test_range_update_small();
    test_range_update_uniform(16);
    test_range_update_uniform(20);
    test_range_update_uniform(100);
    test_range_update_uniform(500);
    test_range_update_uniform(1e6);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Time difference = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    return 0;
}
