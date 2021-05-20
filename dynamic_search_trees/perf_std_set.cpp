#include <set>
#include <random>
#include <iostream>

const int rand_reset_const = 10000;

void test(int max_value, int Q) {
    std::set<int> tree;
    for (int i = 0; i <= max_value; i++){
        tree.insert(i * 7);
    }
    while (Q--)
    {
        int query_type = rand() % 12;

        if (Q % rand_reset_const == 0) {
            srand(Q / rand_reset_const);
        }

        if (query_type < 4)
        {
            int value = rand() % max_value;
            tree.insert(value * 7);
        } else {
            int value = rand() % (max_value * 7);
            int result = *tree.lower_bound(value);
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
    srand(1);
    int n, Q;
    std::cin >> n >> Q;
    test(n, Q);
}