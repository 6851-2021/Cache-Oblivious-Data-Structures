#include "static_search_trees.h"

#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;

inline int next_power_of_2(unsigned int n) {
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n; 
}

//memo of the next power of 2 for each possible height
const int bottom_tree_height_memo[] = {0,1,1,2,2,4,4,4,4,8,8,8,8,8,8,8,8,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32};

co_static_search_tree::co_static_search_tree(int n) {
    this->n = n;
    this->length = next_power_of_2(n);
    this->size = this->length * 2;
    this->height = log2(this->length) + 1;
    this->tree = (int *)malloc(sizeof(int) * this->size);
    for (int i = 0; i < this->size; ++i) {
        this->tree[i] = MINUS_INFINITY;
    }
    this->array = (int *)malloc(sizeof(int) * this->n);
}

co_static_search_tree::~co_static_search_tree() {
    free(this->tree);
    free(this->array);
}

inline int co_static_search_tree::update_3_base_case(int block_index, int range_left, int og_height, int index, int value) {
    /*
                            0
                    1               4
                2       3       5       6
    */
    int leafs_og_height = og_height - 2;
    int leaf_index = (index - range_left) >> (leafs_og_height - 1);
    if(leaf_index == 0) {
        this->tree[block_index + 2] = value;
        this->tree[block_index + 1] = max(this->tree[block_index + 2], this->tree[block_index + 3]);
        this->tree[block_index + 0] = max(this->tree[block_index + 1], this->tree[block_index + 4]);
    }
    else if(leaf_index == 1) {
        this->tree[block_index + 3] = value;
        this->tree[block_index + 1] = max(this->tree[block_index + 2], this->tree[block_index + 3]);
        this->tree[block_index + 0] = max(this->tree[block_index + 1], this->tree[block_index + 4]);
    }
    else if(leaf_index == 2) {
        this->tree[block_index + 5] = value;
        this->tree[block_index + 4] = max(this->tree[block_index + 5], this->tree[block_index + 6]);
        this->tree[block_index + 0] = max(this->tree[block_index + 1], this->tree[block_index + 4]);
    }
    else if(leaf_index == 3) {
        this->tree[block_index + 6] = value;
        this->tree[block_index + 4] = max(this->tree[block_index + 5], this->tree[block_index + 6]);
        this->tree[block_index + 0] = max(this->tree[block_index + 1], this->tree[block_index + 4]);
    }
    return this->tree[block_index];
}

inline int co_static_search_tree::update_4_base_case(int block_index, int range_left, int og_height, int index, int value) {
    /*
                                    0
                    1                                   2
            3               6                   9                 12
        4       5       7       8           10       11      13          14                    
    */
    int leafs_og_height = og_height - 3;
    int leaf_index = (index - range_left) >> (leafs_og_height - 1);
    if(leaf_index == 0) {
        this->tree[block_index + 4] = value;
        this->tree[block_index + 3] = max(this->tree[block_index + 4], this->tree[block_index + 5]);
        this->tree[block_index + 1] = max(this->tree[block_index + 3], this->tree[block_index + 6]);
        this->tree[block_index + 0] = max(this->tree[block_index + 1], this->tree[block_index + 2]);
    }
    else if(leaf_index == 1) {
        this->tree[block_index + 5] = value;
        this->tree[block_index + 3] = max(this->tree[block_index + 4], this->tree[block_index + 5]);
        this->tree[block_index + 1] = max(this->tree[block_index + 3], this->tree[block_index + 6]);
        this->tree[block_index + 0] = max(this->tree[block_index + 1], this->tree[block_index + 2]);
    }
    else if(leaf_index == 2) {
        this->tree[block_index + 7] = value;
        this->tree[block_index + 6] = max(this->tree[block_index + 7], this->tree[block_index + 8]);
        this->tree[block_index + 1] = max(this->tree[block_index + 3], this->tree[block_index + 6]);
        this->tree[block_index + 0] = max(this->tree[block_index + 1], this->tree[block_index + 2]);
    }
    else if(leaf_index == 3) {
        this->tree[block_index + 8] = value;
        this->tree[block_index + 6] = max(this->tree[block_index + 7], this->tree[block_index + 8]);
        this->tree[block_index + 1] = max(this->tree[block_index + 3], this->tree[block_index + 6]);
        this->tree[block_index + 0] = max(this->tree[block_index + 1], this->tree[block_index + 2]);
    }
    else if(leaf_index == 4) {
        this->tree[block_index + 10] = value;
        this->tree[block_index + 9] = max(this->tree[block_index + 10], this->tree[block_index + 11]);
        this->tree[block_index + 2] = max(this->tree[block_index + 9], this->tree[block_index + 12]);
        this->tree[block_index + 0] = max(this->tree[block_index + 1], this->tree[block_index + 2]);
    }
    else if(leaf_index == 5){
        this->tree[block_index + 11] = value;
        this->tree[block_index + 9] = max(this->tree[block_index + 10], this->tree[block_index + 11]);
        this->tree[block_index + 2] = max(this->tree[block_index + 9], this->tree[block_index + 12]);
        this->tree[block_index + 0] = max(this->tree[block_index + 1], this->tree[block_index + 2]);
    }
    else if(leaf_index == 6){
        this->tree[block_index + 13] = value;
        this->tree[block_index + 12] = max(this->tree[block_index + 13], this->tree[block_index + 14]);
        this->tree[block_index + 2] = max(this->tree[block_index + 9], this->tree[block_index + 12]);
        this->tree[block_index + 0] = max(this->tree[block_index + 1], this->tree[block_index + 2]);
    }
    else if(leaf_index == 7){
        this->tree[block_index + 14] = value;
        this->tree[block_index + 12] = max(this->tree[block_index + 13], this->tree[block_index + 14]);
        this->tree[block_index + 2] = max(this->tree[block_index + 9], this->tree[block_index + 12]);
        this->tree[block_index + 0] = max(this->tree[block_index + 1], this->tree[block_index + 2]);
    }
    return this->tree[block_index];
}

