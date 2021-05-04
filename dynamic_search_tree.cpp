#include "dynamic_search_tree.h"

co_dynamic_serach_tree::co_dynamic_serach_tree() {
    setup(&this->list);
    this->N = this->list.N;
    this->tree = new CO_static_search_tree(this->N);
}

co_dynamic_serach_tree::~co_dynamic_serach_tree() {
    free(this->list.items);
}

void co_dynamic_serach_tree::add(int value) {
    // cout << "Insert: " << value << "\n";
    
    int index = this->tree->get(value);

    // cout << "Insert at index: " << index << "\n";
    // cout << "N Now: " << this->N << endl;
    int current_length = this->list.N;
    insert(&this->list, index, value);
    // cout << "Finished Inserting OFM" << endl;
    if (current_length != this->list.N)
    { //OFM resized
        this->N = this->list.N;
        delete (this->tree);
        this->tree = new CO_static_search_tree(this->N);
        this->tree->range_update(0, this->N -1, this->list.items);
    }
    else
    {
        // cout << "N Now: " << this->N << endl;

        // cout << this->list.min_index << " " << this->list.max_index<< endl;

        // this->tree->range_update(this->list.min_index, this->list.max_index, this->list.items);
        this->tree->range_update(0, this->N -1, this->list.items);
    }

    // printf("OFM:\n");
    // print_array(&this->list);
    // printf("CO SST:\n");
    // this->tree->print();
    
}

int co_dynamic_serach_tree::get_successor(int value) {
    int index = this->tree->get(value);
    return this->list.items[index];
}