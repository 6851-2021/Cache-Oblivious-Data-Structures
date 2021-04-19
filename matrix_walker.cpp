#include "matrix_walker.h"
#include <stdlib.h> 
#include <iostream>
#include <immintrin.h>

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

naive_matrix_walker:: naive_matrix_walker(int n) {
    this->n = n;
    this->arr = (int*) malloc(n * n * sizeof(int));
}

inline int naive_matrix_walker::translate(int i, int j) {
    return i * this->n + j;
}

void naive_matrix_walker::teleport(int i, int j) {
    this->i = i;
    this->j = j;
    this->value = *(this->arr + this->translate(this->i, this->j));
}

void naive_matrix_walker::move_left() {
    if(this-> j == 0)
        return;
    this->j = this->j - 1;
    this->value = *(this->arr + this->translate(this->i, this->j));
}

void naive_matrix_walker::move_right() {
    if(this->j == this->n-1)
        return;
    this->j = this->j + 1;
    this->value = *(this->arr + this->translate(this->i, this->j));
}

void naive_matrix_walker::move_up() {
    if(this->i == 0)
        return;
    this->i = this->i - 1;
    this->value = *(this->arr + this->translate(this->i, this->j));
}

void naive_matrix_walker::move_down() {
    if(this->i == n - 1)
        return;
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

co_matrix_walker:: co_matrix_walker(int n) {
    this->n = n;
    this->n_pw2 = next_power_of_2(n);
    this->arr = (int *)malloc(this->n_pw2 * this->n_pw2 * sizeof(int));
    this->i = 0;
    this->j = 0;
    this->z_value = 0;
    this->value = 0;
    this->even_bits = 0;
    long long size = this->n_pw2 * this->n_pw2;
    for (long long i = 1; i < size; i <<= 2)
    {
        this->even_bits |= i;
    }
    this->odd_bits = 0;
    for (long long i = 2; i < size; i <<= 2) {
        this->odd_bits |= i;
    }
}

uint64_t interleave_uint32_with_zeros(uint32_t input)  {
    uint64_t word = input;
    word = (word ^ (word << 16)) & 0x0000ffff0000ffff;
    word = (word ^ (word << 8 )) & 0x00ff00ff00ff00ff;
    word = (word ^ (word << 4 )) & 0x0f0f0f0f0f0f0f0f;
    word = (word ^ (word << 2 )) & 0x3333333333333333;
    word = (word ^ (word << 1 )) & 0x5555555555555555;
    return word;
}

int interleave(int x, int y) {
    return interleave_uint32_with_zeros(x) 
  | (interleave_uint32_with_zeros(y) << 1);
}

int co_matrix_walker::translate(int i, int j) {
    return interleave(j, i);
    // int top_left_i = 0;
    // int top_left_j = 0;
    // int bottom_right_i = this->n_pw2;
    // int bottom_right_j = this->n_pw2;
    // int block_index = 0;
    // /*
    // --------------
    // |  1   |  2  |
    // --------------
    // |  3   |  4  |
    // --------------
    // */
    // while (top_left_i != bottom_right_i - 1 && top_left_j != bottom_right_j - 1)
    // {
    //     int mid_i = (top_left_i + bottom_right_i) >> 1;
    //     int mid_j = (top_left_j + bottom_right_j) >> 1;

    //     if(i >= mid_i) {
    //         block_index += (mid_i - top_left_i) * (bottom_right_j - top_left_j);
    //         if(j >= mid_j) {
    //             block_index += (mid_j - top_left_j) * (bottom_right_i - mid_i);
    //             top_left_i = mid_i;
    //             top_left_j = mid_j;
    //         } else {
    //             top_left_i = mid_i;
    //             bottom_right_j = mid_j;
    //         }
    //     } else {
    //         if(j >= mid_j) {
    //             block_index += (mid_j - top_left_j) * (mid_i - top_left_i);
    //             bottom_right_i = mid_i;
    //             top_left_j = mid_j;
    //         } else {
    //             bottom_right_i = mid_i;
    //             bottom_right_j = mid_j;
    //         }
    //     }
    // }
    // //at the end we might end up with a 1D block
    // return block_index + (i - top_left_i) + (j - top_left_j);
}

void co_matrix_walker::teleport(int i, int j) {
    this->i = i;
    this->j = j;
    this->z_value = this->translate(this->i, this->j);
    this->value = *(this->arr + this->z_value);
}

void co_matrix_walker::move_left() {
    if(this->j == 0)
        return;
    this->j = this->j - 1;
    this->z_value = (((this->z_value & this->even_bits) - 1) & this->even_bits) | (this->z_value & this->odd_bits);
    this->value = *(this->arr + this->z_value);
}

void co_matrix_walker::move_right() {
    if(this->j == n - 1)
        return;
    this->j = this->j + 1;
    this->z_value = (((this->z_value | this->odd_bits) + 1) & this->even_bits) | (this->z_value & this->odd_bits);
    this->value = *(this->arr + this->z_value);
}

void co_matrix_walker::move_up() {
    if(this->i == 0)
        return;
    this->i = this->i - 1;
    this->z_value = (((this->z_value & this->odd_bits) - 1) & this->odd_bits) | (this->z_value & this->even_bits);
    this->value = *(this->arr + this->z_value);
}

void co_matrix_walker::move_down() {
    if(this->i == n-1)
        return;
    this->i = this->i + 1;
    this->z_value = (((this->z_value | this->even_bits) + 1) & this->odd_bits) | (this->z_value & this->even_bits);
    this->value = *(this->arr + this->z_value);
}
int co_matrix_walker::get() {
    return this->value;
}
void co_matrix_walker::set(int i, int j, int value) {
    *(this->arr + this->translate(i, j)) = value;
}