#include<iostream>
#include<math.h>
#include<vector>
using namespace std;

const int NOT_FOUND_INDEX = -1;

class CO_static_search_tree {
    private:
        int *tree;
        int n;
        int length;
        int size;
        int height;
        int block_index_memo[40];

        int merge(int vlaue1, int value2);
        int update(int tree_l, int h, int arr_l,  int og_height, int index, int value);
        int get(int tree_l, int h, int arr_l,  int og_height, int value);

        int update_3_base_case(int tree_l, int h, int arr_l, int og_height, int index, int value);
        int get_3_base_case(int tree_l, int h, int arr_l, int og_height, int value);

        int update_4_base_case(int tree_l, int h, int arr_l, int og_height, int index, int value);
        int get_4_base_case(int tree_l, int h, int arr_l, int og_height, int value);

        int get_tree_height_pwr_2(int block_index, int h, int arr_l, int og_height, int value);
        int update_tree_height_pwr_2(int block_index, int h, int arr_l, int og_height, int index, int value);
        int left_child(int block_index, int depth, int path);
        int right_child(int block_index, int depth, int path);

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

        void range_update(int l, int r, int *items);
};
typedef struct Triplet {
    int parent;
    int left;
    int right;
} triplet;

class built_co_static_search_tree {
    private:
        typedef struct {
            int value;
            int left;
            int right;
        } node;

        int *tree;
        int *temp_tree;
        int n;
        int length;
        int size;
        int height;

        void van_emde_boas_build(int tree_l, int h, int og_height, int bfs_order);
        void build(int index, int h);
        void update(int current_node, int h, int index, int value);

    public:
        ~built_co_static_search_tree();
        /*
    Init a cache obilvious static search tree with size equal to
    the next power of 2 greater than n
    */
        built_co_static_search_tree(int n);
        /*
    Update the value at the given index
    */
        void update(int index, int value);

        /*
    Return the index of the successor of the value in the array.
    If successor does not exists return NOT_FOUND_INDEX
    */
        int get(int value);
};

// Cache-aware (hopefully optimal) static search tree. This is essentially
// a static search tree of subtrees, each of height 3 (4 levels or 15 nodes
// total). Each subtree is stored in an adjacent array slice, so we can index
// it however we want.
class CA_static_search_tree {
    private:
        int *tree;
        int n;
        int length;
        int size;
        int height;
        std::vector<Triplet> parents;

        int merge(int value1, int value2);
        void update(int tree_l, int num_inner_nodes, int temp_root, int h, int arr_l, int arr_r, int index, int value);
        int get(int tree_l, int num_inner_nodes, int temp_root, int h, int arr_l, int arr_r, int value);
        int calc_real_subtree_root(int root_idx);
    public:
    ~CA_static_search_tree();
    /*
    Init a cache aware static search tree with size equal to
    the next power of 2 greater than n.
    */
    CA_static_search_tree(int n);

    /*
    Print the tree defined array values.
    */
    void print_tree();

    /*
    Update the value at the given index.
    */
    void update(int index, int value);

    /*
    Return the index of the successor of the value in the array.
    If successor does not exists return NOT_FOUND_INDEX
    */
    int get(int value);
};

class static_search_tree {
    private:
        int *tree;
        int n;
        int length;
        int size;
        int height;
        bool recursive;

        int merge(int vlaue1, int value2);

        void update_recursive(int tree_l, int arr_l, int arr_r, int index, int value);
        void update_iterative(int tree_l, int arr_l, int arr_r, int index, int value);

        int get_recursive(int tree_l, int arr_l, int arr_r, int value);
        int get_iterative(int tree_l, int arr_l, int arr_r, int value);

    public:
        ~static_search_tree();
        /*
    Init a cache obilvious static search tree with size equal to
    the next power of 2 greater than n
    */
        static_search_tree(int n, bool recursive);

        /*
    Print the tree defined array values.
    */
        void print_tree();

        /*
    Update the value at the given index
    */
        void update(int index, int value);

        /*
    Return the index of the successor of the value in the array.
    If successor does not exists return NOT_FOUND_INDEX
    */
        int get(int value);
};
