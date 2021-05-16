#include <iostream>
#include <stdlib.h>
#include "static_search_trees.h"
#include "perf_params.h"
// #include <time.h>
#include <chrono>

using namespace std;

void test(int n, int Q, bool recursive) {
    simple_static_search_tree tree(n, recursive);

    for (int i = 0; i < n; ++i) {
        tree.update(i, i);
    }

    for (int query = 0; query < Q; ++query)
    {   
        if (query % rand_reset_const == 0) {
            srand(query / rand_reset_const);
        }
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
}

void run(bool recursive) {
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    
    if(recursive) {
        cout << "Recursive Implementation:\n";
    } else{
        cout << "Iterative Implementation:\n";
    }
    for (int run = 0; run < num_runs; ++run)
    {
        cout << "Run " << run << ": ";
        int n, Q;
        cin >> n >> Q;
        test(n, Q, recursive);
    }
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Time difference = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
}

int main(){
    srand(10);
    run(sst_recursive_falg);
}