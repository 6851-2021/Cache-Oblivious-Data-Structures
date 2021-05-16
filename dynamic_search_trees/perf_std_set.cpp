#include <set>
#include <random>

void test(int max_value) {
    int Q = max_value * 2;
    std::set<int> tree;
    for (int i = 0; i <= max_value; i++){
        tree.insert(i * 7);
    }
    while (Q--)
    {
        int query_type = rand() % 12;
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
    test(1e6);
}