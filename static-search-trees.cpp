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

int CO_static_search_tree::merge(int value1, int value2) {
    return max(value1, value2);
}

CO_static_search_tree::CO_static_search_tree(int n) {
    this->n = n;
    this->length = next_power_of_2(n);
    this->size = this->length * 2;
    this->height = log2(this->length) + 1;
    this->tree = (int *)malloc(sizeof(int) * this->size);

    this->nodes_touched_overall = 0;
    this->nodes_touched_during_query = 0;

    this->recursive_calls_overall = 0;
    this->recursive_call_during_query = 0;
}

CO_static_search_tree::~CO_static_search_tree() {
    free(this->tree);
}

int CO_static_search_tree::update(int tree_l, int h, int arr_l, int arr_r, int index, int value) {
    this->recursive_call_during_query++;
    if (h == 1)
    {
        this->tree[tree_l] = value;
        this->nodes_touched_during_query++;
        return value;
    }
    if(h == 2) {
        if(index < (arr_l + arr_r) / 2) {
            this->tree[tree_l + 1] = value;
            this->nodes_touched_during_query++;
        } else {
            this->tree[tree_l + 2] = value;
            this->nodes_touched_during_query++;   
        }
        //merge
        this->tree[tree_l] = this->merge(this->tree[tree_l + 1], this->tree[tree_l + 2]);
        this->nodes_touched_during_query++;
        return this->tree[tree_l];
    }

    //update bottom tree
    int bottom_tree_h = next_power_of_2(ceil(h / 2.0));
    int top_tree_h = h - bottom_tree_h;
    
    int top_tree_size = (1 << top_tree_h) - 1;
    int number_of_bottom_trees = top_tree_size + 1;

    int bottom_tree_range_length = (arr_r - arr_l) / number_of_bottom_trees;
    int bottom_tree_index = (index - arr_l) / bottom_tree_range_length;
    int bottom_tree_size = (1 << bottom_tree_h) - 1;

    int bottom_tree_tree_l = tree_l + top_tree_size + bottom_tree_index * bottom_tree_size;
    int bottom_tree_arr_l = arr_l + bottom_tree_index * bottom_tree_range_length;
    int bottom_tree_arr_r = bottom_tree_arr_l + bottom_tree_range_length;

    int child_value = this->update(bottom_tree_tree_l, bottom_tree_h, bottom_tree_arr_l, bottom_tree_arr_r, index, value);

    //get adjacent child
    int adjacent_child_value;
    if(bottom_tree_index % 2 == 0) {
        adjacent_child_value = this->tree[bottom_tree_tree_l + bottom_tree_size];
        this->nodes_touched_during_query++;
    } else {
        adjacent_child_value = this->tree[bottom_tree_tree_l - bottom_tree_size];
        this->nodes_touched_during_query++;
    }

    //merge two children value
    int merged_value = this->merge(child_value, adjacent_child_value);

    //update upper tree
    int final_value = this->update(tree_l, top_tree_h, arr_l, arr_r, index, merged_value);

    return final_value;
}

void CO_static_search_tree::update(int index, int value) {
    this->recursive_call_during_query = 0;
    this->nodes_touched_during_query = 0;
    this->update(0, this->height, 0, this->length, index, value);
    this->recursive_calls_overall += this->recursive_call_during_query;
    this->nodes_touched_overall += this->nodes_touched_during_query;
}

