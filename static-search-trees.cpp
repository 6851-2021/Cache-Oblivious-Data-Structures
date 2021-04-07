#include "static-search-trees.h"

#include<iostream>
#include<math.h>
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

const int bottom_tree_h_memo[] = {0,1,1,2,2,4,4,4,4,8,8,8,8,8,8,8,8,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32};

inline int CO_static_search_tree::merge(int value1, int value2) {
    return max(value1, value2);
}

CO_static_search_tree::CO_static_search_tree(int n) {
    this->n = n;
    this->length = next_power_of_2(n);
    this->size = this->length * 2;
    this->height = log2(this->length) + 1;
    this->tree = (int *)malloc(sizeof(int) * this->size);
}

CO_static_search_tree::~CO_static_search_tree() {
    free(this->tree);
}

inline int CO_static_search_tree::update_3_base_case(int tree_l, int h, int arr_l, int og_height, int index, int value) {
    /*
                            0
                    1               4
                2       3       5       6
    */
    int leafs_og_height = og_height - 2;
    int leaf_index = (index - arr_l) >> (leafs_og_height - 1);
    if(leaf_index == 0) {
        this->tree[tree_l + 2] = value;
        this->tree[tree_l + 1] = max(this->tree[tree_l + 2], this->tree[tree_l + 3]);
        this->tree[tree_l + 0] = max(this->tree[tree_l + 1], this->tree[tree_l + 4]);
    }
    else if(leaf_index == 1) {
        this->tree[tree_l + 3] = value;
        this->tree[tree_l + 1] = max(this->tree[tree_l + 2], this->tree[tree_l + 3]);
        this->tree[tree_l + 0] = max(this->tree[tree_l + 1], this->tree[tree_l + 4]);
    }
    else if(leaf_index == 2) {
        this->tree[tree_l + 5] = value;
        this->tree[tree_l + 4] = max(this->tree[tree_l + 5], this->tree[tree_l + 6]);
        this->tree[tree_l + 0] = max(this->tree[tree_l + 1], this->tree[tree_l + 4]);
    }
    else if(leaf_index == 3) {
        this->tree[tree_l + 6] = value;
        this->tree[tree_l + 4] = max(this->tree[tree_l + 5], this->tree[tree_l + 6]);
        this->tree[tree_l + 0] = max(this->tree[tree_l + 1], this->tree[tree_l + 4]);
    }
    return this->tree[tree_l];
}

inline int CO_static_search_tree::update_4_base_case(int tree_l, int h, int arr_l, int og_height, int index, int value) {
    /*
                                    0
                    1                                   2
            3               6                   9                 12
        4       5       7       8           10       11      13          14                    
    */
    int leafs_og_height = og_height - 3;
    int leaf_index = (index - arr_l) >> (leafs_og_height - 1);
    if(leaf_index == 0) {
        this->tree[tree_l + 4] = value;
        this->tree[tree_l + 3] = max(this->tree[tree_l + 4], this->tree[tree_l + 5]);
        this->tree[tree_l + 1] = max(this->tree[tree_l + 3], this->tree[tree_l + 6]);
        this->tree[tree_l + 0] = max(this->tree[tree_l + 1], this->tree[tree_l + 2]);
    }
    else if(leaf_index == 1) {
        this->tree[tree_l + 5] = value;
        this->tree[tree_l + 3] = max(this->tree[tree_l + 4], this->tree[tree_l + 5]);
        this->tree[tree_l + 1] = max(this->tree[tree_l + 3], this->tree[tree_l + 6]);
        this->tree[tree_l + 0] = max(this->tree[tree_l + 1], this->tree[tree_l + 2]);
    }
    else if(leaf_index == 2) {
        this->tree[tree_l + 7] = value;
        this->tree[tree_l + 6] = max(this->tree[tree_l + 7], this->tree[tree_l + 8]);
        this->tree[tree_l + 1] = max(this->tree[tree_l + 3], this->tree[tree_l + 6]);
        this->tree[tree_l + 0] = max(this->tree[tree_l + 1], this->tree[tree_l + 2]);
    }
    else if(leaf_index == 3) {
        this->tree[tree_l + 8] = value;
        this->tree[tree_l + 6] = max(this->tree[tree_l + 7], this->tree[tree_l + 8]);
        this->tree[tree_l + 1] = max(this->tree[tree_l + 3], this->tree[tree_l + 6]);
        this->tree[tree_l + 0] = max(this->tree[tree_l + 1], this->tree[tree_l + 2]);
    }
    else if(leaf_index == 4) {
        this->tree[tree_l + 10] = value;
        this->tree[tree_l + 9] = max(this->tree[tree_l + 10], this->tree[tree_l + 11]);
        this->tree[tree_l + 2] = max(this->tree[tree_l + 9], this->tree[tree_l + 12]);
        this->tree[tree_l + 0] = max(this->tree[tree_l + 1], this->tree[tree_l + 2]);
    }
    else if(leaf_index == 5){
        this->tree[tree_l + 11] = value;
        this->tree[tree_l + 9] = max(this->tree[tree_l + 10], this->tree[tree_l + 11]);
        this->tree[tree_l + 2] = max(this->tree[tree_l + 9], this->tree[tree_l + 12]);
        this->tree[tree_l + 0] = max(this->tree[tree_l + 1], this->tree[tree_l + 2]);
    }
    else if(leaf_index == 6){
        this->tree[tree_l + 13] = value;
        this->tree[tree_l + 12] = max(this->tree[tree_l + 13], this->tree[tree_l + 14]);
        this->tree[tree_l + 2] = max(this->tree[tree_l + 9], this->tree[tree_l + 12]);
        this->tree[tree_l + 0] = max(this->tree[tree_l + 1], this->tree[tree_l + 2]);
    }
    else if(leaf_index == 7){
        this->tree[tree_l + 14] = value;
        this->tree[tree_l + 12] = max(this->tree[tree_l + 13], this->tree[tree_l + 14]);
        this->tree[tree_l + 2] = max(this->tree[tree_l + 9], this->tree[tree_l + 12]);
        this->tree[tree_l + 0] = max(this->tree[tree_l + 1], this->tree[tree_l + 2]);
    }
    return this->tree[tree_l];
}

