#include "co_dynamic_search_tree.h"
#include<set>
#include<random>
#include <iostream>

void small_test() {
    co_dynamic_serach_tree tree;
    tree.add(4);
    
    if(tree.get_successor(4) != 4) {
        std::cout << "Incorrect Successor\n";
        exit(-1);
    }

    if(tree.get_successor(3) != 4) {
        std::cout << "Incorrect Successor\n";
        exit(-1);
    }

    if(tree.get_successor(2) != 4) {
        std::cout << "Incorrect Successor\n";
        exit(-1);
    }

    tree.add(25);

    if(tree.get_successor(4) != 4) {
        std::cout << "Incorrect Successor\n";
        exit(-1);
    }
    
    if(tree.get_successor(3) != 4) {
        std::cout << "Incorrect Successor\n";
        exit(-1);
    }

    if(tree.get_successor(2) != 4) {
        std::cout << "Incorrect Successor\n";
        exit(-1);
    }

    if(tree.get_successor(10) != 25) {
        std::cout << "Incorrect Successor\n";
        exit(-1);
    }
    
    if(tree.get_successor(15) != 25) {
        std::cout << "Incorrect Successor\n";
        exit(-1);
    }

    if(tree.get_successor(20) != 25) {
        std::cout << "Incorrect Successor\n";
        exit(-1);
    }

    tree.add(18);

    if(tree.get_successor(3) != 4) {
        std::cout << "Incorrect Successor\n";
        exit(-1);
    }

    if(tree.get_successor(2) != 4) {
        std::cout << "Incorrect Successor\n";
        exit(-1);
    }

    if(tree.get_successor(10) != 18) {
        std::cout << "Incorrect Successor\n";
        exit(-1);
    }
    
    if(tree.get_successor(15) != 18) {
        std::cout << "Incorrect Successor\n";
        exit(-1);
    }

    if(tree.get_successor(20) != 25) {
        std::cout << "Incorrect Successor\n";
        exit(-1);
    }
    
    if(tree.get_successor(18) != 18) {
        std::cout << "Incorrect Successor\n";
        exit(-1);
    }

    if(tree.get_successor(100) != -1) {
        std::cout << "Incorrect Successor\n";
        exit(-1);
    }

    cout << "Small Test Success!\n";
}

void big_test(int Q, int max_value) {
    cout << "Num Queries: " << Q << "\n";
    co_dynamic_serach_tree tree;
    set<int> s;

    s.insert(max_value);
    tree.add(max_value);

    int reCheck = Q / 10;

    while(Q--) {
        int value = rand() % max_value;
        tree.add(value);
        s.insert(value);   

        if (tree.get_successor(value) != *s.lower_bound(value))
        {
            cout << "Incorrect Successor, value already exists\n";
            cout << "Expected: " << *s.lower_bound(value) << ", Got: " << tree.get_successor(value) << "\n";
            throw -1;
        }

        if(tree.get_successor(value - 1) != *s.lower_bound(value - 1)) {
            cout << "Incorrect Successor, prev value\n";
            cout << "Expected: " << *s.lower_bound(value - 1) << ", Got: " << tree.get_successor(value - 1) << "\n";
            throw -1;
        }

        int offset = rand() % value;
        if (tree.get_successor(value - offset) != *s.lower_bound(value - offset))
        {
            cout << "Incorrect Successor\n";
            cout << "Expected: " << *s.lower_bound(value - offset) << ", Got: " << tree.get_successor(value - offset) << "\n";
            throw -1;
        }

        if (Q % reCheck == 0)
        {
            for (auto it : s)
            {
                if (tree.get_successor(it) != it)
                {

                    cout << "Incorrect Successor, loop check\n";
                    cout << "Expected: " << it << ", Got: " << tree.get_successor(it) << "\n";
                    throw -1;
                }
            }

            srand(Q);
            for (int i = 0; i < s.size(); ++i) {
                int value = rand() % max_value;
                if(tree.get_successor(value) != *s.lower_bound(value)) {
                    cout << "Random Check failed\n";
                    cout << "Expected: " << *s.lower_bound(value) << ", Got: " << tree.get_successor(value) << "\n";
                    exit(-1);
                }
            }
        }
    }
    cout << "Success!" << endl;
}

int main() {
    srand(10);
    small_test();
    big_test(16, 100);
    big_test(100, 10000);
    big_test(1000, 1e9);
    big_test(100000, 2e9); 
    big_test(1000000, 2e9);
}