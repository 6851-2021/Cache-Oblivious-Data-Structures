#include "indirection_group.h"
#include<algorithm>
#include<assert.h>
#include <iostream>
using namespace std;

indirection_group::indirection_group(int capacity) {
    this->vec.reserve(capacity * 2);
    this->capacity = capacity;
    max_value = INT32_MIN;
}

bool indirection_group::insert(int value) {
    this->vec.push_back(value);
    if(value > this->max_value) {
        this->max_value = value;
    }
    return (this->vec.size() > this->capacity);
}

indirection_group* indirection_group::split(){
    indirection_group *result = new indirection_group(this->capacity);
    int size = this->vec.size();
    sort(this->vec.begin(), this->vec.begin() + size);
    while (this->vec.size() > result->vec.size())
    {
        result->vec.push_back(this->vec.back());
        this->vec.pop_back();
    }
    this->max_value = this->vec.back();
    result->max_value = result->vec[0];
    return result;
}

bool indirection_group::can_merge(indirection_group *that){
    return this->vec.size() + that->vec.size() <= this->capacity;
}

bool indirection_group::merge_and_split(indirection_group *that) {
    assert(this->capacity == that->capacity);
    assert(this->vec.size() <= this->capacity);
    assert(that->vec.size() <= that->capacity);

    while(!that->vec.empty()) {
        this->vec.push_back(that->vec.back());
        that->vec.pop_back();
    }
    sort(this->vec.begin(), this->vec.begin() + this->vec.size());
    
    if(this->vec.size() <= this->capacity) {
        this->max_value = this->vec.back();
        return false;
    }

    while(this->vec.size() > that->vec.size()) {
        that->vec.push_back(this->vec.back());
        this->vec.pop_back();
    }
    this->max_value = this->vec.back();
    that->max_value = that->vec[0];
    return true;
}


int indirection_group::get_max() {
    return this->max_value;
}

bool indirection_group::overloaded() {
    return this->vec.size() > this->capacity;
}