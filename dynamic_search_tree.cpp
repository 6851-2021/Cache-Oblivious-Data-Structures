#include "dynamic_search_tree.h"

co_dynamic_serach_tree::co_dynamic_serach_tree() {
    setup(&this->list);
    this->N = this->list.N;
    this->tree = new CO_static_search_tree(this->N);
}

co_dynamic_serach_tree::~co_dynamic_serach_tree() {
    free(this->list.items);
}

bool debug = false;

void co_dynamic_serach_tree::add(int value) {
        if (debug)
            cout << "Insert: " << value << "\n";
    
    int index = this->tree->get(value);
    if(index == -1 )
        index = this->list.N - 1;

    if(debug) cout << "Insert at index: " << index << "\n";
    if(debug) cout << "N Now: " << this->N << endl;
    int current_length = this->list.N;
    insert(&this->list, index, value);
    if(debug) cout << "Finished Inserting OFM" << endl;
    if (current_length != this->list.N)
    { //OFM resized
        this->N = this->list.N;
        delete (this->tree);
        this->tree = new CO_static_search_tree(this->N);
        this->tree->range_update(0, this->N -1, this->list.items);
    }
    else
    {
       if(debug) cout << "N Now: " << this->N << endl;

        if(debug) cout << this->list.min_index << " " << this->list.max_index<< endl;

        this->tree->range_update(this->list.min_index, this->list.max_index, this->list.items);
        // this->tree->range_update(0, this->N -1, this->list.items);
    }

    if(debug) printf("OFM:\n");
    if(debug) print_array(&this->list);
    if(debug) printf("CO SST:\n");
    if(debug) this->tree->print();
    
}

int co_dynamic_serach_tree::get_successor(int value) {
    int index = this->tree->get(value);
    if(index == -1) {
        return index;
    }
    return this->list.items[index];
}