#include "static-search-trees.h"

#include<iostream>
#include<math.h>
using namespace std;

int next_power_of_2(unsigned int n) {
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n; 
}

const int next_power_of_2_memo[] = {
    0,
    1,
    2,
    4,
    4,
    8,
    8,
    8,
    8,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    16,
    32,
    32,
    32,
    32,
    32,
    32,
    32,
    32,
    32,
    32,
    32,
    32,
    32,
    32,
    32,
    32,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
};

int CO_static_search_tree::merge(int value1, int value2) {
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

int CO_static_search_tree::update(int tree_l, int h, int arr_l, int arr_r, int index, int value) {
    if (h == 1)
    {
        this->tree[tree_l] = value;
        return value;
    }
    if(h == 2) {
        if(index < (arr_l + arr_r) / 2) {
            this->tree[tree_l + 1] = value;
        } else {
            this->tree[tree_l + 2] = value;
        }
        //merge
        this->tree[tree_l] = this->merge(this->tree[tree_l + 1], this->tree[tree_l + 2]);
        return this->tree[tree_l];
    }

    //update bottom tree
    int bottom_tree_h = next_power_of_2_memo[(int)ceil(h / 2.0)];
    int top_tree_h = h - bottom_tree_h;
    
    int top_tree_size = (1 << top_tree_h) - 1;
    int number_of_bottom_trees = top_tree_size + 1;

    int bottom_tree_range_length = (arr_r - arr_l) >> top_tree_h;
    int bottom_tree_index = (index - arr_l) / bottom_tree_range_length;
    int bottom_tree_size = (1 << bottom_tree_h) - 1;

    int bottom_tree_tree_l = tree_l + top_tree_size + (bottom_tree_index << bottom_tree_h) - bottom_tree_index;
    int bottom_tree_arr_l = arr_l + bottom_tree_index * bottom_tree_range_length;
    int bottom_tree_arr_r = bottom_tree_arr_l + bottom_tree_range_length;

    int child_value = this->update(bottom_tree_tree_l, bottom_tree_h, bottom_tree_arr_l, bottom_tree_arr_r, index, value);

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
    int final_value = this->update(tree_l, top_tree_h, arr_l, arr_r, index, merged_value);

    return final_value;
}

void CO_static_search_tree::update(int index, int value) {
    this->update(0, this->height, 0, this->length, index, value);
}

int CO_static_search_tree::get(int tree_l, int h, int arr_l, int arr_r, int value) {
    if (h == 1){
        return arr_l;
    }
    if(h == 2) {
        if(value <= this->tree[tree_l + 1])
            return arr_l;
        return (arr_l + arr_r) / 2;
    }

    int bottom_tree_h = next_power_of_2_memo[(int)ceil(h / 2.0)];
    int top_tree_h = h - bottom_tree_h;

    int index = this->get(tree_l, top_tree_h, arr_l, arr_r, value);

    int top_tree_size = (1 << top_tree_h) - 1;
    int number_of_bottom_trees = top_tree_size + 1;

    int bottom_tree_range_length = (arr_r - arr_l) >> top_tree_h;
    int bottom_tree_index = (index - arr_l) / bottom_tree_range_length;
    int bottom_tree_size = (1 << bottom_tree_h) - 1;

    int bottom_tree_tree_l = tree_l + top_tree_size + (bottom_tree_index << bottom_tree_h) - bottom_tree_index;
    int bottom_tree_arr_l = arr_l + bottom_tree_index * bottom_tree_range_length;
    int bottom_tree_arr_r = bottom_tree_arr_l + bottom_tree_range_length;

    if(value <= tree[bottom_tree_tree_l]) {
        return get(bottom_tree_tree_l, bottom_tree_h, bottom_tree_arr_l, bottom_tree_arr_r, value);
    }
    else{
        bottom_tree_index += 1;
        bottom_tree_tree_l += bottom_tree_size;
        bottom_tree_arr_l += bottom_tree_range_length;
        bottom_tree_arr_r = bottom_tree_arr_l + bottom_tree_range_length;
        return get(bottom_tree_tree_l, bottom_tree_h, bottom_tree_arr_l, bottom_tree_arr_r, value);
    }
}

int CO_static_search_tree::get(int value) {
    int result = this->get(0, this->height, 0, this->length, value);
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

int CA_static_search_tree::merge(int value1, int value2) {
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
    if (h > 0 && (h+1) % 4 == 0) {
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
    if (h > 0 && (h+1) % 4 == 0) {
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

static_search_tree::static_search_tree(int n) {
    this->n = n;
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

int static_search_tree::merge(int vlaue1, int value2) {
    return max(vlaue1, value2);
}

void static_search_tree::update(int tree_l, int arr_l, int arr_r, int index, int value) {
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
        this->update(left_child, arr_l, mid, index, value);
    }
    else
    {
        this->update(right_child, mid + 1, arr_r, index, value);
    }
    

    this->tree[tree_l] = this->merge(this->tree[left_child], this->tree[right_child]);
}

int static_search_tree::get(int tree_l, int arr_l, int arr_r, int value) {
    if (arr_l == arr_r)
    {
        return arr_l;
    }

    int mid = (arr_l + arr_r) / 2;
    int left_child = tree_l * 2;
    int right_child = tree_l * 2 + 1;

    if(value <= this->tree[left_child]) {
        return this->get(left_child, arr_l, mid, value);
    } else {
        return this->get(right_child, mid + 1, arr_r, value);
    }
}

void static_search_tree:: update(int index, int value){

    this->update(1, 0, this->length - 1, index, value);
}

int static_search_tree::get(int value) {
    int result = this->get(1, 0, this->length - 1, value);
    return result;
}