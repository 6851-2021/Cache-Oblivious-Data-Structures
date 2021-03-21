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

const int mxn = (1 << 20);
int tree[mxn];

int update(int tree_l, int h, int arr_l, int arr_r, int index, int value) {

    // cout << tree_l << " " << h << " " << arr_l << " "<<index<<" "<<value<<endl;
    if (h == 1)
    {
        tree[tree_l] = value;
        return value;
    }
    if(h == 2) {
        if(index < (arr_l + arr_r) / 2) {
            tree[tree_l + 1] = value;
        } else {
            tree[tree_l + 2] = value;   
        }
        //merge
        tree[tree_l] = tree[tree_l + 1] + tree[tree_l + 2];
        return tree[tree_l];
    }

    //update bottom tree
    int bottom_tree_h = next_power_of_2(ceil(h / 2.0));
    int top_tree_h = h - bottom_tree_h;

    int bottom_tree_range_length = (1 << (bottom_tree_h - 1));
    int bottom_tree_index = (index - arr_l) / bottom_tree_range_length;
    int bottom_tree_size = (1 << bottom_tree_h) - 1;
    int top_tree_size = (1 << top_tree_h) - 1;

    int bottom_tree_tree_l = tree_l + top_tree_size + bottom_tree_index * bottom_tree_size;
    int bottom_tree_arr_l = arr_l + bottom_tree_index * bottom_tree_range_length;
    int bottom_tree_arr_r = bottom_tree_arr_l + bottom_tree_range_length;

    int child_value = update(bottom_tree_tree_l, bottom_tree_h, bottom_tree_arr_l, bottom_tree_arr_r, index, value);

    //get adjacent child
    int adjacent_child_value;
    if(bottom_tree_index % 2 == 0) {
        adjacent_child_value = tree[bottom_tree_tree_l + bottom_tree_size];
    } else {
        adjacent_child_value = tree[bottom_tree_tree_l - bottom_tree_size];
    }

    //merge two children value
    int merged_value = child_value + adjacent_child_value;

    //update upper tree
    int final_value = update(tree_l, top_tree_h, arr_l, arr_r, index, merged_value);

    return final_value;
}

int main() {
    int n = 16;
    for (int i = 0; i < n; ++i) {
        // cout << "Update: "
        //      << " " << i << endl;
        update(0, 5, 0, 16, i, i);
        // cout << endl;
    }
    // for (int i = 0; i < 31; ++i){
    //     cout << i + 1 << " " << tree[i] << endl;
    // }
}