int CO_static_search_tree::update(int tree_l, int h, int arr_l, int og_height, int index, int value) {
    if (h == 1)
    {
        this->tree[tree_l] = value;
        return value;
    }
    if(h == 2) {
        if(index < arr_l + (1 << (og_height - 2))) {
            this->tree[tree_l + 1] = value;
        } else {
            this->tree[tree_l + 2] = value;
        }
        //merge
        this->tree[tree_l] = this->merge(this->tree[tree_l + 1], this->tree[tree_l + 2]);
        return this->tree[tree_l];
    }
    if(h == 3) {
        return this->update_3_base_case(tree_l, h, arr_l, og_height, index, value);
    }   
    if(h == 4) {
        return this->update_4_base_case(tree_l, h, arr_l, og_height, index, value);
    }

    //update bottom tree
    int bottom_tree_h = bottom_tree_h_memo[h];
    // int bottom_tree_h = next_power_of_2((int)ceil(h / 2));

    int top_tree_h = h - bottom_tree_h;
    
    int top_tree_size = (1 << top_tree_h) - 1;

    int bottom_tree_og_height = og_height - top_tree_h;
    int bottom_tree_index = (index - arr_l) >> (bottom_tree_og_height - 1);
    int bottom_tree_size = (1 << bottom_tree_h) - 1;

    int bottom_tree_tree_l = tree_l + top_tree_size + (bottom_tree_index << bottom_tree_h) - bottom_tree_index;
    int bottom_tree_arr_l = arr_l + (bottom_tree_index << (bottom_tree_og_height - 1));

    int child_value = this->update(bottom_tree_tree_l, bottom_tree_h, bottom_tree_arr_l, bottom_tree_og_height, index, value);

    //get adjacent child
    int adjacent_child_value;
    if(bottom_tree_index % 2 == 0) {
        adjacent_child_value = this->tree[bottom_tree_tree_l + bottom_tree_size];
    } else {
        adjacent_child_value = this->tree[bottom_tree_tree_l - bottom_tree_size];
    }

    //merge two children value
    int merged_value = this->merge(child_value, adjacent_child_value);

    //update upper tree
    int final_value = this->update(tree_l, top_tree_h, arr_l, og_height, index, merged_value);

    return final_value;
}

void CO_static_search_tree::update(int index, int value) {
    this->update(0, this->height, 0, this->height, index, value);
}

inline int CO_static_search_tree::get_3_base_case(int tree_l, int h, int arr_l, int og_height, int value) {
    /*
                            0
                    1               4
                2       3       5       6
    */

    int leafs_og_height = og_height - 2;
    int leafs_range_length = (1 << (leafs_og_height - 1));
    if(value <= this->tree[tree_l + 1]){
        if (value <= this->tree[tree_l + 2])
            return arr_l;
        else    
            return arr_l + leafs_range_length;
    } else {
        if(value <= this->tree[tree_l + 5])
            return arr_l + leafs_range_length << 1;
        else
            return arr_l + (leafs_range_length << 1) + leafs_range_length; 
    }
}