int co_static_search_tree::update(int block_index, int height, int range_left, int og_height, int index, int value) {
    if (height == 1)
    {
        this->tree[block_index] = value;
        return value;
    }
    if(height == 2) {
        if(index < range_left + (1 << (og_height - 2))) {
            this->tree[block_index + 1] = value;
        } else {
            this->tree[block_index + 2] = value;
        }
        //merge
        this->tree[block_index] = max(this->tree[block_index + 1], this->tree[block_index + 2]);
        return this->tree[block_index];
    }
    if(height == 3) {
        return this->update_3_base_case(block_index, range_left, og_height, index, value);
    }   
    if(height == 4) {
        return this->update_4_base_case(block_index, range_left, og_height, index, value);
    }
    
    //update bottom tree
    int bottom_tree_height = bottom_tree_height_memo[height];

    int top_tree_height = height - bottom_tree_height;
    
    int top_tree_size = (1 << top_tree_height) - 1;

    int bottom_tree_og_height = og_height - top_tree_height;
    int bottom_tree_index = (index - range_left) >> (bottom_tree_og_height - 1);
    int bottom_tree_size = (1 << bottom_tree_height) - 1;

    int bottom_tree_block_index = block_index + top_tree_size + (bottom_tree_index << bottom_tree_height) - bottom_tree_index;
    int bottom_tree_range_left = range_left + (bottom_tree_index << (bottom_tree_og_height - 1));

    int child_value = this->update(bottom_tree_block_index, bottom_tree_height, bottom_tree_range_left, bottom_tree_og_height, index, value);


    //get adjacent child
    int adjacent_child_value;
    if(bottom_tree_index % 2 == 0) {
        adjacent_child_value = this->tree[bottom_tree_block_index + bottom_tree_size];
    } else {
        adjacent_child_value = this->tree[bottom_tree_block_index - bottom_tree_size];
    }

    //merge two children value
    int merged_value = max(child_value, adjacent_child_value);

    //update upper tree
    int final_value = this->update(block_index, top_tree_height, range_left, og_height, index, merged_value);

    return final_value;
}

void co_static_search_tree::update(int index, int value) {
    this->update(0, this->height, 0, this->height, index, value);
}

inline int co_static_search_tree::get_3_base_case(int block_index, int range_left, int og_height, int value) {
    /*
                            0
                    1               4
                2       3       5       6
    */

    int leafs_og_height = og_height - 2;
    int leafs_range_length = (1 << (leafs_og_height - 1));
    if(value <= this->tree[block_index + 1]){
        if (value <= this->tree[block_index + 2])
            return range_left;
        else    
            return range_left + leafs_range_length;
    } else {
        if(value <= this->tree[block_index + 5])
            return range_left + leafs_range_length << 1;
        else
            return range_left + (leafs_range_length << 1) + leafs_range_length; 
    }
}

