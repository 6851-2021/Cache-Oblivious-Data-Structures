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
    return this->get(0, this->height, 0, this->length, value);
}

// int main() {
//     int n = 1024;
//     CO_static_search_tree ds(n);
//     for (int i = 0; i < n; ++i) {
//         ds.update(i, i * 2);
//     }
//     for (int i = 0; i <=  2 * (n-1); ++i) {
//         cout << "value: " << i << " at index :" << ds.get(i) << endl;
//     }
// }