inline int CO_static_search_tree::get_4_base_case(int tree_l, int h, int arr_l, int og_height, int value) {
    /*
                                    0
                    1                                   2
            3               6                   9                 12
        4       5       7       8           10       11      13          14                    
    */
    int leafs_og_height = og_height - 3;
    int leafs_range_length = (1 << (leafs_og_height - 1));
    if(value <= this->tree[tree_l + 1]) {
        if(value <= this->tree[tree_l + 3]) {
            if(value <= this->tree[tree_l + 4])
                return arr_l;
            return arr_l + leafs_range_length;
        }
        else
        { //6
            if(value <= this->tree[tree_l + 7])
                return arr_l + (leafs_range_length << 1);
            return arr_l + (leafs_range_length << 1) + leafs_range_length;
        }
    } else //2
    {
        if(value <= this->tree[tree_l + 9]) {
            if(value <= this->tree[tree_l + 10]) return  arr_l + (leafs_range_length << 2);
            return arr_l + (leafs_range_length << 2) + leafs_range_length;
        }
        else //12 
        {
            if(value <= this->tree[tree_l + 13])
                return arr_l + (leafs_range_length << 2) + (leafs_range_length << 1);
            return arr_l + (leafs_range_length << 2) + (leafs_range_length << 1) + leafs_range_length;
        }
    }
}

int CO_static_search_tree::get(int tree_l, int h, int arr_l, int og_height, int value) {
    if (h == 1){
        return arr_l;
    }
    if(h == 2) {
        if(value <= this->tree[tree_l + 1])
            return arr_l;
        return arr_l + (1 << (og_height - 2));
    }
    if(h == 3){
        return this->get_3_base_case(tree_l, h, arr_l, og_height, value);
    }
    if(h == 4) {
        return this->get_4_base_case(tree_l, h, arr_l, og_height, value);
    }

    int bottom_tree_h = bottom_tree_h_memo[h];
    // int bottom_tree_h = next_power_of_2((int)ceil(h / 2));
    int top_tree_h = h - bottom_tree_h;

    int index = this->get(tree_l, top_tree_h, arr_l, og_height, value);
    
    int top_tree_size = (1 << top_tree_h) - 1;

    int bottom_tree_og_height = og_height - top_tree_h;
    int bottom_tree_index = (index - arr_l) >> (bottom_tree_og_height - 1);
    int bottom_tree_size = (1 << bottom_tree_h) - 1;

    int bottom_tree_tree_l = tree_l + top_tree_size + (bottom_tree_index << bottom_tree_h) - bottom_tree_index;
    int bottom_tree_arr_l = arr_l + (bottom_tree_index << (bottom_tree_og_height - 1));

    if(value <= tree[bottom_tree_tree_l]) {
        return get(bottom_tree_tree_l, bottom_tree_h, bottom_tree_arr_l, bottom_tree_og_height , value);
    }
    else{
        bottom_tree_index += 1;
        bottom_tree_tree_l += bottom_tree_size;
        bottom_tree_arr_l += (1 << (bottom_tree_og_height - 1));
        return get(bottom_tree_tree_l, bottom_tree_h, bottom_tree_arr_l, bottom_tree_og_height , value);
    }
}

int CO_static_search_tree::get(int value) {
    int result = this->get(0, this->height, 0, this->height, value);
    return result;
}


//-----------------------------------------------------------------------

CA_static_search_tree::CA_static_search_tree(int n) {
    this->n = n;
    this->length = next_power_of_2(n);
    this->size = this->length * 2;
    this->height = log2(this->length) + 1;
    this->tree = (int *)malloc(sizeof(int) * this->size);
}

CA_static_search_tree::~CA_static_search_tree() {
    free(this->tree);
}

inline int CA_static_search_tree::merge(int value1, int value2) {
    return max(value1, value2);
}