inline int co_static_search_tree::get_4_base_case(int block_index, int range_left, int og_height, int value) {
    /*
                                    0
                    1                                   2
            3               6                   9                 12
        4       5       7       8           10       11      13          14                    
    */
    int leafs_og_height = og_height - 3;
    int leafs_range_length = (1 << (leafs_og_height - 1));
    if(value <= this->tree[block_index + 1]) {
        if(value <= this->tree[block_index + 3]) {
            if(value <= this->tree[block_index + 4])
                return range_left;
            return range_left + leafs_range_length;
        }
        else
        { //6
            if(value <= this->tree[block_index + 7])
                return range_left + (leafs_range_length << 1);
            return range_left + (leafs_range_length << 1) + leafs_range_length;
        }
    } else //2
    {
        if(value <= this->tree[block_index + 9]) {
            if(value <= this->tree[block_index + 10]) return  range_left + (leafs_range_length << 2);
            return range_left + (leafs_range_length << 2) + leafs_range_length;
        }
        else //12 
        {
            if(value <= this->tree[block_index + 13])
                return range_left + (leafs_range_length << 2) + (leafs_range_length << 1);
            return range_left + (leafs_range_length << 2) + (leafs_range_length << 1) + leafs_range_length;
        }
    }
}

int co_static_search_tree::get(int block_index, int height, int range_left, int og_height, int value) {
    if (height == 1)
    {
        return range_left;
    }
    if(height == 2) {
        if(value <= this->tree[block_index + 1])
            return range_left;
        return range_left + (1 << (og_height - 2));
    }
    if(height == 3){
        return this->get_3_base_case(block_index, range_left, og_height, value);
    }
    if(height == 4) {
        return this->get_4_base_case(block_index, range_left, og_height, value);
    }

    
    int bottom_tree_height = bottom_tree_height_memo[height];
    int top_tree_height = height - bottom_tree_height;

    int index = this->get(block_index, top_tree_height, range_left, og_height, value);
    
    int top_tree_size = (1 << top_tree_height) - 1;

    int bottom_tree_og_height = og_height - top_tree_height;
    int bottom_tree_index = (index - range_left) >> (bottom_tree_og_height - 1);
    int bottom_tree_size = (1 << bottom_tree_height) - 1;

    int bottom_tree_block_index = block_index + top_tree_size + (bottom_tree_index << bottom_tree_height) - bottom_tree_index;
    int bottom_tree_range_left = range_left + (bottom_tree_index << (bottom_tree_og_height - 1));

    if (value <= tree[bottom_tree_block_index]){
        return this->get(bottom_tree_block_index, bottom_tree_height, bottom_tree_range_left, bottom_tree_og_height, value);
    }
    else{
        bottom_tree_index += 1;
        bottom_tree_block_index += bottom_tree_size;
        bottom_tree_range_left += (1 << (bottom_tree_og_height - 1));
        return this->get(bottom_tree_block_index, bottom_tree_height, bottom_tree_range_left, bottom_tree_og_height, value);
    }
}

int co_static_search_tree::get(int value) {
    if(value > this->tree[0]) {
        return NOT_FOUND_INDEX;
    }
    int result = this->get(0, this->height, 0, this->height, value);
    return result;
}

