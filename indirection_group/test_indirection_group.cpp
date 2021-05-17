#include "indirection_group.h"
#include <assert.h>
#include <iostream>
using namespace std;

void test_inserts() {
    indirection_group grp(3);
    assert(grp.insert(3) == false);
    assert(grp.get_max() == 3);
    assert(grp.overloaded() == false);

    assert(grp.insert(2) == false);
    assert(grp.get_max() == 3);
    assert(grp.overloaded() == false);

    assert(grp.insert(7) == false);
    assert(grp.get_max() == 7);
    assert(grp.overloaded() == false);

    assert(grp.insert(-1) == true);
    assert(grp.get_max() == 7);
    assert(grp.overloaded() == true);

    cout<<"test_inserts: Success!\n";
}

void test_splits() {
    indirection_group grp(5);
    grp.insert(100);
    grp.insert(101);
    grp.insert(102);
    grp.insert(103);
    grp.insert(104);
    int min_value = 100;
    for (int i = 0; i < 10; ++i) {
        int max_value = grp.get_max();
        assert(grp.insert(--min_value) == true);
        assert(grp.overloaded() == true);

        indirection_group *temp_grp = grp.split();//size 3

        assert(temp_grp->get_max() == max_value);
        assert (grp.overloaded() == false);
        assert (temp_grp->overloaded() == false);
        assert (grp.get_max() <= temp_grp->get_max());
        assert (grp.insert(--min_value) == false); //size 4
        assert (grp.insert(--min_value) == false); //size 5
    }
    cout << "test_split: Success!\n";
}

void test_merge_and_split_1() {
    indirection_group grp1(5);
    grp1.insert(1);
    grp1.insert(2);
    grp1.insert(3);

    indirection_group grp2(5);
    grp2.insert(4);
    grp2.insert(5);
    grp2.insert(6);

    assert(grp1.merge_and_split(&grp2) == true);
    assert(grp1.get_max() == 3);
    assert(grp2.get_max() == 6);
    assert(grp1.overloaded() == false);
    assert(grp2.overloaded() == false);
    cout << "test_merge_and_split_1: Success!\n";
}

void test_merge_and_split_2() {
    indirection_group grp1(5);
    grp1.insert(10);
    grp1.insert(11);
    grp1.insert(12);

    indirection_group grp2(5);
    grp2.insert(4);
    grp2.insert(5);
    grp2.insert(6);

    assert(grp1.merge_and_split(&grp2) == true);
    assert(grp1.get_max() == 6);
    assert(grp2.get_max() == 12);
    assert(grp1.overloaded() == false);
    assert(grp2.overloaded() == false);
    cout << "test_merge_and_split_2: Success!\n";
}

void test_merge_and_split_3() {
    indirection_group grp1(5);
    grp1.insert(10);
    grp1.insert(11);
    grp1.insert(12);

    indirection_group grp2(5);
    grp2.insert(4);
    grp2.insert(5);
    
    assert(grp1.merge_and_split(&grp2) == false);
    assert(grp1.get_max() == 12);
    cout << "test_merge_and_split_3: Success!\n";
}

int main() {
    test_inserts();
    test_splits();
    test_merge_and_split_1();
    test_merge_and_split_2();
    test_merge_and_split_3();
}