int CO_static_search_tree::get(int tree_l, int h, int arr_l, int arr_r, int value) {
    this->recursive_call_during_query++;
    if (h == 1){
        return arr_l;
    }
    if(h == 2) {
        this->nodes_touched_during_query++;
        if(value <= this->tree[tree_l + 1])
            return arr_l;
        return (arr_l + arr_r) / 2;
    }

    int bottom_tree_h = next_power_of_2(ceil(h / 2.0));
    int top_tree_h = h - bottom_tree_h;

    int index = this->get(tree_l, top_tree_h, arr_l, arr_r, value);

    int top_tree_size = (1 << top_tree_h) - 1;
    int number_of_bottom_trees = top_tree_size + 1;

    int bottom_tree_range_length = (arr_r - arr_l) / number_of_bottom_trees;
    int bottom_tree_index = (index - arr_l) / bottom_tree_range_length;
    int bottom_tree_size = (1 << bottom_tree_h) - 1;
    
    int bottom_tree_tree_l = tree_l + top_tree_size + bottom_tree_index * bottom_tree_size;
    int bottom_tree_arr_l = arr_l + bottom_tree_index * bottom_tree_range_length;
    int bottom_tree_arr_r = bottom_tree_arr_l + bottom_tree_range_length;

    
    this->nodes_touched_during_query++;
    if(value <= tree[bottom_tree_tree_l]) {
        return get(bottom_tree_tree_l, bottom_tree_h, bottom_tree_arr_l, bottom_tree_arr_r, value);
    }
    else{
        bottom_tree_index += 1;
        bottom_tree_tree_l = tree_l + top_tree_size + bottom_tree_index * bottom_tree_size;
        bottom_tree_arr_l = arr_l + bottom_tree_index * bottom_tree_range_length;
        bottom_tree_arr_r = bottom_tree_arr_l + bottom_tree_range_length;
        return get(bottom_tree_tree_l, bottom_tree_h, bottom_tree_arr_l, bottom_tree_arr_r, value);
    }
}

int CO_static_search_tree::get(int value) {
    this->nodes_touched_during_query = 0;
    this->recursive_call_during_query = 0;
    int result = this->get(0, this->height, 0, this->length, value);
    this->recursive_calls_overall += this->recursive_call_during_query;
    this->nodes_touched_overall += this->nodes_touched_during_query;
    return result;
}

long long CO_static_search_tree::get_num_of_touched_nodes() { return this->nodes_touched_overall; }

long long CO_static_search_tree::get_num_of_recursive_calls() { return this->recursive_calls_overall; }

static_search_tree::static_search_tree(int n) {
    this->n = n;
    this->length = next_power_of_2(n);
    this->size = this->length * 2;
    this->height = log2(this->length) + 1;
    this->tree = (int *)malloc(sizeof(int) * this->size);

    this->nodes_touched_overall = 0;
    this->nodes_touched_during_query = 0;

    this->recursive_calls_overall = 0;
    this->recursive_call_during_query = 0;
}

static_search_tree::~static_search_tree() {
    free(this->tree);
}

int static_search_tree::merge(int vlaue1, int value2) {
    return max(vlaue1, value2);
}

void static_search_tree::update(int tree_l, int arr_l, int arr_r, int index, int value) {
    this->recursive_call_during_query++;
    if (arr_l == arr_r)
    {
        this->nodes_touched_during_query++;
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
    
    this->nodes_touched_during_query++;
    this->nodes_touched_during_query++;
    this->nodes_touched_during_query++;
    this->tree[tree_l] = this->merge(this->tree[left_child], this->tree[right_child]);
}

int static_search_tree::get(int tree_l, int arr_l, int arr_r, int value) {
    this->recursive_call_during_query++;
    if (arr_l == arr_r)
    {
        return arr_l;
    }

    int mid = (arr_l + arr_r) / 2;
    int left_child = tree_l * 2;
    int right_child = tree_l * 2 + 1;

    this->nodes_touched_during_query++;
    if(value <= this->tree[left_child]) {
        return this->get(left_child, arr_l, mid, value);
    } else {
        return this->get(right_child, mid + 1, arr_r, value);
    }
}

void static_search_tree:: update(int index, int value){
    this->recursive_call_during_query = 0;
    this->nodes_touched_during_query = 0;
    this->update(1, 0, this->length - 1, index, value);
    this->recursive_calls_overall += this->recursive_call_during_query;
    this->nodes_touched_overall += this->nodes_touched_during_query;
}

int static_search_tree::get(int value) {
    this->nodes_touched_during_query = 0;
    this->recursive_call_during_query = 0;
    int result = this->get(1, 0, this->length - 1, value);
    this->recursive_calls_overall += this->recursive_call_during_query;
    this->nodes_touched_overall += this->nodes_touched_during_query;
    return result;
}

long long static_search_tree::get_num_of_touched_nodes() { return this->nodes_touched_overall; }

long long static_search_tree::get_num_of_recursive_calls() { return this->recursive_calls_overall; }