void co_static_search_tree::range_update(int block_index, int height, int range_left,  int og_height, int query_range_left, int query_range_right, int* items) {
    if (height == 1)
    {

        this->tree[block_index] = items[range_left];
        return;
    }

    //update bottom tree
    int bottom_tree_height = bottom_tree_height_memo[height];

    int top_tree_height = height - bottom_tree_height;
    
    int top_tree_size = (1 << top_tree_height) - 1;

    int bottom_tree_og_height = og_height - top_tree_height;
    int bottom_tree_size = (1 << bottom_tree_height) - 1;

    int bottom_tree_index_range_left = (query_range_left - range_left) >> (bottom_tree_og_height - 1);
    int bottom_tree_index_range_right = (query_range_right - range_left) >> (bottom_tree_og_height - 1);

    for (int bottom_tree_index = bottom_tree_index_range_left; bottom_tree_index <= bottom_tree_index_range_right; ++bottom_tree_index) {
        int bottom_tree_block_index = block_index + top_tree_size + (bottom_tree_index << bottom_tree_height) - bottom_tree_index;
        int bottom_tree_range_left = range_left + (bottom_tree_index << (bottom_tree_og_height - 1));
        this->range_update(bottom_tree_block_index, bottom_tree_height, bottom_tree_range_left, bottom_tree_og_height, max(query_range_left, bottom_tree_range_left), min(query_range_right, bottom_tree_range_left + (1 << (bottom_tree_og_height - 1)) - 1), items);
    }

    bottom_tree_index_range_left = bottom_tree_index_range_left & (~1);
    int range_lenght = (1 << (bottom_tree_og_height - 1));
    for (int bottom_tree_index = bottom_tree_index_range_left; bottom_tree_index <= bottom_tree_index_range_right; bottom_tree_index += 2)
    {
        int bottom_tree_block_index = block_index + top_tree_size + (bottom_tree_index << bottom_tree_height) - bottom_tree_index;
        int bottom_tree_range_left = range_left + (bottom_tree_index << (bottom_tree_og_height - 1));
        items[bottom_tree_range_left] = max(this->tree[bottom_tree_block_index], this->tree[bottom_tree_block_index + bottom_tree_size]);
    }

    //update upper tree
    this->range_update(block_index, top_tree_height, range_left, og_height, query_range_left, query_range_right, items);
}

void co_static_search_tree::range_update(int query_range_left, int query_range_right, int *items) {
    
    for (int i = query_range_left; i <= query_range_right; ++i) {
        this->array[i] = items[i];
    }
    this->range_update(0, this->height, 0, this->height, query_range_left, query_range_right, this->array);
}

inline int co_static_search_tree::left_child(int block_index, int depth, int path) {
    if (depth & 1){
        return block_index + 1;
    }
    int biggest_leaving_block_h = (depth & ~(depth - 1));
    int bottom_tree_index = (path << 1) & ((1 << biggest_leaving_block_h) - 1);
    int next_big_block_index = this->block_index_memo[depth + 1 - biggest_leaving_block_h];
    int left_child_block_index = next_big_block_index + ((bottom_tree_index + 1) << biggest_leaving_block_h) - (bottom_tree_index + 1);
    return left_child_block_index;
}

inline int co_static_search_tree::right_child(int block_index, int depth, int path) {
    if (depth & 1){
        return block_index + 2;
    }
    int biggest_leaving_block_h = (depth & ~(depth - 1));
    int bottom_tree_index = ((path << 1) | 1) & ((1 << biggest_leaving_block_h) - 1);
    int next_big_block_index = this->block_index_memo[depth + 1 - biggest_leaving_block_h];
    int right_child_block_index = next_big_block_index + ((bottom_tree_index + 1) << biggest_leaving_block_h) - (bottom_tree_index + 1);
    return right_child_block_index;
}

int co_static_search_tree::update_tree_height_pwr_2(int block_index, int height, int range_left, int og_height, int index, int value) {
    int inner_block_index = 0;
    int depth = 1;
    int path = 0;
    int length = (1 << (og_height - 2));
    while (depth != height)
    {
        this->block_index_memo[depth] = inner_block_index;
        if (index < range_left + length)
        {
            inner_block_index = this->left_child(inner_block_index, depth, path);
            path <<= 1;
        }
        else {
            inner_block_index = this->right_child(inner_block_index, depth, path);
            path = (path << 1) | 1;
            range_left += length;
        }
        length >>= 1;
        depth += 1;
    }
    this->tree[block_index + inner_block_index] = value;
    for (int i = height - 1; i >= 1; --i) {
        path >>= 1;
        int inner_block_index = this->block_index_memo[i];
        int left_child_inner_block_index = this->left_child(inner_block_index, i, path);
        int right_child_inner_block_index = this->right_child(inner_block_index, i, path);
        this->tree[block_index + inner_block_index] = max(this->tree[block_index + left_child_inner_block_index], this->tree[block_index + right_child_inner_block_index]);
    }
    return this->tree[block_index];
}


