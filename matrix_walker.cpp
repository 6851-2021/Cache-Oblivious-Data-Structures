#include "matrix_walker.h"
#include <stdlib.h> 
#include <iostream>

naive_matrix_walker:: naive_matrix_walker(int n, int m) {
    this->n = n;
    this->m = m;
    this->arr = (int*) malloc(n * m * sizeof(int));
}

inline int naive_matrix_walker::translate(int i, int j) {
    return i * this->m + j;
}

void naive_matrix_walker::teleport(int i, int j) {
    this->i = i;
    this->j = j;
    this->value = *(this->arr + this->translate(this->i, this->j));
}

void naive_matrix_walker::move_left() {
    this->j = this->j - 1;
    this->value = *(this->arr + this->translate(this->i, this->j));
}

void naive_matrix_walker::move_right() {
    this->j = this->j + 1;
    this->value = *(this->arr + this->translate(this->i, this->j));
}

void naive_matrix_walker::move_up() {
    this->i = this->i - 1;
    this->value = *(this->arr + this->translate(this->i, this->j));
}

void naive_matrix_walker::move_down() {
    this->i = this->i + 1;
    this->value = *(this->arr + this->translate(this->i, this->j));
}
int naive_matrix_walker::get() {
    return this->value;
}
void naive_matrix_walker::set(int i, int j, int value) {
    *(this->arr + this->translate(i, j)) = value;
}

/***************************************************************************************************************/

co_matrix_walker:: co_matrix_walker(int n, int m) {
    this->n = n;
    this->m = m;
    this->arr = (int*) malloc(n * m * sizeof(int));
}

inline int co_matrix_walker::translate(int i, int j) {
    int top_left_i = 0;
    int top_left_j = 0;
    int bottom_right_i = this->n;
    int bottom_right_j = this->m;
    int block_index = 0;
    /*
    --------------
    |  1   |  2  |
    --------------
    |  3   |  4  |
    --------------
    */
    while (top_left_i != bottom_right_i - 1 && top_left_j != bottom_right_j - 1)
    {
        int mid_i = (top_left_i + bottom_right_i) >> 1;
        int mid_j = (top_left_j + bottom_right_j) >> 1;

        if(i >= mid_i) {
            block_index += (mid_i - top_left_i) * (bottom_right_j - top_left_j);
            if(j >= mid_j) {
                block_index += (mid_j - top_left_j) * (bottom_right_i - mid_i);
                top_left_i = mid_i;
                top_left_j = mid_j;
            } else {
                top_left_i = mid_i;
                bottom_right_j = mid_j;
            }
        } else {
            if(j >= mid_j) {
                block_index += (mid_j - top_left_j) * (mid_i - top_left_i);
                bottom_right_i = mid_i;
                top_left_j = mid_j;
            } else {
                bottom_right_i = mid_i;
                bottom_right_j = mid_j;
            }
        }
    }
    //at the end we might end up with a 1D block
    return block_index + (i - top_left_i) + (j - top_left_j);
}

void co_matrix_walker::teleport(int i, int j) {
    this->i = i;
    this->j = j;
    this->value = *(this->arr + this->translate(this->i, this->j));
}

void co_matrix_walker::move_left() {
    this->j = this->j - 1;
    this->value = *(this->arr + this->translate(this->i, this->j));
}

void co_matrix_walker::move_right() {
    this->j = this->j + 1;
    this->value = *(this->arr + this->translate(this->i, this->j));
}

void co_matrix_walker::move_up() {
    this->i = this->i - 1;
    this->value = *(this->arr + this->translate(this->i, this->j));
}

void co_matrix_walker::move_down() {
    this->i = this->i + 1;
    this->value = *(this->arr + this->translate(this->i, this->j));
}
int co_matrix_walker::get() {
    return this->value;
}
void co_matrix_walker::set(int i, int j, int value) {
    *(this->arr + this->translate(i, j)) = value;
}