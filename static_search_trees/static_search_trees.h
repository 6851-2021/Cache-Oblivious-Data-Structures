#include<iostream>
#include<math.h>
#include<vector>
#include<map>
using namespace std;

const int NOT_FOUND_INDEX = -1;
const int MINUS_INFINITY = -1;

/**
 * @brief A cache oblivious static search tree.
 * 
 * A cache oblivous static search tree built over an array of length that is 
 * a power of two. Each node stores the maximum of the subtree.
 * 
 */
class co_static_search_tree {
    private:
        int *tree;
        int *array;
        int n;
        int length;
        int size;
        int height;
        int block_index_memo[40];
        
        /**
         * @brief Recursively update a block in the tree by updating the value at
         *        the given index.
         * 
         * @param block_index  the index of the block in the array
         * @param height  the height of the block
         * @param range_left  the left index of the range the node represents in the array
         * @param og_height  the original height the of the block in the full tree
         * @param index  the index in the array to update
         * @param value  the value to update at this index
         * @return int  the new the value of the block root
         */
        int update(int block_index, int height, int range_left, int og_height, int index, int value);
        
        /**
         * @brief Get the index in the array of the successor of the value in the block.
         * 
         * @param block_index  the index of the block in memory
         * @param height  the height of the block
         * @param range_left  the left index of the range the node represents in the array
         * @param og_height  the original height the of the block in the full tree
         * @param value  the value to find the succssor of
         * @return int  the index in the array with the successor of the value
         */
        int get(int block_index, int height, int range_left, int og_height, int value);

        /**
         * @brief Update a block of height 3 in the tree at by change the given index.
         * 
         * @param block_index  the index of the block in memory
         * @param range_left  the left index of the range the node represents in the array
         * @param og_height  the original height the of the block in the full tree
         * @param index  the index in the array to update
         * @param value  the value to update at this index
         * @return int  the new the value of the block root
         */
        int update_3_base_case(int block_index, int range_left, int og_height, int index, int value);
        
        /**
         * @brief Get the index in the array of the successor of the value in a block of height 3.
         * 
         * @param block_index  the index of the block in memory
         * @param range_left  the left index of the range the node represents in the array
         * @param og_height  the original height the of the block in the full tree
         * @param value  the value to find the succssor of
         * @return int  the index in the array with the successor of the value
         */
        int get_3_base_case(int block_index, int range_left, int og_height, int value);

        /**
         * @brief Update a block of height 4 in the tree at by change the given index.
         * 
         * @param block_index  the index of the block in memory
         * @param range_left  the left index of the range the node represents in the array
         * @param og_height  the original height the of the block in the full tree
         * @param index  the index in the array to update
         * @param value  the value to update at this index
         * @return int  the new the value of the block root
         */
        int update_4_base_case(int block_index, int range_left, int og_height, int index, int value);
        
        /**
         * @brief Get the index in the array of the successor of the value in a block of height 4.
         * 
         * @param block_index  the index of the block in memory
         * @param range_left  the left index of the range the node represents in the array
         * @param og_height  the original height the of the block in the full tree
         * @param value  the value to find the succssor of
         * @return int  the index in the array with the successor of the value
         */
        int get_4_base_case(int block_index, int range_left, int og_height, int value);

        /**
         * @brief Get the index in the array of the successor of the value in the block
         *        where the height of the block is a power of 2.
         * 
         * @param block_index  the index of the block in memory
         * @param height  the height of the block (power of 2)
         * @param range_left  the left index of the range the node represents in the array
         * @param og_height  the original height the of the block in the full tree
         * @param value  the value to find the succssor of
         * @return int  the index in the array with the successor of the value
         */
        int get_tree_height_pwr_2(int block_index, int height, int range_left, int og_height, int value);
        
        /**
         * @brief Recursively update a block in the tree by updating the value at
         *        the given index, where the height of the block is a power of 2.
         * 
         * @param block_index  the index of the block in memory
         * @param height  the height of the block (power of 2)
         * @param range_left  the left index of the range the node represents in the array
         * @param og_height  the original height the of the block in the full tree
         * @param index  the index in the array to update
         * @param value  the value to update at this index
         * @return int  the new the value of the block root
         */
        int update_tree_height_pwr_2(int block_index, int height, int range_left, int og_height, int index, int value);

        /**
         * @brief Get the block index in memory of the left child of the block's root,
         *        where the height of the full tree is a power of 2.
         * 
         * @param block_index  the index of the block in memory
         * @param depth  the depth of the block with resepct to the tree root
         * @param path  encoding of the path taken to get to this node (add 0 to the beginning if you took a left,
         *               add 1 to the beginning if you took a right) 
         * @return int  the index in memory of the left child of the block's root.
         */
        int left_child(int block_index, int depth, int path);
        
