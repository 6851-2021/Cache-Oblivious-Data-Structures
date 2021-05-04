#include "dynamic_search_tree.h"

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

    cout << "Small Test Success!\n";
}

int main() {
    small_test();
}