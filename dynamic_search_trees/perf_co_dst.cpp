#include "co_dynamic_search_tree.h"
#include <random>

void test(int max_value, int Q) {
    co_dynamic_serach_tree tree;
    for (int i = 0; i <= max_value; i++){
        tree.add(i * 7);
    }
    while (Q--)
    {
        int query_type = rand() % 12;
        if (query_type < 4)
        {
            int value = rand() % max_value;
            tree.add(value * 7);
        } else {
            int value = rand() % (max_value * 7);
            int result = tree.get_successor(value);
            int expected = ceil(value / 7.0) * 7;
            if (result != expected)
            {
                printf("Failure. Successor for %d, expected: %d, got: %d\n", value, expected, result);
                exit(-1);
            }
        }
    }
    printf("Success!\n");
}

int main() {
    int n, Q;
    std::cin >> n >> Q;
    test(n, Q);
}