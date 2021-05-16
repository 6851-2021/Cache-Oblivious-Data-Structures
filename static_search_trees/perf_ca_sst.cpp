#include <iostream>
#include <stdlib.h>
#include "static_search_trees.h"
#include "perf_params.h"
// #include <time.h>
#include <chrono>

using namespace std;

void test(int n, int Q) {
    CA_static_search_tree tree(n);

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
}

int main(){
    srand(10);
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    for (int run = 0; run < num_runs; ++run)
    {
        cout << "Run " << run << ": ";
        int n, Q;
        cin >> n >> Q;
        test(n, Q);
    }
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Time difference = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
}