int co_static_search_tree::get_tree_height_pwr_2(int block_index, int height, int range_left, int og_height, int value) {
    int inner_block_index = 0;
    int depth = 1;
    int path = 0;
    int length = (1 << (og_height - 2));
    while (depth != height)
    {
        this->block_index_memo[depth] = inner_block_index;
        int left_child_inner_block_index = this->left_child(inner_block_index, depth, path);
        if (value <= this->tree[block_index + left_child_inner_block_index])
        {
            path <<= 1;
            inner_block_index = left_child_inner_block_index;
        }
        else {
            inner_block_index = this->right_child(inner_block_index, depth, path);
            path = (path << 1) | 1;
            range_left += length;
        }
        length >>= 1;
        depth += 1;
    }
    return range_left;
}

//-----------------------------------------------------------------------

built_co_static_search_tree::built_co_static_search_tree(int n) {
    this->n = n;
    this->length = next_power_of_2(n);
    this->size = this->length * 2;
    this->height = log2(this->length) + 1;
    this->tree = (int *)malloc(sizeof(int) * this->size * 3);
    this->temp_tree = (int *)malloc(sizeof(int) * this->size);
    this->van_emde_boas_build(0, this->height, this->height, 1);
    this->build(1, this->height);
    free(this->temp_tree);
}

built_co_static_search_tree::~built_co_static_search_tree () {
    free(this->tree);
}

void built_co_static_search_tree::van_emde_boas_build(int tree_l, int h, int og_height, int bfs_order) {
    if (h == 1)
    {
        this->temp_tree[bfs_order] = tree_l;
        return;
    }

    int bottom_tree_h = bottom_tree_height_memo[h];
    int top_tree_h = h - bottom_tree_h;

    this->van_emde_boas_build(tree_l, top_tree_h, og_height, bfs_order);
    
    int top_tree_size = (1 << top_tree_h) - 1;

    int bottom_tree_og_height = og_height - top_tree_h;
    int bottom_tree_size = (1 << bottom_tree_h) - 1;
    int bottom_tree_tree_l = tree_l + top_tree_size;

    for (int bottom_tree_index = 0; bottom_tree_index < (1 << top_tree_h); ++bottom_tree_index) {
        int bottom_tree_bfs_order = (bfs_order << top_tree_h) | bottom_tree_index;
        this->van_emde_boas_build(bottom_tree_tree_l, bottom_tree_h, bottom_tree_og_height, bottom_tree_bfs_order);
        bottom_tree_tree_l += bottom_tree_size;
    }
}

void built_co_static_search_tree::build(int index, int h) {
    if(h == 1) {
        return;
    }
    int van_emde_boas_index = this->temp_tree[index];
    this->tree[van_emde_boas_index * 3 + 1] = this->temp_tree[index << 1] * 3;
    this->tree[van_emde_boas_index * 3 + 2] = this->temp_tree[(index << 1) + 1] * 3;
    this->build(index << 1, h-1);
    this->build((index << 1) + 1, h-1);
}

void built_co_static_search_tree::update(int current_node, int h, int index, int value) {
    if(h == 1) {
        this->tree[current_node] = value;
        return;
    }
    if(index & (1 << (h - 2))) {
        this->update(this->tree[current_node + 2], h - 1, index, value);
    } else {
        this->update(this->tree[current_node + 1], h - 1, index, value);
    }
    this->tree[current_node] = max(this->tree[this->tree[current_node + 1]], this->tree[this->tree[current_node + 2]]);
}

void built_co_static_search_tree::update(int index, int value) {
    this->update(0, this->height, index, value);
}

int built_co_static_search_tree::get(int value) {
    int current_node = 0;
    int index = 0;
    for (int i = 0; i < this->height - 1; ++i)
    {
        if (value <= this->tree[this->tree[current_node + 1]])
        {
            current_node = this->tree[current_node + 1];
            index <<= 1;
        }
        else
        {
            current_node = this->tree[current_node + 2];
            index <<= 1;
            index += 1;
        }
    }
    return index;
}

//-----------------------------------------------------------------------

CA_static_search_tree::CA_static_search_tree(int n) {
    this->n = n;
    this->length = next_power_of_2(n);
    this->size = this->length * 2;
    this->height = log2(this->length) + 1;
    this->tree = (int *)malloc(sizeof(int) * this->size);
    this->parents.resize(this->height);
}

CA_static_search_tree::~CA_static_search_tree() {
    free(this->tree);
}

inline int CA_static_search_tree::merge(int value1, int value2) {
    return max(value1, value2);
}

