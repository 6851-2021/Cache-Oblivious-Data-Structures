#include<iostream>
#include<math.h>
using namespace std;

const int NOT_FOUND_INDEX = -1;

class CO_static_search_tree {
    private:
        int *tree;
        int n;
        int length;
        int size;
        int height;

        long long nodes_touched_overall;
        int nodes_touched_during_query;

        int merge(int vlaue1, int value2);
        int update(int tree_l, int h, int arr_l, int arr_r, int index, int value);
        int get(int tree_l, int h, int arr_l, int arr_r, int value);
    public:
        ~CO_static_search_tree();
        /*
    Init a cache obilvious static search tree with size equal to
    the next power of 2 greater than n
    */
        CO_static_search_tree(int n);
        /*
    Update the value at the given index
    */
        void update(int index, int value);

        /*
    Return the index of the successor of the value in the array.
    If successor does not exists return NOT_FOUND_INDEX
    */
        int get(int value);

    /*
    Returns the number of access to the tree array since creating the object
    */
        long long get_num_of_touched_nodes();
};

class static_search_tree {
    private:
        int *tree;
        int n;
        int length;
        int size;
        int height;

        long long nodes_touched_overall;
        int nodes_touched_during_query;

        int merge(int vlaue1, int value2);
        void update(int tree_l, int arr_l, int arr_r, int index, int value);
        int get(int tree_l, int arr_l, int arr_r, int value);
    public:
    ~static_search_tree();
    /*
    Init a cache obilvious static search tree with size equal to
    the next power of 2 greater than n
    */
    static_search_tree(int n);
    /*
    Update the value at the given index
    */
    void update(int index, int value);

    /*
    Return the index of the successor of the value in the array.
    If successor does not exists return NOT_FOUND_INDEX
    */
    int get(int value);

    /*
    Returns the number of access to the tree array since creating the object
    */
    long long get_num_of_touched_nodes();
};