        /**
         * @brief Get the block index in memory of the right child of the block's root,
         *        where the height of the full tree is a power of 2.
         * 
         * @param block_index  the index of the block in memory
         * @param depth  the depth of the block with resepct to the tree root
         * @param path  encoding of the path taken to get to this node (add 0 to the beginning if you took a left,
         *               add 1 to the beginning if you took a right) 
         * @return int  the index in memory of the right child of the block's root.
         */
        int right_child(int block_index, int depth, int path);

        /**
         * @brief Update the given query range inside the block according to the values in items.
         * 
         * @param block_index  the index of the block in memory
         * @param height   the height of the block
         * @param range_left  the left index of the range the node represents in the array
         * @param og_height  the original height the of the block in the full tree
         * @param query_range_left  the left index of the query range
         * @param query_range_right  the right index of the query range
         * @param items  the array from which to get the values to update the range (this array is mutated)
         */
        void range_update(int block_index, int height, int range_left,  int og_height, int query_range_left, int query_range_right, int* items);

    public:
        ~co_static_search_tree();

        /**
         * @brief Construct a new co static search tree object
         *        on a top of an array of length n (n is rounded up to the next power of 2)
         *        
         *        The tree is initialized to MINUS_INFINITY
         * 
         * @param n  the length of the array
         */
        co_static_search_tree(int n);
        
        /**
         * @brief Update the value at the given index
         * 
         * @param index  the index to update
         * @param value  the value to set at this index
         */
        void update(int index, int value);

        /**
        * @brief  return the index in the array of the successor of value
        * 
        * @param value  the value to find the successor of
        * @return int  the index of the successor or NOT_FOUND_INDEX if the successor does not exists
        */
        int get(int value);

        /**
         * @brief  Update the a range of values in the array.
         * 
         * @param query_range_left  the left side of the range (inclusive)
         * @param query_range_right  the right side of the range (inclusive)
         * @param items 
         */
        void range_update(int query_range_left, int query_range_right, int *items);
};

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

// Auxiliary struct for stack of nodes along an update path.
typedef struct Triplet {
    int parent;
    int left;
    int right;
} triplet;


// Cache-aware (hopefully optimal) static search tree. This is essentially
// a static search tree of subtrees, each of height 3 (4 levels or 15 nodes
// total). Each subtree is stored in an adjacent array slice, so we can index
// it however we want. The subtrees are ordered within the CA_sst in a normal BST
// order.
class CA_static_search_tree {
    private:
        int *tree;
        int n;
        int length;
        int size;
        int height;
        // auxiliary array serving as a stack to keep track of parent indices for calls to
        // update so that we can update the whole path down to the target leaf.
        std::vector<Triplet> parents;

        /**
        * @brief Merge two children node values into the parent. The merge function itself is
        *        a max function.
        *
        * @param value1: left child value.
        * @param value2: right child value.
        *
        * @return max of the two values.
        */
        int merge(int value1, int value2);
        /**
        * @brief Update the value at index index, which corresponds to the index of some value in the
        *        tree if it were a sorted array.
        *
        * @param tree_1: current real index in the CA tree.
        * @param num_inner_nodes: number of inner nodes (base case subtrees) we went over so far, with
        *                         the exception of preceding inner nodes within our current level in the
        *                         tree.
        * @param temp_root: current root within the current subunit/subtree (tree of size 15). Values range
        *                   from 1 to 15.
        * @param h: current height of the actual node we're at within the CA_tree (not subtree root node).
        * @param arr_l: left end of the sorted-order range containg value.
        * @param arr_3: right end of the sorted-order range containg value.
        * @param index: index of the node to update. Index corresponds to where the node would be in a sorted
        *               array (in-order traversal array).
        * @param value: new value to place at index.
        */
        void update(int tree_l, int num_inner_nodes, int temp_root, int h, int arr_l, int arr_r, int index, int value);
        /**
        * @brief return in-order traversal index of value in the tree.
        *
        * @param tree_1: current real index in the CA tree.
        * @param num_inner_nodes: number of inner nodes (base case subtrees) we went over so far, with
        *                         the exception of preceding inner nodes within our current level in the
        *                         tree.
        * @param temp_root: current root within the current subunit/subtree (tree of size 15). Values range
        *                   from 1 to 15.
        * @param h: current height of the actual node we're at within the CA_tree (not subtree root node).
        * @param arr_l: left end of the sorted-order range containg value.
        * @param arr_3: right end of the sorted-order range containg value.
        * @param value: new value to place at index.
        *
        * @return: in-order traversal (sorted array) index of value.
        */
        int get(int tree_l, int num_inner_nodes, int temp_root, int h, int arr_l, int arr_r, int value);
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

class simple_static_search_tree {
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
        ~simple_static_search_tree();
        /*
    Init a cache obilvious static search tree with size equal to
    the next power of 2 greater than n
    */
        simple_static_search_tree(int n, bool recursive);

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

class map_rep_static_search_tree {
    private:
        map<int, int> m;

    public:
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

