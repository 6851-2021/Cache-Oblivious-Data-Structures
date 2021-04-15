#include "matrix_walker.h"
#include <stdlib.h>
#include <iostream>

int test_random(int n, int m, long long q) {
    #if PERF
        co_matrix_walker *matrix = new co_matrix_walker(n, m);
    #else
        naive_matrix_walker *matrix = new naive_matrix_walker(n, m);
    #endif
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++) {
            matrix->set(i, j, i + 2*j);
        }
    }

    int i, j;
    while(q--) {
        i = rand()%n;
        j = rand()%m;
        matrix->teleport(i, j);

        //move up
        while (i > 0) {
            if(matrix->get() != i + 2*j) {
                fprintf(stderr, "move down wrong\n");
                return -1;
            }
            matrix->move_up();
            i-=1;
        }

        //move left
        while (j > 0) {
            if(matrix->get() != i + 2*j) {
                fprintf(stderr, "move left wrong\n");
                return -1;
            }
            matrix->move_left();
            j-=1;
        }

        //move down
        while (i < n-1) {
            if(matrix->get() != i + 2*j) {
                fprintf(stderr, "move up wrong\n");
                return -1;
            }
            matrix->move_down();
            i+=1;
        }

        //move right
        while (j < m-1) {
            if(matrix->get() != i + 2*j) {
                fprintf(stderr, "move right wrong\n");
                return -1;
            }
            matrix->move_right();
            j+=1;
        }
    }

    return 0;
}
int main(){
    srand(10);
    test_random(100, 100, 100000);
}