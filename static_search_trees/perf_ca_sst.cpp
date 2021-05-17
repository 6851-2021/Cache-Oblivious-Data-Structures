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

int main(){
    // I think it's better to first let the user specify the inputs,
    // then make 10 independent runs on the same inputs n and Q, and
    // measure the runtime of each separately. We need an average of
    // runtimes, not the total runtime - maybe I'm wrong about this?
    cout << "Enter values for n and Q: ";
    int n, Q;
    cin >> n >> Q;
    double total = 0.0;
    for (int run = 1; run <= num_runs; ++run)
    {
        srand(0);
        chrono::steady_clock::time_point begin = chrono::steady_clock::now();
        cout << "Run number: " << run << endl;
        test(n, Q);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        cout << "Time difference = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
        total += chrono::duration_cast<chrono::microseconds>(end - begin).count();
    }
    cout << "Done." << endl;
    cout << "Average runtime on " << num_runs << " is: " << total / num_runs << endl;
}