void CA_static_search_tree::update(int tree_l, int num_inner_nodes, int temp_root, int h, int arr_l, int arr_r, int index, int value) {
    int parents_idx = 0;
    while (arr_l != arr_r) {
        int old_tree_l = tree_l, old_temp_root = temp_root;
        int mid = (arr_l + arr_r) >> 1;
        int new_tree_l = 0, new_tree_r = 0;
        if (h > 0 && (h+1) & 3 == 0) {
            h++;
            num_inner_nodes += (1 << (h-4));
            int mid = (arr_l + arr_r) >> 1;
            new_tree_l = (tree_l<<4) + ((temp_root-8)<<1) + 1;
            new_tree_r = (tree_l<<4) + ((temp_root-8)<<1) + 2;
            if (index <= mid) {
                arr_r = mid;
                tree_l = new_tree_l;
            } else {
                arr_l = mid + 1;
                tree_l = new_tree_r;
            }
            temp_root = 1;
            int last_subtree_size = min((1 << (this->height-((h>>2)<<2))) - 1, 15);
            int real_tree_l = ((num_inner_nodes<<4)-num_inner_nodes) + (new_tree_l-num_inner_nodes)*last_subtree_size;
            int real_tree_r = real_tree_l + last_subtree_size;
            this->parents[parents_idx].parent = (((old_tree_l<<4)-old_tree_l) + old_temp_root);
            this->parents[parents_idx].left = real_tree_l + 1;
            this->parents[parents_idx].right = real_tree_r + 1;
            parents_idx++;
            if (h == this->height - 1) {
                break;
            }
        }
        mid = (arr_l + arr_r) >> 1;
        int left_child = temp_root << 1;
        int right_child = (temp_root << 1) + 1;
        h++;
        int last_subtree_size = min((1 << (this->height-((h>>2)<<2))) - 1, 15);
        int real_subtree_root = ((num_inner_nodes<<4)-num_inner_nodes) + (tree_l-num_inner_nodes)*last_subtree_size;
        this->parents[parents_idx].parent = real_subtree_root + temp_root;
        this->parents[parents_idx].left = real_subtree_root + left_child;
        this->parents[parents_idx].right = real_subtree_root + right_child;
        parents_idx++;
        if (index <= mid) {
            temp_root = left_child; arr_r = mid;
        } else {
            temp_root = right_child; arr_l = mid + 1;
        }
    }
    int last_subtree_size = min((1 << (this->height-((h>>2)<<2))) - 1, 15);
    int real_subtree_root = ((num_inner_nodes<<4)-num_inner_nodes) + (tree_l-num_inner_nodes)*last_subtree_size;
    this->tree[real_subtree_root + temp_root] = value;
    for (int i = parents_idx-1; i >= 0; i--) {
        int old_val = this->tree[this->parents[i].parent];
        int new_val = this->merge(this->tree[this->parents[i].left], this->tree[this->parents[i].right]);
        this->tree[this->parents[i].parent] = new_val;
        // if (old_val == new_val) {
        //     break;
        // }
    }
}

int CA_static_search_tree::get(int tree_l, int num_inner_nodes, int temp_root, int h, int arr_l, int arr_r, int value) {
    while (arr_l != arr_r) {
        int mid = (arr_l + arr_r) >> 1;
        if (h > 0 && (h+1) & 3 == 0) {
            h++;
            num_inner_nodes += (1 << (h-4));
            // update tree_l
            int mid = (arr_l + arr_r) >> 1;
            int left_or_right = 1;
            int new_tree_l = (tree_l << 4) + ((temp_root-8) << 1) + 1;
            tree_l = new_tree_l;
            temp_root = 1;
            int last_subtree_size = min((1 << (this->height-((h>>2)<<2))) - 1, 15);
            int real_subtree_root = ((num_inner_nodes<<4)-num_inner_nodes) + (tree_l-num_inner_nodes)*last_subtree_size;
            if (value <= this->tree[real_subtree_root + temp_root]) {
                arr_r = mid;
            } else {
                arr_l = mid + 1;
                tree_l++;
            }
            if (h == this->height - 1) {
                return arr_l;
            }
        }
        mid = (arr_l + arr_r) >> 1;
        int left_child = temp_root << 1;
        int right_child = (temp_root << 1) + 1;
        h++;
        int last_subtree_size = min((1 << (this->height-((h>>2)<<2))) - 1, 15);
        int real_subtree_root = ((num_inner_nodes<<4)-num_inner_nodes) + (tree_l-num_inner_nodes)*last_subtree_size;
        if(value <= this->tree[real_subtree_root + left_child]) {
            temp_root = left_child; arr_r = mid;
        } else {
            temp_root = right_child; arr_l = mid+1;
        }
    }
    return arr_l;
}

