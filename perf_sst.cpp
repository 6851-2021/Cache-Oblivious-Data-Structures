#include <iostream>
#include <stdlib.h>
#include "static-search-trees.h"
#include "perf_params.h"
#include <time.h>

using namespace std;

void test(int n, int Q) {
    static_search_tree tree(n);

    for (int i = 0; i < n; ++i) {
        tree.update(i, i);
    }

    for (int query = 0; query < Q; ++query)
    {
        int type = rand() % 2;
        int index = rand() % n;
        if(type == 0) {
            tree.update(index, index);
        } else {
            if(tree.get(index) != index) {
                cout << "Fail: expected value " << index << " at index " << index << endl;
                return;
            }
        }
    }
    cout << "test(" << n << ", " << Q << "): OK" << endl;
    cout << "Nodes Touched: " << tree.get_num_of_touched_nodes() << endl;
    cout << "Recursive Calls: " << tree.get_num_of_recursive_calls() << endl;
}

int main(){
    srand(time(NULL));
    for (int run = 0; run < num_runs; ++run)
    {
        cout << "Run " << run << ": ";
        test(n, Q);
    }
}