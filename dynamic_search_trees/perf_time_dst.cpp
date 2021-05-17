//===----------------------------------------------------------------------===//
//
// Test the performance of our dynamic search trees against C++ standard template
// implementation of std::set, which is a red-black tree.
// 
// We mainly test the
// methods add() and get_successor() against std::insert() and std::lower_bound().
// We apply the same sequence of operations on each search tree and compare the
// runtimes and cache misses.
//
//===----------------------------------------------------------------------===//

#include "co_dynamic_search_tree.h"

#include <stdlib.h>
#include <chrono>
#include <set>
#include <algorithm>
#include <limits.h>

#define RAND_SEED_FREQ 10000
#define RAND_NUM_LIMIT 1000000

using namespace std;

// We will assign the result of calling lower_bound() for std::set or get_successor()
// for dynamic_search_tree to this variable to make sure the compiler does not optimize
// out the call to that method as we don't use that variable to check for correctness.
static int temp_successor_value __attribute__((used)) = 0;

// Insert n elements into the passed-in dynamic search tree.
void insert_n_dyn_search_tree(int n, co_dynamic_serach_tree &tree) {
	for (int i = 0; i < n; i++) {
		if (i % RAND_SEED_FREQ == 0) {
			srand(i / RAND_SEED_FREQ);
		}
		int elem = rand() % RAND_NUM_LIMIT;
		tree.add(elem);
	}
}

// Insert n elements into the passed-in std::set.
void insert_n_std_set(int n, set<int> &tree) {
	for (int i = 0; i < n; i++) {
		if (i % RAND_SEED_FREQ == 0) {
			srand(i / RAND_SEED_FREQ);
		}
		int elem = rand() % RAND_NUM_LIMIT;
		tree.insert(elem);
	}
}

// Make Q get_successor queries into passed-in dynamic search tree.
void get_successor_Q_dyn_search_tree(int Q, co_dynamic_serach_tree &tree) {
	for (int i = 0; i < Q; i++) {
		if (i % RAND_SEED_FREQ == 0) {
			srand(INT_MAX + (i / RAND_SEED_FREQ));
		}
		int elem = rand() % RAND_NUM_LIMIT;
		temp_successor_value = tree.get_successor(elem);
	}
}

// Make Q get_successor queries into passed-in std::set.
void get_successor_Q_std_set(int Q, set<int> &tree) {
	for (int i = 0; i < Q; i++) {
		if (i % RAND_SEED_FREQ == 0) {
			srand(INT_MAX + (i / RAND_SEED_FREQ));
		}
		int elem = rand() % RAND_NUM_LIMIT;
		temp_successor_value = *tree.lower_bound(elem);
	}
}

// Insert n random elements into each search tree and then compare runtimes.
void test_add_n_rand(int n) {
	co_dynamic_serach_tree dyn_tree;
	set<int> std_set;

	chrono::steady_clock::time_point begin;
	chrono::steady_clock::time_point end;

	cout << "Testing " << n << " random insert/add operations:\n\n";

	// dynamic search tree.
	cout << "Testing runtime of dynamic cache-oblivious B-trees on " << n << " add operations." << endl;
	begin = chrono::steady_clock::now();
	insert_n_dyn_search_tree(n, dyn_tree);
	end = chrono::steady_clock::now();
	cout << "Runtime = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << "\n\n";

	// std::set.
	cout << "Testing runtime of std::set on " << n << " insert operations." << endl;
	begin = chrono::steady_clock::now();
	insert_n_std_set(n, std_set);
	end = chrono::steady_clock::now();
	cout << "Runtime = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << "\n\n";

	cout << "Done." << endl;
}

// Insert n random elements into each search tree and then do Q successor queries
// on random elements that might exist or not exist in each tree. The runtime here
// for each tree reflects the runtime of Q successor queries on that tree.
void test_add_n_rand_then_query_Q_rand(int n, int Q) {
	co_dynamic_serach_tree dyn_tree;
	set<int> std_set;

	chrono::steady_clock::time_point begin;
	chrono::steady_clock::time_point end;

	cout << "Testing " << n << " random get_successor operations:\n\n";

	// dynamic search tree.
	insert_n_dyn_search_tree(n, dyn_tree);
	cout << "Testing runtime of dynamic cache-oblivious B-trees on " << Q << " get_successor() operations." << endl;
	begin = chrono::steady_clock::now();
	get_successor_Q_dyn_search_tree(Q, dyn_tree);
	end = chrono::steady_clock::now();
	cout << "Runtime = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << "\n\n";

	// std::set.
	insert_n_std_set(n, std_set);
	cout << "Testing runtime of std::set on " << Q << " get_successor() operations." << endl;
	begin = chrono::steady_clock::now();
	get_successor_Q_std_set(Q, std_set);
	end = chrono::steady_clock::now();
	cout << "Runtime = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << "\n\n";

	cout << "Done." << endl;
}

// Test randomly insering or deleting random-valued elements into CO-DST or std::set,
// for a total of Q operations. Measure the runtime of each data structure accordingly.
void test_rand_add_and_query(int Q) {
	co_dynamic_serach_tree dyn_tree;
	set<int> std_set;

	chrono::steady_clock::time_point begin;
	chrono::steady_clock::time_point end;

	cout << "Testing " << Q << " randomized insert and lower_bound/get_successor operations:\n\n";

	// dynamic search tree
	srand(0);
	cout << "Testing runtime of dynamic cache-oblivious B-trees on " << Q << " random operations." << endl;
	begin = chrono::steady_clock::now();
	for (int i = 0; i < 5; i++) {
		// insert a few random elements first.
		dyn_tree.add(rand() % RAND_NUM_LIMIT);
	}
	for (int i = 0; i < Q; i++) {
		if ((i + 5) % RAND_SEED_FREQ == 0) {
			srand(INT_MAX + (i / RAND_SEED_FREQ));
		}
		int query_type = rand() & 1;
		int elem = rand() % RAND_NUM_LIMIT;
		if (query_type == 0) {
			// insert
			dyn_tree.add(elem);
		} else {
			temp_successor_value = dyn_tree.get_successor(elem);
		}
	}
	end = chrono::steady_clock::now();
	cout << "Runtime = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << "\n\n";

	// std::set
	srand(0);
	cout << "Testing runtime of std::set on " << Q << " randomized operations." << endl;
	begin = chrono::steady_clock::now();
	for (int i = 0; i < 5; i++) {
		// insert a few random elements first.
		std_set.insert(rand() % RAND_NUM_LIMIT);
	}
	for (int i = 0; i < Q; i++) {
		if ((i + 5) % RAND_SEED_FREQ == 0) {
			srand(INT_MAX + (i / RAND_SEED_FREQ));
		}
		int query_type = rand() & 1;
		int elem = rand() % RAND_NUM_LIMIT;
		if (query_type == 0) {
			// insert
			std_set.insert(elem);
		} else {
			temp_successor_value = *std_set.lower_bound(elem);
		}
	}
	end = chrono::steady_clock::now();
	cout << "Runtime = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << "\n\n";

	cout << "Done." << endl;
}	

// Make the calls to all the performance tests here.
void run(int n, int Q) {
	cout << "Running performance tests on dynamic search trees\n";
	test_add_n_rand(n);
	test_add_n_rand_then_query_Q_rand(n, Q);
	test_rand_add_and_query(Q);
}

int main(){
    run((1 << 20), (1 << 24));
}