void CA_static_search_tree::update(int index, int value) {
    this->update(0, 0, 1, 0, 0, this->length - 1, index, value);
}

int CA_static_search_tree::get(int value) {
    int result = this->get(0, 0, 1, 0, 0, this->length - 1, value);
    return result;
}

void CA_static_search_tree::print_tree() {
    int start = 1;
    // printf("")
    for (int i = 1; i < this->size; i++) {
        printf("%d ", this->tree[i]);
    }
    printf("\n");
}

//-----------------------------------------------------------------------

static_search_tree::static_search_tree(int n, bool recursive) {
    this->n = n;
    this->recursive = recursive;
    this->length = next_power_of_2(n);
    this->size = this->length * 2;
    this->height = log2(this->length) + 1;
    this->tree = (int *)malloc(sizeof(int) * this->size);
}

static_search_tree::~static_search_tree() {
    free(this->tree);
}

void static_search_tree::print_tree() {
    int start = 1;
    // printf("")
    for (int i = 1; i < this->size; i++) {
        printf("%d ", this->tree[i]);
    }
    printf("\n");
}

inline int static_search_tree::merge(int vlaue1, int value2) {
    return max(vlaue1, value2);
}

void static_search_tree::update_recursive(int tree_l, int arr_l, int arr_r, int index, int value) {
    if (arr_l == arr_r)
    {
        this->tree[tree_l] = value;
        return;
    }

    int mid = (arr_l + arr_r) / 2;
    int left_child = tree_l * 2;
    int right_child = tree_l * 2 + 1;
    if (index <= mid)
    {
        this->update_recursive(left_child, arr_l, mid, index, value);
    }
    else
    {
        this->update_recursive(right_child, mid + 1, arr_r, index, value);
    }

    this->tree[tree_l] = this->merge(this->tree[left_child], this->tree[right_child]);
}

void static_search_tree::update_iterative(int tree_l, int arr_l, int arr_r, int index, int value) {
    while(arr_l != arr_r) {
        int mid = (arr_l + arr_r) >> 1;
        int left_child = tree_l << 1;
        int right_child = left_child + 1;
        if(index <= mid){
            tree_l = left_child;
            arr_r = mid;
        }
        else {
            tree_l = right_child;
            arr_l = mid + 1;
        }
    }
    this->tree[tree_l] = value;
    while(tree_l != 1) {
        tree_l /= 2;
        int left_child = tree_l << 1;
        int right_child = left_child + 1;
        this->tree[tree_l] = this->merge(this->tree[left_child], this->tree[right_child]);
    }
}

int static_search_tree::get_recursive(int tree_l, int arr_l, int arr_r, int value) {
    if (arr_l == arr_r)
    {
        return arr_l;
    }

    int mid = (arr_l + arr_r) / 2;
    int left_child = tree_l * 2;
    int right_child = tree_l * 2 + 1;

    if(value <= this->tree[left_child]) {
        return this->get_recursive(left_child, arr_l, mid, value);
    } else {
        return this->get_recursive(right_child, mid + 1, arr_r, value);
    }
}

int static_search_tree::get_iterative(int tree_l, int arr_l, int arr_r, int value) {
    while(arr_l != arr_r) {
        int mid = (arr_l + arr_r) >> 1;
        int left_child = tree_l << 1;
        int right_child = left_child + 1;
        if(value <= this->tree[left_child]){
            tree_l = left_child;
            arr_r = mid;
        }
        else {
            tree_l = right_child;
            arr_l = mid + 1;
        }
    }
    return arr_l;
}

void static_search_tree:: update(int index, int value){
    if (this->recursive)
    {
        this->update_recursive(1, 0, this->length - 1, index, value);
    }
    else
    {
        this->update_iterative(1, 0, this->length - 1, index, value);
    }
}

int static_search_tree::get(int value) {
    if(this->recursive) {
        int result = this->get_recursive(1, 0, this->length - 1, value);
        return result;
    }
    else {
        int result = this->get_iterative(1, 0, this->length - 1, value);
        return result;
    }
}