void CA_static_search_tree::update(int tree_l, int num_inner_nodes, int temp_root, int h, int arr_l, int arr_r, int index, int value) {
    if (arr_l == arr_r)
    {
        int last_subtree_size = min((1 << (this->height-((h>>2)<<2))) - 1, 15);
        int real_subtree_root = num_inner_nodes*15 + (tree_l-num_inner_nodes)*last_subtree_size;
        // printf("update at index %d, real index %d, value %d\n", arr_l, tree_l + temp_root, value);
        this->tree[real_subtree_root + temp_root] = value;
        return;
    }
    int old_tree_l = tree_l, old_temp_root = temp_root;
    int mid = (arr_l + arr_r) / 2;
    int new_tree_l = 0, new_tree_r = 0;
    if (h > 0 && (h+1) & 3 == 0) {
        h++;
        int old_num_inner_nodes = num_inner_nodes;
        num_inner_nodes += (1 << (h-4));
        // update tree_l
        int mid = (arr_l + arr_r) / 2;
        new_tree_l = tree_l*16 + (temp_root-8)*2 + 1;
        new_tree_r = tree_l*16 + (temp_root-8)*2 + 2;
        if (index <= mid) {
            arr_r = mid;
            tree_l = new_tree_l;
        } else {
            arr_l = mid + 1;
            tree_l = new_tree_r;
        }
        temp_root = 1;
        if (h == this->height - 1) {
            int last_subtree_size = min((1 << (this->height-((h>>2)<<2))) - 1, 15);
            int real_subtree_root = num_inner_nodes*15 + (tree_l-num_inner_nodes)*last_subtree_size;
            this->tree[real_subtree_root + temp_root] = value;
            // printf("here....\n");
            int real_tree_l = num_inner_nodes*15 + (new_tree_l-num_inner_nodes)*last_subtree_size;
            int real_tree_r = real_tree_l + last_subtree_size;
            int old_real_subtree_root = old_tree_l*15;
            this->tree[old_real_subtree_root + old_temp_root] = this->merge(this->tree[real_tree_l + 1], this->tree[real_tree_r + 1]);
            return;
        }
    }
    mid = (arr_l + arr_r) / 2;
    int left_child = temp_root * 2;
    int right_child = temp_root * 2 + 1;
    h++;
    if (index <= mid)
    {
        this->update(tree_l, num_inner_nodes, left_child, h, arr_l, mid, index, value);
    }
    else
    {
        this->update(tree_l, num_inner_nodes, right_child, h, mid + 1, arr_r, index, value);
    }
    int last_subtree_size = min((1 << (this->height-((h>>2)<<2))) - 1, 15);
    int real_subtree_root = num_inner_nodes*15 + (tree_l-num_inner_nodes)*last_subtree_size;
    this->tree[real_subtree_root + temp_root] = this->merge(this->tree[real_subtree_root + left_child], this->tree[real_subtree_root + right_child]);
    if (old_tree_l != tree_l) {
        int last_subtree_size = min((1 << (this->height-((h>>2)<<2))) - 1, 15);
        int real_tree_l = num_inner_nodes*15 + (new_tree_l-num_inner_nodes)*last_subtree_size;
        int real_tree_r = real_tree_l + last_subtree_size;
        int old_real_subtree_root = old_tree_l*15;
        this->tree[old_real_subtree_root + old_temp_root] = this->merge(this->tree[real_tree_l + 1], this->tree[real_tree_r + 1]);
    }
}

int CA_static_search_tree::get(int tree_l, int num_inner_nodes, int temp_root, int h, int arr_l, int arr_r, int value) {
    if (arr_l == arr_r)
    {
        // printf("get at index %d, real index %d, value %d\n", arr_l, tree_l + temp_root, this->tree[tree_l+temp_root]);
        return arr_l;
    }
    int mid = (arr_l + arr_r) / 2;
    if (h > 0 && (h+1) & 3 == 0) {
        h++;
        num_inner_nodes += (1 << (h-4));
        // update tree_l
        int mid = (arr_l + arr_r) / 2;
        int left_or_right = 1;
        int new_tree_l = tree_l*16 + (temp_root-8)*2 + 1;
        tree_l = new_tree_l;
        temp_root = 1;
        int last_subtree_size = min((1 << (this->height-((h>>2)<<2))) - 1, 15);
        int real_subtree_root = num_inner_nodes*15 + (tree_l-num_inner_nodes)*last_subtree_size;
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
    mid = (arr_l + arr_r) / 2;
    int left_child = temp_root * 2;
    int right_child = temp_root * 2 + 1;
    h++;
    int last_subtree_size = min((1 << (this->height-((h>>2)<<2))) - 1, 15);
    int real_subtree_root = num_inner_nodes*15 + (tree_l-num_inner_nodes)*last_subtree_size;
    if(value <= this->tree[real_subtree_root + left_child]) {
        return this->get(tree_l, num_inner_nodes, left_child, h, arr_l, mid, value);
    } else {
        return this->get(tree_l, num_inner_nodes, right_child, h, mid + 1, arr_r, value);
    }
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